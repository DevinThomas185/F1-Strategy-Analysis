#include "udp_updater.h"
#include <QtCore>
#include <iostream>
#include <iomanip>
#include <string>
#include <locale>
#include <codecvt>
#include <algorithm>

#include "enums.hpp"
#include "formatting.hpp"

#define INTERVALS_RECORDED_AT_M 500.0f

UDPUpdater::UDPUpdater(QObject *parent)
    : QThread{parent},
    participants_(22)
{

}

void UDPUpdater::run()
{
    while (enable_listening) {
        const PacketData packet = udp_listener.getPacket();
        PacketType packetType = getPacketType(packet);

        if (packetType == PacketType::PARTICIPANTS) {
            handleParticipantsPacket(packet);
            raceRecorder.handleParticipantsPacket(packet);
        }

        if (!participantsReceived) continue;

        switch (packetType)
        {
        case PacketType::MOTION:
            handleMotionPacket(packet);
            raceRecorder.handleMotionPacket(packet);
            break;
        case PacketType::SESSION:
            handleSessionPacket(packet);
            raceRecorder.handleSessionPacket(packet);
            break;
        case PacketType::LAP_DATA:
            handleLapPacket(packet);
            raceRecorder.handleLapPacket(packet);
            break;
        case PacketType::EVENT:
            handleEventPacket(packet);
            raceRecorder.handleEventPacket(packet);
            break;
        case PacketType::PARTICIPANTS:
            // Handled above
            break;
        case PacketType::CAR_SETUPS:
            handleCarSetupPacket(packet);
            raceRecorder.handleCarSetupPacket(packet);
            break;
        case PacketType::CAR_TELEMETRY:
            handleCarTelemetryPacket(packet);
            raceRecorder.handleCarTelemetryPacket(packet);
            break;
        case PacketType::CAR_STATUS:
            handleCarStatusPacket(packet);
            raceRecorder.handleCarStatusPacket(packet);
            break;
        case PacketType::FINAL_CLASSIFICATION:
            handleFinalClassificationPacket(packet);
            raceRecorder.handleFinalClassificationPacket(packet);
            break;
        case PacketType::LOBBY_INFO:
            handleLobbyInfoPacket(packet);
            raceRecorder.handleLobbyInfoPacket(packet);
            break;
        case PacketType::CAR_DAMAGE:
            handleCarDamagePacket(packet);
            raceRecorder.handleCarDamagePacket(packet);
            break;
        case PacketType::SESSION_HISTORY:
            handleSessionHistoryPacket(packet);
            raceRecorder.handleSessionHistoryPacket(packet);
            break;
        default:
            break;
        }
    }
}

void UDPUpdater::handleMotionPacket(const PacketData& packet) {
    const PacketMotionData motionData = packet.packet.motionData;

    PositionalDataMap pdm;
    for (size_t i = 0; i < participants_.size(); i++) {
        CarMotionData cd = motionData.carMotionData[i];

        if (cd.worldPositionX == 0 && cd.worldPositionY == 0 && cd.worldPositionZ == 0) continue; // Unused positional data (22 cars)

        PositionalData pd = {
            .driverLabel = std::string(participants_[i].name).substr(0, 3),
            .driverColour = getTeamColour(getTeamID(participants_[i].teamId)),
            .x = cd.worldPositionX,
            .y = cd.worldPositionY,
            .z = cd.worldPositionZ
        };
        pdm.push_back(pd);
    }

    emit PositionalDataMapUpdate(pdm);

}

void UDPUpdater::handleSessionPacket(const PacketData& packet) {
    const PacketSessionData sessionData = packet.packet.sessionData;

    // Send weather update
    WeatherData wd;
    for (uint8_t i = 0; i < sessionData.numWeatherForecastSamples; i++) {
        WeatherForecastSample sample = sessionData.weatherForecastSamples[i];
        WeatherDataBox box = {
            .timeOffset = sample.timeOffset == 0 ? "Now" : std::to_string(sample.timeOffset) + " Minutes" ,
            .status = getWeatherString(getWeather(sample.weather)),
            .trackTemp = std::to_string(sample.trackTemperature) + "°C",
            .airTemp = std::to_string(sample.airTemperature) + "°C",
            .rainPercent = std::to_string(sample.rainPercentage) + "%",
        };
        wd.push_back(box);
    }
    emit WeatherUpdate(wd);

    // Send safety car status

    emit SafetyCarStatusUpdate(getSafetyCarStatus(sessionData.safetyCarStatus));


    if (totalLaps != sessionData.totalLaps) {
        totalLaps = sessionData.totalLaps;
        emit TotalLapsUpdate(totalLaps);
    }

    if (trackLength != sessionData.trackLength) {
        trackLength = sessionData.trackLength;
        emit TrackLengthUpdate(trackLength);
    }

    if (track != getTrackID(sessionData.trackId)) {
        track = getTrackID(sessionData.trackId);
        emit TrackUpdate(track);
    }

    if (sessionType != getSessionType(sessionData.sessionType)) {
        sessionType = getSessionType(sessionData.sessionType);
        emit SessionTypeUpdate(sessionType);
    }

}

bool comparePositions (PositionsTableRow d1, PositionsTableRow d2) {
    return std::stoi(d1.position) < std::stoi(d2.position);
}

uint16_t roundDownToInterval(float lapDistance) {
    return std::floor(lapDistance / INTERVALS_RECORDED_AT_M) * INTERVALS_RECORDED_AT_M;
}

void UDPUpdater::handleLapPacket(const PacketData& packet){
    const PacketLapData lapData = packet.packet.lapData;
    const uint32_t sessionTime = static_cast<uint32_t>(packet.header.sessionTime * 1000);

    // Send data for positions table
    PositionsTable rows;
    for (size_t i = 0; i < participants_.size(); i++) {
        LapData ld = lapData.lapData[i];

        // Set the time at this interval for this lap for each driver
        driverIntervalTimes[i][ld.currentLapNum-1].insert({roundDownToInterval(ld.lapDistance), sessionTime});

        if (ld.carPosition == 0) continue; // Unused positional data (not all 22 cars)

        PositionsTableRow row = {
            ._carIdx = i,
            ._lapData = ld,
            .position = std::to_string(ld.carPosition),
            .driver = participants_[i].name,
            .positionChange = (ld.gridPosition + 1) - ld.carPosition, // gridPosition is from 0?
            .sector1 = formatSectorMS(ld.sector1TimeInMS),
            .sector2 = formatSectorMS(ld.sector2TimeInMS),
            .lastlap = formatLapTimeMS(ld.lastLapTimeInMS),
            .interval = "---", // TEMPORARY
            .tyreData = driverTyreData[i],
        };
        rows.push_back(row);
    }
    std::sort(rows.begin(), rows.end(), comparePositions); // Sorted by positions, now add intervals


    // INTERVAL CALCULATIONS

    // Start at 1 (P2) to ignore the leader
    for (size_t pos = 1; pos < rows.size(); pos++) {
        LapData ld = rows[pos]._lapData;
        uint8_t carIdx = rows[pos]._carIdx;
        uint8_t aheadCarIdx = rows[pos-1]._carIdx;
        uint8_t aheadDriverCurrentLap = rows[pos-1]._lapData.currentLapNum;
        float lapDistance = ld.lapDistance;

        if (ld.carPosition == 0) continue; // Unused positional data (not all 22 cars)

        uint32_t carTimeAtX = driverIntervalTimes[carIdx][ld.currentLapNum-1][roundDownToInterval(lapDistance)];
        uint32_t aheadCarTimeAtX = driverIntervalTimes[aheadCarIdx][ld.currentLapNum-1][roundDownToInterval(lapDistance)];

        // Interval = Time at which you passed x metres - Time at which driver ahead passed x metres
        uint32_t intervalMS = carTimeAtX > aheadCarTimeAtX ? carTimeAtX - aheadCarTimeAtX : 0;

        rows[pos].interval = formatIntervalTime(intervalMS, aheadDriverCurrentLap, ld.currentLapNum);
    }

    emit PositionsTableUpdate(rows);

    LapData wld = lapData.lapData[driverSelected];

    WheelLapData wheelData = {
        .currentPosition = "P" + std::to_string(wld.carPosition),
        .currentLapTime = formatLapTimeMS(wld.currentLapTimeInMS),
        .currentLapNumber = "L" + std::to_string(wld.currentLapNum),
    };

    emit WheelLapUpdate(wheelData);

    emit LapDistanceUpdate(wld.lapDistance);
}

std::string logStartLights(int numLights) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string lights = converter.to_bytes(std::wstring(numLights, L'🔴') + std::wstring(5 - numLights, L'🔵'));
    return lights;
}

void UDPUpdater::handleEventPacket(const PacketData& packet) {
    const PacketEventData event = packet.packet.eventData;
    const EventDataDetails eventDetails = event.eventDetails;

    std::string msg;
    switch (eventStringCodeToEventType(event.eventStringCode))
    {
    case ::SESSION_STARTED:
        msg.append("Session Started");
        break;
    case ::SESSION_ENDED:
        msg.append("Session Ended");
        break;
    case ::FASTEST_LAP:
        msg.append(participants_[eventDetails.FastestLap.vehicleIdx].name);
        msg.append(" has set the fastest lap of ");
        msg.append(formatLapTime(eventDetails.FastestLap.lapTime));
        break;
    case ::RETIREMENT:
        msg.append(participants_[eventDetails.Retirement.vehicleIdx].name);
        msg.append(" has retired");
        break;
    case ::DRS_ENABLED:
        msg.append("DRS Enabled");
        break;
    case ::DRS_DISABLED:
        msg.append("DRS Disabled");
        break;
    case ::TEAM_MATE_IN_PITS:
        msg.append(participants_[eventDetails.TeamMateInPits.vehicleIdx].name);
        msg.append(" is in the pits");
        break;
    case ::CHEQUERED_FLAG:
        msg.append("Chequered flag has been waved");
        break;
    case ::RACE_WINNER:
        msg.append(participants_[eventDetails.RaceWinner.vehicleIdx].name);
        msg.append(" has won the race!");
        break;
    case ::PENALTY_ISSUED:
        msg = handlePenaltyIssued(event);
        break;
    case ::SPEED_TRAP_TRIGGERED:
        msg.append(participants_[eventDetails.RaceWinner.vehicleIdx].name);
        msg.append(" hit ");
        msg.append(formatFloatTo2DP(convertKPHtoMPH(eventDetails.SpeedTrap.speed)));
        msg.append(" MPH");
        break;
    case ::START_LIGHTS:
        msg.append(logStartLights((int)eventDetails.StartLights.numLights));
        break;
    case ::LIGHTS_OUT:
        msg.append("🟢🟢🟢🟢🟢"); // TODO: Distinguish between formation lap and the actual race start
        break;
    case ::DRIVE_THROUGH_SERVED:
        msg.append(participants_[eventDetails.RaceWinner.vehicleIdx].name);
        msg.append(" has served their drive through penalty");
        break;
    case ::STOP_AND_GO_SERVED:
        msg.append(participants_[eventDetails.RaceWinner.vehicleIdx].name);
        msg.append(" has served their stop and go penalty");
        break;
    case ::FLASHBACK:
        msg.append("Flashback to ");
        msg.append(std::to_string(eventDetails.Flashback.flashbackSessionTime));
        break;
    case ::BUTTON_STATUS:
        return; // Currently do nothing if just button data is received
    default:
        return; // Don't log anything after this
    }

    emit EventAnnouncementUpdate(msg);
}

void UDPUpdater::handleParticipantsPacket(const PacketData& packet) {
    const PacketParticipantsData participantsData = packet.packet.participantsData;

    if (changedParticipants(participantsData)) {
        Participants ps;
        ps.playerCarIdx = packet.header.playerCarIndex;
        ps.secondCarIdx = packet.header.secondaryPlayerCarIndex;

        for (int i = 0; i < participantsData.numActiveCars; i++) {
            participants_[i] = participantsData.participants[i];

            auto pi = participantsData.participants[i];
            Participant p = {
                .driverId = getDriverID(pi.driverId),
                .teamId = getTeamID(pi.teamId),
                .raceNumber = pi.raceNumber,
                .nationality = getNationalityID(pi.nationality),
                .name = pi.name,
            };
            ps.participants.push_back(p);
        }

        participantsReceived = true;

        emit ParticipantsUpdate(ps);
    }
}

void UDPUpdater::handleCarSetupPacket(const PacketData& packet) {
    const PacketCarSetupData setupData = packet.packet.carSetupData;

    // TODO: Do not keep updating the setup packet, just do it once
    for (size_t i = 0; i < participants_.size(); i++) {
        driverCarSetup[i] = setupData.carSetups[i];
    }
}

std::string getRevLights(uint16_t n) {
    int bits = std::bitset < 16 > (n).count();
    std::string revLights;
    for (int i = 0; i < bits; i++) {
        revLights += "🔴";
    }
    return revLights;
}

void UDPUpdater::handleCarTelemetryPacket(const PacketData& packet){
    const PacketCarTelemetryData telemetryData = packet.packet.carTelemetryData;

    CarTelemetryData td = telemetryData.carTelemetryData[driverSelected];

    TemperaturePressureData tempsPressure = {
        .rearLeftSurfaceTemperature = td.tyresSurfaceTemperature[REAR_LEFT],
        .rearRightSurfaceTemperature = td.tyresSurfaceTemperature[REAR_RIGHT],
        .frontLeftSurfaceTemperature = td.tyresSurfaceTemperature[FRONT_LEFT],
        .frontRightSurfaceTemperature = td.tyresSurfaceTemperature[FRONT_RIGHT],

        .rearLeftInnerTemperature = td.tyresInnerTemperature[REAR_LEFT],
        .rearRightInnerTemperature = td.tyresInnerTemperature[REAR_RIGHT],
        .frontLeftInnerTemperature = td.tyresInnerTemperature[FRONT_LEFT],
        .frontRightInnerTemperature = td.tyresInnerTemperature[FRONT_RIGHT],

        .rearLeftBrakeTemperature = td.brakesTemperature[REAR_LEFT],
        .rearRightBrakeTemperature = td.brakesTemperature[REAR_RIGHT],
        .frontLeftBrakeTemperature = td.brakesTemperature[FRONT_LEFT],
        .frontRightBrakeTemperature = td.brakesTemperature[FRONT_RIGHT],

        .engineTemperature = td.engineTemperature,

        .rearLeftPressure = td.tyresPressure[REAR_LEFT],
        .rearRightPressure = td.tyresPressure[REAR_RIGHT],
        .frontLeftPressure = td.tyresPressure[FRONT_LEFT],
        .frontRightPressure = td.tyresPressure[FRONT_RIGHT],

        .setupRearLeftPressure = driverCarSetup[driverSelected].rearLeftTyrePressure,
        .setupRearRightPressure = driverCarSetup[driverSelected].rearRightTyrePressure,
        .setupFrontLeftPressure = driverCarSetup[driverSelected].frontLeftTyrePressure,
        .setupFrontRightPressure = driverCarSetup[driverSelected].frontRightTyrePressure,
    };

    emit TemperaturePressureUpdate(tempsPressure);


    WheelTelemetryData wheelTelemetry = {
        .speed = convertKPHtoMPH(td.speed),
        .throttle = static_cast<uint8_t>(td.throttle * 100),
        .brake = static_cast<uint8_t>(td.brake * 100),
        .clutch = td.clutch,
        .steering = static_cast<int8_t>(td.steer * 100),
        .gear = td.gear,
        .rpm = td.engineRPM,
        .drsActivated = td.drs == 1,
        .revLights = getRevLights(td.revLightsBitValue),
    };

    emit WheelTelemetryUpdate(wheelTelemetry);


    PlotTelemetryData plotTelemetryData = {
        .speed = convertKPHtoMPH(td.speed),
        .throttle = static_cast<uint8_t>(td.throttle * 100),
        .brake = static_cast<uint8_t>(td.brake * 100),
        .rpm = td.engineRPM,
        .gear = td.gear,
        .steering = static_cast<int8_t>(td.steer * 100),
    };

    emit PlotTelemetryUpdate(plotTelemetryData);
}

void UDPUpdater::handleCarStatusPacket(const PacketData& packet){
    const PacketCarStatusData statusData = packet.packet.carStatusData;

    // Update map for current tyre data
    for (size_t i = 0; i < participants_.size(); i++) {
        CarStatusData sd = statusData.carStatusData[i];
        TyreData td = {
            .actualTyreCompound = getActualTyreCompound(sd.actualTyreCompound),
            .visualTyreCompound = getVisualTyreCompound(sd.visualTyreCompound),
            .tyreAge = sd.tyresAgeLaps,
        };
        driverTyreData[i] = td;
    }

    CarStatusData sd = statusData.carStatusData[driverSelected];

    WheelStatusData wheelStatus = {
        .ersDeployMode = getERSDeployMode(sd.ersDeployMode),
        .ersPercent = static_cast<uint8_t>((sd.ersStoreEnergy * 100) / 4000000),
        .ersDeployedThisLap = static_cast<uint8_t>((sd.ersDeployedThisLap * 100) / 4000000),
        .frontBrakeBias = std::to_string(sd.frontBrakeBias) + "%",
        .fuelRemainingLaps = sd.fuelRemainingLaps,
        .drsAllowed = sd.drsAllowed == 1,
        // TODO: ADD ERS USED THIS LAP
    };

    emit WheelStatusUpdate(wheelStatus);
}

void UDPUpdater::handleFinalClassificationPacket(const PacketData& packet){}

void UDPUpdater::handleLobbyInfoPacket(const PacketData& packet){}

void UDPUpdater::handleCarDamagePacket(const PacketData& packet){
    const PacketCarDamageData damageData = packet.packet.carDamageData;

    CarDamageData cd = damageData.carDamageData[driverSelected];

    DamageData damage = {
        // TODO: FIX WHATEVER TYRE WEAR IS SUPPOSED TO MEAN
        .rearLeftTyreWearPercent = static_cast<uint8_t>(cd.tyresWear[REAR_LEFT] * 100),
        .rearRightTyreWearPercent = static_cast<uint8_t>(cd.tyresWear[REAR_RIGHT] * 100),
        .frontLeftTyreWearPercent = static_cast<uint8_t>(cd.tyresWear[FRONT_LEFT] * 100),
        .frontRightTyreWearPercent = static_cast<uint8_t>(cd.tyresWear[FRONT_RIGHT] * 100),

        .rearLeftTyreDamagePercent = cd.tyresDamage[REAR_LEFT],
        .rearRightTyreDamagePercent = cd.tyresDamage[REAR_RIGHT],
        .frontLeftTyreDamagePercent = cd.tyresDamage[FRONT_LEFT],
        .frontRightTyreDamagePercent = cd.tyresDamage[FRONT_RIGHT],

        .rearLeftBrakeDamagePercent = cd.brakesDamage[REAR_LEFT],
        .rearRightBrakeDamagePercent = cd.brakesDamage[REAR_RIGHT],
        .frontLeftBrakeDamagePercent = cd.brakesDamage[FRONT_LEFT],
        .frontRightBrakeDamagePercent = cd.brakesDamage[FRONT_RIGHT],

        .frontLeftWingDamagePercent = cd.frontLeftWingDamage,
        .frontRightWingDamagePercent = cd.frontRightWingDamage,

        .rearWingDamagePercent = cd.rearWingDamage,

        .floorDamagePercent = cd.floorDamage,
        .sidepodDamagePercent = cd.sidepodDamage,
        .diffuserDamagePercent = cd.diffuserDamage,

        .drsFault = cd.drsFault == 0 ? "OK" : "FAULT",
        .ersFault = cd.ersFault == 0 ? "OK" : "FAULT",

        .gearboxDamagePercent = cd.gearBoxDamage,
        .engineDamagePercent = cd.engineDamage,

        .mguhWearPercent = cd.engineMGUHWear,
        .esWearPercent = cd.engineESWear,
        .ceWearPercent = cd.engineCEWear,
        .iceWearPercent = cd.engineICEWear,
        .mgukWearPercent = cd.engineMGUKWear,
        .tcWearPercent = cd.engineTCWear,

        .engineBlownFault = cd.engineBlown == 0 ? "OK" : "FAULT",
        .engineSeizedFault = cd.engineSeized == 0 ? "OK" : "FAULT",
    };

    emit DamageUpdate(damage);
}

void UDPUpdater::handleSessionHistoryPacket(const PacketData& packet){
    const PacketSessionHistoryData sessionHistoryData = packet.packet.sessionHistoryData;

    if (sessionHistoryData.carIdx != driverSelected) return; // Do nothing if the packet is not of the observed driver

    LapHistoryTable ld;

    for (uint8_t i = 0; i < 100; i++) {
        LapHistoryData lap = sessionHistoryData.lapHistoryData[i];
        if (lap.lapTimeInMS == 0) break; // No more laps

        LapHistoryRow ldr = {
            .lap = static_cast<uint8_t>(i + 1),
            .sector1 = formatSectorMS(lap.sector1TimeInMS),
            .sector2 = formatSectorMS(lap.sector2TimeInMS),
            .sector3 = formatSectorMS(lap.sector3TimeInMS),
            .lapTime = formatLapTimeMS(lap.lapTimeInMS),
            ._lapTimeMS = lap.lapTimeInMS,
            .sector1Valid = static_cast<bool>(lap.lapValidBitFlags & 0x02),
            .sector2Valid = static_cast<bool>(lap.lapValidBitFlags & 0x04),
            .sector3Valid = static_cast<bool>(lap.lapValidBitFlags & 0x08),
            .lapValid = static_cast<bool>(lap.lapValidBitFlags & 0x01),
            .tyre = "", // TEMPORARY
            .tyreColour = Colour(0, 0, 0), // TEMPORARY
        };
        ld.table.push_back(ldr);
    }

    ld.bestLapTimeLap = sessionHistoryData.bestLapTimeLapNum;
    ld.bestSector1Lap = sessionHistoryData.bestSector1LapNum;
    ld.bestSector2Lap = sessionHistoryData.bestSector2LapNum;
    ld.bestSector3Lap = sessionHistoryData.bestSector3LapNum;

    size_t lastStintEnd = 0;
    for (size_t i = 0; i < 8; i++) {
        TyreStintHistoryData stint = sessionHistoryData.tyreStintsHistoryData[i];
        for (size_t l = lastStintEnd; l <= stint.endLap; l++) {
            if (l < ld.table.size()) { // endLap = 255 if this is the current stint, so stop at the last lap and break after
                ld.table[l].tyre = getActualTyreName(getActualTyreCompound(stint.tyreActualCompound));
                ld.table[l].tyreColour = getVisualTyreColour(getVisualTyreCompound(stint.tyreVisualCompound));
            } else {
                break;
            }
            lastStintEnd = stint.endLap+1;
        }
    }

    // Put Lap 1 at the bottom, most recent lap x on the top
    std::reverse(ld.table.begin(), ld.table.end());

    emit LapHistoryTableUpdate(ld);
}

std::string UDPUpdater::handlePenaltyIssued(const PacketEventData event) {
    EventDataDetails eventDetails = event.eventDetails;
    std::string msg(participants_[eventDetails.Penalty.vehicleIdx].name);
    PenaltyTypeID penaltyType = getPenaltyTypeID(eventDetails.Penalty.penaltyType);
    switch (penaltyType)
    {
    case ::DRIVE_THROUGH:
        msg.append(" has been given a drive through penalty due to ");
        msg.append(handleInfringement(eventDetails));
        break;
    case ::STOP_AND_GO:
        msg.append(" has been given a stop and go penalty due to ");
        msg.append(handleInfringement(eventDetails));
        break;
    case ::GRID_PENALTY:
        msg.append(" has been given a grid penalty due to ");
        msg.append(handleInfringement(eventDetails));
        break;
    case ::PENALTY_REMINDER:
        msg.append(" has a penalty reminder for ");
        msg.append(handleInfringement(eventDetails));
        break;
    case ::TIME_PENALTY:
        msg.append(" has a ");
        msg.append(std::to_string(eventDetails.Penalty.time));
        msg.append(" second time penalty due to ");
        msg.append(handleInfringement(eventDetails));
        break;
    case ::WARNING:
        msg.append(" has a warning for ");
        msg.append(handleInfringement(eventDetails));
        break;
    case ::DISQUALIFIED_PENALTY:
        msg.append(" has been disqualified due to ");
        msg.append(handleInfringement(eventDetails));
        break;
    case ::REMOVED_FROM_FORMATION_LAP:
        msg.append(" has been removed from the formation lap due to ");
        msg.append(handleInfringement(eventDetails));
        break;
    case ::PARKED_TOO_LONG_TIMER:
        msg.append(" has been parked too long for ");
        msg.append(std::to_string(eventDetails.Penalty.time));
        msg.append(" seconds");
        break;
    case ::TYRE_REGULATIONS:
        msg.append(" has a tyre regulations penalty for ");
        msg.append(handleInfringement(eventDetails));
        break;
    case ::THIS_LAP_INVALIDATED:
        msg.append(" has had this lap invalidated due to ");
        msg.append(handleInfringement(eventDetails));
        break;
    case ::THIS_AND_NEXT_LAP_INVALIDATED:
        msg.append(" has had this lap and next lap invalidated due to ");
        msg.append(handleInfringement(eventDetails));
        break;
    case ::THIS_LAP_INVALIDATED_WITHOUT_REASON:
        msg.append(" has had this lap invalidated without reason");
        break;
    case ::THIS_AND_NEXT_LAP_INVALIDATED_WITHOUT_REASON:
        msg.append(" has had this lap and next lap invalidated without reason");
        break;
    case ::THIS_AND_PREVIOUS_LAP_INVALIDATED:
        msg.append(" has had this lap and the previous lap invalidated due to ");
        msg.append(handleInfringement(eventDetails));
        break;
    case ::THIS_AND_PREVIOUS_LAP_INVALIDATED_WITHOUT_REASON:
        msg.append(" has had this lap and the previous lap invalidated without reason");
        break;
    case ::RETIRED_PENALTY:
        msg.append(" has retired due to ");
        msg.append(handleInfringement(eventDetails));
        break;
    case ::BLACK_FLAG_TIMER_PENALTY:
        msg.append(" has a black flag timer for ");
        msg.append(std::to_string(eventDetails.Penalty.time));
        msg.append(" seconds");
        msg.append(handleInfringement(eventDetails));
        break;
    default:
        break;
    }
    return msg;
}

std::string UDPUpdater::handleInfringement(EventDataDetails eventDetails) {
    std::string msg;
    InfringementTypeID infringementType = getInfringementTypeID(eventDetails.Penalty.infringementType);
    switch (infringementType)
    {
    case ::BLOCKING_BY_DRIVING_SLOW:
        msg.append("blocking by driving slow");
        break;
    case ::BLOCKING_BY_WRONG_WAY_DRIVING:
        msg.append("blocking by driving the wrong way");
        break;
    case ::REVERSING_OFF_THE_START_LINE:
        msg.append("reversing off the start line");
        break;
    case ::BIG_COLLISION:
        msg.append("a big collision with ");
        msg.append(participants_[eventDetails.Penalty.otherVehicleIdx].name);
        break;
    case ::SMALL_COLLISION:
        msg.append("a small collision with ");
        msg.append(participants_[eventDetails.Penalty.otherVehicleIdx].name);
        break;
    case ::COLLISION_FAILED_TO_HAND_BACK_POSITION_SINGLE:
        msg.append("collision failed to hand back one position");
        break;
    case ::COLLISION_FAILED_TO_HAND_BACK_POSITION_MULTIPLE:
        msg.append("collision failed to hand back multiple positions");
        break;
    case ::CORNER_CUTTING_GAINED_TIME:
        msg.append("gaining time whilst corner cutting");
        // TODO: HOW MUCH TIME (in penalty .time)
        break;
    case ::CORNER_CUTTING_OVERTAKE_SINGLE:
        msg.append("gaining one place whilst corner cutting");
        break;
    case ::CORNER_CUTTING_OVERTAKE_MULTIPLE:
        msg.append("gaining multiple places whilst corner cutting");
        break;
    case ::CROSSED_PITLANE_EXIT:
        msg.append("crossing the pitlane exit");
        break;
    case ::IGNORING_BLUE_FLAGS:
        msg.append("ignoring blue flags");
        break;
    case ::IGNORING_YELLOW_FLAGS:
        msg.append("ignoring yellow flags");
        break;
    case ::IGNORING_DRIVE_THROUGH:
        msg.append("ignoring drive through penalty");
        break;
    case ::TOO_MANY_DRIVE_THROUGHS:
        msg.append("accumulating too many drive through penalties");
        break;
    case ::DRIVE_THROUGH_REMINDER_SERVE_WITHIN_N_LAPS:
        msg.append("serve drive through penalty within ");
        msg.append(std::to_string(eventDetails.Penalty.time));
        msg.append(" laps");
        break;
    case ::DRIVE_THROUGH_REMINDER_SERVE_THIS_LAP:
        msg.append("serve drive through penalty this lap");
        break;
    case ::PITLANE_SPEEDING:
        msg.append("speeding in the pitlane");
        break;
    case ::PARKED_FOR_TOO_LONG:
        msg.append("being parked for too long");
        break;
    case ::IGNORING_TYRE_REGULATIONS:
        msg.append("ignoring tyre regulations");
        break;
    case ::TOO_MANY_PENALTIES:
        msg.append("accumulating too many penalties");
        break;
    case ::MULTIPLE_WARNINGS:
        msg.append("receiving multiple warnings");
        break;
    case ::APPROACHING_DISQUALIFICATION:
        msg.append("approaching disqualification");
        break;
    case ::TYRE_REGULATIONS_SELECT_SINGLE:
        msg.append("having to select one tyre from the tyre regulations");
        break;
    case ::TYRE_REGULATIONS_SELECT_MULTIPLE:
        msg.append("having to select multiple tyres from the tyre regulations");
        break;
    case ::LAP_INVALIDATED_CORNER_CUTTING:
        msg.append("an invalidated lap due to corner cutting");
        break;
    case ::LAP_INVALIDATED_RUNNING_WIDE:
        msg.append("an invalidated lap due to running wide");
        break;
    case ::CORNER_CUTTING_RAN_WIDE_GAINED_TIME_MINOR:
        msg.append("gaining a minor amount of time whilst corner cutting");
        break;
    case ::CORNER_CUTTING_RAN_WIDE_GAINED_TIME_SIGNIFICANT:
        msg.append("gaining a significant amount of time whilst corner cutting (");
        msg.append(std::to_string(eventDetails.Penalty.time));
        msg.append(" seconds)");
        break;
    case ::CORNER_CUTTING_RAN_WIDE_GAINED_TIME_EXTREME:
        msg.append("gaining an extreme amount of time whilst corner cutting (");
        msg.append(std::to_string(eventDetails.Penalty.time));
        msg.append(" seconds)");
        break;
    case ::LAP_INVALIDATED_WALL_RIDING:
        msg.append("an invalidated lap due to wall riding");
        break;
    case ::BLOCKING_THE_PITLANE:
        msg.append("blocking the pitlane");
        break;
    case ::JUMP_START:
        msg.append("jumping the start");
        break;
    case ::SAFETY_CAR_TO_CAR_COLLISION:
        msg.append("colliding with the safety car");
        break;
    case ::SAFETY_CAR_ILLEGAL_OVERTAKE:
        msg.append("illegally overtaking the safety car");
        break;
    case ::SAFETY_CAR_EXCEEDING_ALLOWED_PACE:
        msg.append("exceeding the allowed pace under safety car conditions");
        break;
    case ::VIRTUAL_SAFETY_CAR_EXCEEDING_ALLOWED_PACE:
        msg.append("exceeding the allowed pace under virtual safety car conditions");
        break;
    case ::FORMATION_LAP_BELOW_ALLOWED_SPEED:
        msg.append("being below the allowed pace during the formation lap");
        break;
    case ::FORMATION_LAP_PARKING:
        msg.append("formation lap parking");
        break;
    case ::RETIRED_MECHANICAL_FAILURE:
        msg.append("mechanical failure");
        break;
    case ::RETIRED_TERMINALLY_DAMAGED:
        msg.append("terminal damage");
        break;
    case ::SAFETY_CAR_FALLING_TOO_FAR_BACK:
        msg.append("falling far too back under safety car conditions");
        break;
    case ::BLACK_FLAG_TIMER_INFRINGEMENT:
        msg.append("black flag timer");
        break;
    case ::UNSERVED_STOP_AND_GO_PENALTY:
        msg.append("an unserved stop and go penalty");
        break;
    case ::UNSERVED_DRIVE_THROUGH_PENALTY:
        msg.append("an unserved drive through penalty");
        break;
    case ::ENGINE_COMPONENT_CHANGE:
        msg.append("changing an engine component");
        break;
    case ::GEARBOX_CHANGE:
        msg.append("changing gearbox");
        break;
    case ::PARC_FERME_CHANGE:
        msg.append("changing the car under parc ferme conditions");
        break;
    case ::LEAGUE_GRID_PENALTY:
        msg.append("league grid penalty");
        break;
    case ::RETRY_PENALTY:
        msg.append("retry penalty");
        break;
    case ::ILLEGAL_TIME_GAIN:
        msg.append("illegal time gain");
        break;
    case ::MANDATORY_PITSTOP:
        msg.append("mandatory pitstop");
        break;
    case ::ATTRIBUTE_ASSIGNED:
        msg.append("attribute assigned");
        break;
    default:
        break;
    }
    return msg;
}

bool UDPUpdater::changedParticipants(PacketParticipantsData pd) {
    for (int i = 0; i < pd.numActiveCars; i++) {
        if (strcmp(pd.participants[i].name, participants_[i].name) != 0) {
            return true;
        }
    }
    return false;
}




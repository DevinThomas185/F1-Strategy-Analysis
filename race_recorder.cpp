#include "race_recorder.hpp"
#include "enums.hpp"
#include <iostream>
#include <google/protobuf/util/json_util.h>

RaceRecorder::RaceRecorder(QObject *parent)
    : QObject{parent}
{

}


void RaceRecorder::writeRaceToPB() {
    std::ofstream file(getFileName() + ".pb", std::ios::binary);

    // Serialize the message to the file
    if (raceWeekend.SerializeToOstream(&file)) {
        std::cout << "Race written to PB file successfully." << std::endl;
    } else {
        std::cerr << "Failed to write message to file." << std::endl;
    }
    file.close();
}

void RaceRecorder::writeRaceToJSON() {
    google::protobuf::util::JsonPrintOptions options;
    options.add_whitespace = true;

    std::string jsonString;
    google::protobuf::util::MessageToJsonString(raceWeekend, &jsonString, options);

    std::ofstream file(getFileName() + ".json");
    if (file.is_open()) {
        file << jsonString;
        file.close();
        std::cout << "Race written to JSON file successfully." << std::endl;
    } else {
        std::cerr << "Failed to write message to file." << std::endl;
    }
}

void RaceRecorder::startStint(StintType stintType) {
    switch (stintType) {
    case StintType::RACE_SIMULATION:
        currentStint = currentPractice->add_race_simulation();
        break;
    case StintType::QUALIFYING_SIMULATION:
        currentStint = currentPractice->add_qualifying_simulation();
        break;
    }

    // Set fields for a stint
    currentSetup = currentStint->mutable_setup();
    currentLap = currentStint->add_lap();
    currentlyRecording = true;

    currentStintType = stintType;
    emit StintStarted(currentStintType.value());
}


void RaceRecorder::handleMotionPacket(const PacketData& packet) {
    if (!currentlyRecording) return;
    lastMotionPacket = packet.packet.motionData;
}

void RaceRecorder::handleSessionPacket(const PacketData& packet) {
    const PacketSessionData sessionData = packet.packet.sessionData;

    SessionType session = getSessionType(sessionData.sessionType);

    // Session is not yet selected
    if (!currentSession.has_value()) {
        switch (session) {
        case SessionType::P1:
            currentPractice = raceWeekend.mutable_race_sessions()->mutable_fp1();
            break;
        case SessionType::P2:
            currentPractice = raceWeekend.mutable_race_sessions()->mutable_fp2();
            break;
        case SessionType::P3:
            currentPractice = raceWeekend.mutable_race_sessions()->mutable_fp3();
            break;
        // Cover the other session types here
        }
        currentSession = session;
    }

    trackId = getTrackID(sessionData.trackId);
    raceWeekend.set_track_id(sessionData.trackId);
}

void RaceRecorder::handleLapPacket(const PacketData& packet) {
    if (!currentlyRecording) return;

    const LapData lapData = packet.packet.lapData.lapData[playerCarIndex];

    DriverStatus newStatus = getDriverStatus(lapData.driverStatus);

    // If going from garage to lap (start of new stint)
    if (driverStatus == DriverStatus::IN_GARAGE 
    && (newStatus == DriverStatus::OUT_LAP
    ||  newStatus == DriverStatus::FLYING_LAP
    ||  newStatus == DriverStatus::ON_TRACK)) {
        // Nothing to do, all done in the startStint
    }
    
    // If going from lap to garage (end of stint)
    if ((driverStatus == DriverStatus::FLYING_LAP
    || driverStatus == DriverStatus::IN_LAP
    || driverStatus == DriverStatus::ON_TRACK)
    && newStatus == DriverStatus::IN_GARAGE) {
        // Delete current stint type activated
        emit StintEnded(currentStintType.value());
        currentStintType.reset();
        currentlyRecording = false;
    }

    // Driver has passed into the next lap, set that laps laptime and sectors, then make a new one
    if (currentLapNum < lapData.currentLapNum) {
        currentLap->set_lap_time(lapData.lastLapTimeInMS);
        currentLap->set_sector_1(lastLapData.sector1TimeInMS);
        currentLap->set_sector_2(lastLapData.sector2TimeInMS);
        currentLap->set_sector_3(lapData.lastLapTimeInMS - lastLapData.sector1TimeInMS - lastLapData.sector2TimeInMS);

        currentLap = currentStint->add_lap();
        currentLapNum = lapData.currentLapNum;
    }

    driverStatus = newStatus;
    currentDistance = lapData.lapDistance;
    lastLapData = lapData;

    addTelemetryDataToLap();
}

void RaceRecorder::handleEventPacket(const PacketData& packet) {
    if (!currentlyRecording) return;
}

void RaceRecorder::handleParticipantsPacket(const PacketData& packet) {
    if (!currentlyRecording) return;

    /*
    playerCarIndex should not change, however, rather than waste computation,
    we can just assign it each time
    */ 

    playerCarIndex = packet.header.playerCarIndex;
}

void RaceRecorder::handleCarSetupPacket(const PacketData& packet) {
    if (!currentlyRecording) return;

    const CarSetupData setupData = packet.packet.carSetupData.carSetups[playerCarIndex];

    currentSetup->set_front_wing(setupData.frontWing);
    currentSetup->set_rear_wing(setupData.rearWing);
    currentSetup->set_differential_on_throttle(setupData.onThrottle);
    currentSetup->set_differential_off_throttle(setupData.offThrottle);
    currentSetup->set_front_camber(setupData.frontCamber);
    currentSetup->set_rear_camber(setupData.rearCamber);
    currentSetup->set_front_toe(setupData.frontToe);
    currentSetup->set_rear_toe(setupData.rearToe);
    currentSetup->set_front_suspension(setupData.frontSuspension);
    currentSetup->set_rear_suspension(setupData.rearSuspension);
    currentSetup->set_front_anti_roll_bar(setupData.frontAntiRollBar);
    currentSetup->set_rear_anti_roll_bar(setupData.rearAntiRollBar);
    currentSetup->set_front_suspension_height(setupData.frontSuspensionHeight);
    currentSetup->set_rear_suspension_height(setupData.rearSuspensionHeight);
    currentSetup->set_brake_pressure(setupData.brakePressure);
    currentSetup->set_brake_bias(setupData.brakeBias);
    currentSetup->set_rear_left_tyre_pressure(setupData.rearLeftTyrePressure);
    currentSetup->set_rear_right_tyre_pressure(setupData.rearRightTyrePressure);
    currentSetup->set_front_left_tyre_pressure(setupData.frontLeftTyrePressure);
    currentSetup->set_front_right_tyre_pressure(setupData.frontRightTyrePressure);
    currentSetup->set_ballast(setupData.ballast);
    currentSetup->set_fuel_load(setupData.fuelLoad);

    // From Car Status
    currentSetup->set_fuel_capacity(lastStatusData.fuelCapacity);
    currentSetup->set_actual_tyre_compound(lastStatusData.actualTyreCompound);
    currentSetup->set_visual_tyre_compound(lastStatusData.visualTyreCompound);
}

void RaceRecorder::handleCarTelemetryPacket(const PacketData& packet) {
    if (!currentlyRecording) return;
    lastTelemetryData = packet.packet.carTelemetryData.carTelemetryData[playerCarIndex];
}

void RaceRecorder::handleCarStatusPacket(const PacketData& packet) {
    if (!currentlyRecording) return;
    lastStatusData = packet.packet.carStatusData.carStatusData[playerCarIndex];
}

void RaceRecorder::handleFinalClassificationPacket(const PacketData& packet) {
    if (!currentlyRecording) return;
}

void RaceRecorder::handleLobbyInfoPacket(const PacketData& packet) {
    if (!currentlyRecording) return;
}

void RaceRecorder::handleCarDamagePacket(const PacketData& packet) {
    if (!currentlyRecording) return;
    lastDamageData = packet.packet.carDamageData.carDamageData[playerCarIndex];
}

void RaceRecorder::handleSessionHistoryPacket(const PacketData& packet) {
    if (!currentlyRecording) return;
}


void RaceRecorder::addTelemetryDataToLap() {
    Telemetry t;
    // Telemetry Data
    t.set_speed(lastTelemetryData.speed);
    t.set_throttle(lastTelemetryData.throttle);
    t.set_steer(lastTelemetryData.steer);
    t.set_brake(lastTelemetryData.brake);
    t.set_clutch(lastTelemetryData.clutch);
    t.set_gear(lastTelemetryData.gear);
    t.set_engine_rpm(lastTelemetryData.engineRPM);
    t.set_drs(lastTelemetryData.drs);
    t.set_rev_lights_percent(lastTelemetryData.revLightsPercent);
    t.set_rev_lights_bit_value(lastTelemetryData.revLightsBitValue);

    t.set_rear_left_brake_temperature(lastTelemetryData.brakesTemperature[REAR_LEFT]);
    t.set_rear_right_brake_temperature(lastTelemetryData.brakesTemperature[REAR_RIGHT]);
    t.set_front_left_brake_temperature(lastTelemetryData.brakesTemperature[FRONT_LEFT]);
    t.set_front_right_brake_temperature(lastTelemetryData.brakesTemperature[FRONT_RIGHT]);

    t.set_rear_left_tyre_surface_temperature(lastTelemetryData.tyresSurfaceTemperature[REAR_LEFT]);
    t.set_rear_right_tyre_surface_temperature(lastTelemetryData.tyresSurfaceTemperature[REAR_RIGHT]);
    t.set_front_left_tyre_surface_temperature(lastTelemetryData.tyresSurfaceTemperature[FRONT_LEFT]);
    t.set_front_right_tyre_surface_temperature(lastTelemetryData.tyresSurfaceTemperature[FRONT_RIGHT]);

    t.set_rear_left_tyre_inner_temperature(lastTelemetryData.tyresInnerTemperature[REAR_LEFT]);
    t.set_rear_right_tyre_inner_temperature(lastTelemetryData.tyresInnerTemperature[REAR_RIGHT]);
    t.set_front_left_tyre_inner_temperature(lastTelemetryData.tyresInnerTemperature[FRONT_LEFT]);
    t.set_front_right_tyre_inner_temperature(lastTelemetryData.tyresInnerTemperature[FRONT_RIGHT]);

    t.set_engine_temperature(lastTelemetryData.engineTemperature);

    t.set_rear_left_tyre_pressure(lastTelemetryData.tyresPressure[REAR_LEFT]);
    t.set_rear_right_tyre_pressure(lastTelemetryData.tyresPressure[REAR_RIGHT]);
    t.set_front_left_tyre_pressure(lastTelemetryData.tyresPressure[FRONT_LEFT]);
    t.set_front_right_tyre_pressure(lastTelemetryData.tyresPressure[FRONT_RIGHT]);

    t.set_rear_left_surface_type(lastTelemetryData.surfaceType[REAR_LEFT]);
    t.set_rear_right_surface_type(lastTelemetryData.surfaceType[REAR_RIGHT]);
    t.set_front_left_surface_type(lastTelemetryData.surfaceType[FRONT_LEFT]);
    t.set_front_right_surface_type(lastTelemetryData.surfaceType[FRONT_RIGHT]);


    // Lap Data
    t.set_lap_distance(currentDistance);


    // Car Status
    t.set_fuel_in_tank(lastStatusData.fuelInTank);
    t.set_tyres_age_laps(lastStatusData.tyresAgeLaps);
    t.set_ers_store_energy(lastStatusData.ersStoreEnergy);
    t.set_ers_deploy_mode(lastStatusData.ersDeployMode);
    t.set_ers_harvested_this_lap_mguk(lastStatusData.ersHarvestedThisLapMGUK);
    t.set_ers_harvested_this_lap_mguh(lastStatusData.ersHarvestedThisLapMGUH);
    t.set_ers_deployed_this_lap(lastStatusData.ersDeployedThisLap);


    // Car Damaage
    t.set_rear_left_tyre_wear(lastDamageData.tyresWear[REAR_LEFT]);
    t.set_rear_right_tyre_wear(lastDamageData.tyresWear[REAR_RIGHT]);
    t.set_front_left_tyre_wear(lastDamageData.tyresWear[FRONT_LEFT]);
    t.set_front_right_tyre_wear(lastDamageData.tyresWear[FRONT_RIGHT]);

    t.set_rear_left_tyre_damage(lastDamageData.tyresDamage[REAR_LEFT]);
    t.set_rear_right_tyre_damage(lastDamageData.tyresDamage[REAR_RIGHT]);
    t.set_front_left_tyre_damage(lastDamageData.tyresDamage[FRONT_LEFT]);
    t.set_front_right_tyre_damage(lastDamageData.tyresDamage[FRONT_RIGHT]);

    t.set_gear_box_damage(lastDamageData.gearBoxDamage);
    t.set_engine_damage(lastDamageData.engineDamage);

    t.set_engine_ce_wear(lastDamageData.engineCEWear);
    t.set_engine_ice_wear(lastDamageData.engineICEWear);
    t.set_engine_tc_wear(lastDamageData.engineTCWear);
    t.set_engine_es_wear(lastDamageData.engineESWear);
    t.set_engine_mguh_wear(lastDamageData.engineMGUHWear);
    t.set_engine_mguk_wear(lastDamageData.engineMGUKWear);


    // Motion Data
    t.set_rear_left_suspension_position(lastMotionPacket.suspensionPosition[REAR_LEFT]);
    t.set_rear_right_suspension_position(lastMotionPacket.suspensionPosition[REAR_RIGHT]);
    t.set_front_left_suspension_position(lastMotionPacket.suspensionPosition[FRONT_LEFT]);
    t.set_front_right_suspension_position(lastMotionPacket.suspensionPosition[FRONT_RIGHT]);

    t.set_rear_left_wheel_speed(lastMotionPacket.wheelSpeed[REAR_LEFT]);
    t.set_rear_right_wheel_speed(lastMotionPacket.wheelSpeed[REAR_RIGHT]);
    t.set_front_left_wheel_speed(lastMotionPacket.wheelSpeed[FRONT_LEFT]);
    t.set_front_right_wheel_speed(lastMotionPacket.wheelSpeed[FRONT_RIGHT]);

    t.set_rear_left_wheel_slip(lastMotionPacket.wheelSpeed[REAR_LEFT]);
    t.set_rear_right_wheel_slip(lastMotionPacket.wheelSpeed[REAR_RIGHT]);
    t.set_front_left_wheel_slip(lastMotionPacket.wheelSpeed[FRONT_LEFT]);
    t.set_front_right_wheel_slip(lastMotionPacket.wheelSpeed[FRONT_RIGHT]);


    CarMotionData md = lastMotionPacket.carMotionData[playerCarIndex];

    t.set_world_position_x(md.worldPositionX);
    t.set_world_position_y(md.worldPositionY);
    t.set_world_position_z(md.worldPositionZ);

    t.set_g_force_lateral(md.gForceLateral);
    t.set_g_force_longitudinal(md.gForceLongitudinal);
    t.set_g_force_vertical(md.gForceVertical);

    t.set_yaw(md.yaw);
    t.set_pitch(md.pitch);
    t.set_roll(md.roll);

    currentLap->add_telemetry()->CopyFrom(t);
}

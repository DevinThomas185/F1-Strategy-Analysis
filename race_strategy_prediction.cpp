#include "race_strategy_prediction.hpp"
#include "analysis.hpp"
#include "packets.hpp"
#include "constants.h"

RaceStrategyPredictor::RaceStrategyPredictor(QObject *parent)
    : QObject{parent}
{

}

void RaceStrategyPredictor::predictStrategy(RaceWeekend raceWeekend, uint8_t raceLaps) {
    // Reset current strategy
    currentStrategy = {};

    totalRacingLaps = raceLaps;
    track = getTrackID(raceWeekend.track_id());

    // Initialise current strategy;
    currentStrategy.totalRacingLaps = totalRacingLaps;
    currentStrategy.currentLapNumber = currentLapNumber;
    // Lap 0 is 'before' lap 1, every lap maps to its index
    for (int i = 0; i <= totalRacingLaps; i++) {
        currentStrategy.perLapStrategy.push_back({
            .actual = {
                .lapTimeMS = 0,
                .fuelInTank = 0,
                .tyreCompound = ActualTyreCompound::C1,
                .tyreHealth = 0,
            },
            .predicted = {
                .lapTimeMS = 0,
                .fuelInTank = 0,
                .tyreCompound = ActualTyreCompound::C1,
                .tyreHealth = 0,
            }
        });
    }


//    mockPredictStrategy(raceWeekend);
    simplePredictStrategy(raceWeekend);
    geneticAlgorithmPredictStrategy(raceWeekend);

    strategyInitialised = true;

    emit StrategyUpdate(currentStrategy);
}

void RaceStrategyPredictor::mockPredictStrategy(RaceWeekend raceWeekend) {
    currentStrategy.perLapStrategy[0] = {
        .actual = {
            .lapTimeMS = 0,
            .fuelInTank = 0,
            .tyreCompound = ActualTyreCompound::C1,
            .tyreHealth = 100,
        },
        .predicted = {
            .lapTimeMS = 110000,
            .fuelInTank = 10,
            .tyreCompound = ActualTyreCompound::C1,
            .tyreHealth = 100,
        },
    };

    currentStrategy.perLapStrategy[1] = {
        .actual = {
            .lapTimeMS = 0,
            .fuelInTank = 0,
            .tyreCompound = ActualTyreCompound::C1,
            .tyreHealth = 97,
        },
        .predicted = {
            .lapTimeMS = 97000,
            .fuelInTank = 9,
            .tyreCompound = ActualTyreCompound::C2,
            .tyreHealth = 100,
        }
    };
}

ActualTyreCompound pickCompound(std::set<ActualTyreCompound> usedCompounds, TyreCompoundMap compoundMapping) {

    // Pick the softest compound if not already used
    if (!usedCompounds.contains(compoundMapping.getSoftTyre())) return compoundMapping.getSoftTyre();
    if (!usedCompounds.contains(compoundMapping.getMediumTyre())) return compoundMapping.getMediumTyre();
    if (!usedCompounds.contains(compoundMapping.getHardTyre())) return compoundMapping.getHardTyre();

    return compoundMapping.getMediumTyre(); // Otherwise, use the medium tyre
}

bool pitstopRequired(uint8_t totalRacingLaps, uint8_t currentLap, float tyreHealth, TyreCompoundMap compoundMapping,  std::set<ActualTyreCompound> usedCompounds) {
    // If first set of tyres not selected yet
    if (currentLap == 0) return true;

    // If the tyres are too worn out
    if (tyreHealth < 50) return true;

    // If not in a Quickfire or Very Short race and we are at the penultimate lap
    if (totalRacingLaps > 5 && (currentLap == totalRacingLaps - 1)) {
        // Either mediums or hard tyres not used yet
        if (!usedCompounds.contains(compoundMapping.getMediumTyre()) || !usedCompounds.contains(compoundMapping.getHardTyre())) return true;

        // Not yet completed one pitstop
        if (usedCompounds.size() < 2) return true;
    }

    return false;
}

void RaceStrategyPredictor::simplePredictStrategy(RaceWeekend raceWeekend) {

    // Determine degradation and fuel usage for each race simulation stint generated across all practice sessions
    std::map<ActualTyreCompound, std::vector<float>> fuelRegressions;
    std::map<ActualTyreCompound, std::vector<float>> tyreDegradationRegressions;
    std::map<ActualTyreCompound, std::vector<double>> lapTimeRegressions;
    std::map<ActualTyreCompound, std::vector<double>> lapTimesPerTyre;

    TyreCompoundMap compoundMapping;

    Practice practices[3] = {
        raceWeekend.race_sessions().fp1(),
        raceWeekend.race_sessions().fp2(),
        raceWeekend.race_sessions().fp3(),
    };

    // For each practice
    for (auto practice : practices) {
        // For each race simulation stint
        for (int i = 0; i < practice.race_simulation_size(); i++) {
            Stint raceSimulation = practice.race_simulation()[i];

            std::vector<double>fuelUsageValues;
            std::vector<double>tyreDegradationValues;
            std::vector<double>lapDistanceValues;

            std::vector<double>lapTimeValues;
            std::vector<double>lapNumberValues;
            int lapNumber = 1;

            float l = 0; // l represents the total distance travelled in the stint

            ActualTyreCompound tyreCompound = getActualTyreCompound(raceSimulation.setup().actual_tyre_compound());
            VisualTyreCompound visualCompound = getVisualTyreCompound(raceSimulation.setup().visual_tyre_compound());

            if (!compoundMapping.exists()) compoundMapping.setMap(tyreCompound, visualCompound);

            // For each lap in the stint
            for (const Lap &lap : raceSimulation.lap()) {
                // IN LAP has no lap time but lap exists in recording TODO: Remove this?
                if (lap.lap_time() == 0) continue;

                lapTimesPerTyre[tyreCompound].push_back(lap.lap_time());
                lapTimeValues.push_back(lap.lap_time());
                lapNumberValues.push_back(lapNumber++);

                // For all telemetry in the lap
                for (const Telemetry &t : lap.telemetry()) {
                    fuelUsageValues.push_back(t.fuel_in_tank());
                    tyreDegradationValues.push_back(t.rear_left_tyre_damage()); // TODO: CHANGE TO BE AN AVERAGE OF ALL TYRE'S DEGRADATIONS OR MINIMUM OF THE 4
                    lapDistanceValues.push_back(l + t.lap_distance());
                }
                l += raceWeekend.track_length();
            }

            LinearRegressionResult fuelRegression = calculateLinearRegression(lapDistanceValues, fuelUsageValues);
            LinearRegressionResult tyreRegression = calculateLinearRegression(lapDistanceValues, tyreDegradationValues);
            LinearRegressionResult lapTimeRegression = calculateLinearRegression(lapNumberValues, lapTimeValues);


            // Negate to keep value as amount of fuel used per lap
            fuelRegressions[tyreCompound].push_back(- fuelRegression.gradient * raceWeekend.track_length()); // TODO: Should also be per tyre fuel regressions?
            tyreDegradationRegressions[tyreCompound].push_back(tyreRegression.gradient * raceWeekend.track_length());
            lapTimeRegressions[tyreCompound].push_back(lapTimeRegression.gradient);
        }
    }

    std::map<ActualTyreCompound, float> averageFuelRegressions;
    std::map<ActualTyreCompound, float> averageTyreDegradationRegressions;
    std::map<ActualTyreCompound, double> averageLapTimeRegressions;
    std::map<ActualTyreCompound, float> lapTimeStdDeviations;

    for (const auto &fr : fuelRegressions) {
        averageFuelRegressions[fr.first] = std::accumulate(fr.second.begin(), fr.second.end(), 0.0) / fr.second.size();
    }

    for (const auto &tdr : tyreDegradationRegressions) {
        averageTyreDegradationRegressions[tdr.first] = std::accumulate(tdr.second.begin(), tdr.second.end(), 0.0) / tdr.second.size();
    }

    for (const auto &ltr : lapTimeRegressions) {
        averageLapTimeRegressions[ltr.first] = std::accumulate(ltr.second.begin(), ltr.second.end(), 0.0) / ltr.second.size();
    }

    for (const auto &ltpt : lapTimesPerTyre) {
        lapTimeStdDeviations[ltpt.first] = standard_deviation(ltpt.second);
    }


    int currentLap = 0;

    float tyreHealth = 100;
    float totalFuelLeft = 110; // Maximum amount of fuel that can go in the car
    uint32_t predictedLapTime = StrategyConstants::averageLapTimeDefaults.at(getTrackID(raceWeekend.track_id()));

    std::set<ActualTyreCompound> usedCompounds;
    ActualTyreCompound currentCompound;

    while (currentLap <= totalRacingLaps) {
        bool isPitLap = false;

        // If on first lap or tyres degraded too much, or not used two tyre sets yet
        if (pitstopRequired(totalRacingLaps, currentLap, tyreHealth, compoundMapping, usedCompounds)) {
            isPitLap = true;
            currentCompound = pickCompound(usedCompounds, compoundMapping);
            usedCompounds.insert(currentCompound);
            tyreHealth = 100;

            predictedLapTime = StrategyConstants::averageLapTimeDefaults.at(getTrackID(raceWeekend.track_id())) + StrategyConstants::tyreDefaults.at(currentCompound).averageLapTimeDelta;
        }

        // Default values if tyre wasn't tested with
        float fuelUsage = StrategyConstants::tyreDefaults.at(currentCompound).fuelUsage;
        float tyreDegradation = StrategyConstants::tyreDefaults.at(currentCompound).tyreDegradation;
        uint32_t lapTimeIncrease = StrategyConstants::tyreDefaults.at(currentCompound).lapTimeIncrease;

        // TODO: when putting all three into one map, change this (currently, all should contain the same tyre compounds)
        if (averageFuelRegressions.contains(currentCompound)) {
            fuelUsage = averageFuelRegressions[currentCompound];
            tyreDegradation = averageTyreDegradationRegressions[currentCompound];
            lapTimeIncrease = averageLapTimeRegressions[currentCompound];
        }

        currentStrategy.perLapStrategy[currentLap].predicted.fuelInTank = totalFuelLeft;
        currentStrategy.perLapStrategy[currentLap].predicted.lapTimeMS = isPitLap ? predictedLapTime + StrategyConstants::PITSTOP_LAPTIME_INCREASE : predictedLapTime;

        currentStrategy.perLapStrategy[currentLap].predicted.tyreCompound = currentCompound;
        currentStrategy.perLapStrategy[currentLap].predicted.tyreHealth = tyreHealth;

        // Add to the total predicted race time
        currentStrategy.predictedRaceTime += predictedLapTime;
        currentStrategy.predictedRaceTimeUncertainty += lapTimeStdDeviations[currentCompound];

        tyreHealth -= tyreDegradation;
        predictedLapTime += lapTimeIncrease; // predicted lap times are not correct
        totalFuelLeft -= fuelUsage;

        currentLap++;
    }

    // Correct fuel to be minimum required
    float fuelOnLastLap = currentStrategy.perLapStrategy[totalRacingLaps].predicted.fuelInTank;
    for (int i = 0; i <= totalRacingLaps; i++) {
        currentStrategy.perLapStrategy[i].predicted.fuelInTank -= (fuelOnLastLap - StrategyConstants::MINIMUM_FUEL_LEVEL);
    }

    currentStrategy.startingFuelLoad = currentStrategy.perLapStrategy[0].predicted.fuelInTank;
    currentStrategy.compoundMapping = compoundMapping;
}

void RaceStrategyPredictor::geneticAlgorithmPredictStrategy(RaceWeekend raceWeekend) {
    
}

void RaceStrategyPredictor::updateStrategy() {
    emit StrategyUpdate(currentStrategy);
}


void RaceStrategyPredictor::handleMotionPacket(const PacketData &packet) {
    if (!strategyInitialised) return;
    updateStrategy();
}
void RaceStrategyPredictor::handleSessionPacket(const PacketData &packet) {}

void RaceStrategyPredictor::handleLapPacket(const PacketData &packet) {
    if (!strategyInitialised) return;

    const PacketLapData lapData = packet.packet.lapData;
    uint8_t playerCarIndex = packet.header.playerCarIndex;
    LapData ld = lapData.lapData[playerCarIndex];

    // Change of lap number
    if (ld.currentLapNum != currentLapNumber) {
        // If fuel and tyres not yet set, don't record the starting values and update the lap number
        if (currentLapNumber == 0 && (currentFuelInTank == 0 || currentTyreHealth == 0)) return;

        currentStrategy.perLapStrategy[currentLapNumber].actual.lapTimeMS = ld.lastLapTimeInMS;
        currentStrategy.perLapStrategy[currentLapNumber].actual.fuelInTank = currentFuelInTank;
        currentStrategy.perLapStrategy[currentLapNumber].actual.tyreHealth = currentTyreHealth;

        currentLapNumber = ld.currentLapNum;
        currentStrategy.currentLapNumber = currentLapNumber;

    }
}

void RaceStrategyPredictor::handleEventPacket(const PacketData &packet) {}
void RaceStrategyPredictor::handleParticipantsPacket(const PacketData &packet) {}
void RaceStrategyPredictor::handleCarSetupPacket(const PacketData &packet) {}
void RaceStrategyPredictor::handleCarTelemetryPacket(const PacketData &packet) {}

void RaceStrategyPredictor::handleCarStatusPacket(const PacketData &packet) {
    if (!strategyInitialised) return;

    const PacketCarStatusData statusData = packet.packet.carStatusData;
    uint8_t playerCarIndex = packet.header.playerCarIndex;
    CarStatusData csd = statusData.carStatusData[playerCarIndex];

    currentFuelInTank = csd.fuelInTank;
}


void RaceStrategyPredictor::handleFinalClassificationPacket(const PacketData &packet) {}
void RaceStrategyPredictor::handleLobbyInfoPacket(const PacketData &packet) {}

void RaceStrategyPredictor::handleCarDamagePacket(const PacketData &packet) {
    if (!strategyInitialised) return;

    const PacketCarDamageData damageData = packet.packet.carDamageData;
    uint8_t playerCarIndex = packet.header.playerCarIndex;
    CarDamageData csd = damageData.carDamageData[playerCarIndex];

    currentTyreHealth = 100 - std::min({csd.tyresDamage[REAR_LEFT],
                                        csd.tyresDamage[REAR_RIGHT],
                                        csd.tyresDamage[FRONT_LEFT],
                                        csd.tyresDamage[FRONT_RIGHT]});

}


void RaceStrategyPredictor::handleSessionHistoryPacket(const PacketData &packet) {}

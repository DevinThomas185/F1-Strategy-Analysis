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
    for (int i = 0; i < totalRacingLaps; i++) {
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

void RaceStrategyPredictor::simplePredictStrategy(RaceWeekend raceWeekend) {

    // Determine degradation and fuel usage for each race simulation stint generated across all practice sessions
    std::map<ActualTyreCompound, std::vector<float>> fuelRegressions;
    std::map<ActualTyreCompound, std::vector<float>> tyreDegradationRegressions;
    std::map<ActualTyreCompound, std::vector<double>> lapTimeRegressions;
    std::map<ActualTyreCompound, std::vector<double>> lapTimesPerTyre;

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

            // For each lap in the stint
            for (Lap lap : raceSimulation.lap()) {
                // IN LAP has no lap time but lap exists in recording TODO: Remove this?
                if (lap.lap_time() == 0) continue;

                lapTimesPerTyre[tyreCompound].push_back(lap.lap_time());
                lapTimeValues.push_back(lap.lap_time());
                lapNumberValues.push_back(lapNumber++);
                // For all telemetry in the lap
                for (Telemetry t : lap.telemetry()) {
                    fuelUsageValues.push_back(t.fuel_in_tank());
                    tyreDegradationValues.push_back(t.rear_left_tyre_damage()); // TODO: CHANGE TO BE AN AVERAGE OF ALL TYRE'S DEGRADATIONS
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
    uint32_t predictedLapTime = StrategyConstants::averageLapTimeDefaults.at(getTrackID(raceWeekend.track_id()));

    std::set<ActualTyreCompound> usedCompounds; // TODO: Should this be a set?
    ActualTyreCompound currentCompound;


    currentStrategy = bruteForceFastestStrategy(currentStrategy, 0);


//    while (currentLap < totalRacingLaps) {
//        bool isPitLap = false;

//        // If on first lap or tyres degraded too much, or not used two tyre sets yet
//        if (currentLap == 0 || tyreHealth < 40 || (usedCompounds.size() < 2 && currentLap == totalRacingLaps-2)) {
//            isPitLap = true;
//            currentCompound = usedCompounds.contains(currentCompound) ? ActualTyreCompound::C2 : ActualTyreCompound::C3;
//            usedCompounds.insert(currentCompound);
//            tyreHealth = 100;

//            predictedLapTime = StrategyConstants::averageLapTimeDefaults.at(getTrackID(raceWeekend.track_id())) + StrategyConstants::tyreDefaults.at(currentCompound).averageLapTimeDelta;
//        }

//        // Default values if tyre wasn't tested with
//        float fuelUsage = StrategyConstants::tyreDefaults.at(currentCompound).fuelUsage;
//        float tyreDegradation = StrategyConstants::tyreDefaults.at(currentCompound).tyreDegradation;
//        uint32_t lapTimeIncrease = StrategyConstants::tyreDefaults.at(currentCompound).lapTimeIncrease;

//        // TODO: when putting all three into one map, change this (currently, all should contain the same tyre compounds)
//        if (averageFuelRegressions.contains(currentCompound)) {
//            fuelUsage = averageFuelRegressions[currentCompound];
//            tyreDegradation = averageTyreDegradationRegressions[currentCompound];
//            lapTimeIncrease = averageLapTimeRegressions[currentCompound];
//        }

//        currentStrategy.perLapStrategy[currentLap].predicted.fuelInTank = fuelUsage * (totalRacingLaps - currentLap) + StrategyConstants::MINIMUM_FUEL_LEVEL;
//        currentStrategy.perLapStrategy[currentLap].predicted.lapTimeMS = isPitLap ? predictedLapTime + StrategyConstants::PITSTOP_LAPTIME_INCREASE : predictedLapTime;

//        currentStrategy.perLapStrategy[currentLap].predicted.tyreCompound = currentCompound;
//        currentStrategy.perLapStrategy[currentLap].predicted.tyreHealth = tyreHealth;

//        // Add to the total predicted race time
//        currentStrategy.predictedRaceTime += predictedLapTime;
//        currentStrategy.predictedRaceTimeUncertainty += lapTimeStdDeviations[currentCompound];

//        tyreHealth -= tyreDegradation;
//        predictedLapTime += lapTimeIncrease; // predicted lap times are not correct

//        currentLap++;
//    }
}

bool compareStrategies(Strategy a, Strategy b) {
    return a.predictedRaceTime < b.predictedRaceTime;
}

Strategy pitToTyre(ActualTyreCompound newTyre, uint8_t currentLap, Strategy strategy, TrackID track) {
    strategy.perLapStrategy[currentLap].predicted.tyreCompound = newTyre;
    strategy.perLapStrategy[currentLap].predicted.tyreHealth = 100;
    strategy.perLapStrategy[currentLap].predicted.fuelInTank = strategy.perLapStrategy[currentLap-1].predicted.fuelInTank - StrategyConstants::tyreDefaults.at(newTyre).fuelUsage;;
    strategy.perLapStrategy[currentLap].predicted.lapTimeMS = StrategyConstants::averageLapTimeDefaults.at(track) + StrategyConstants::tyreDefaults.at(newTyre).averageLapTimeDelta + StrategyConstants::PITSTOP_LAPTIME_INCREASE;
    strategy.predictedRaceTime += strategy.perLapStrategy[currentLap].predicted.lapTimeMS;
    return strategy;
}

Strategy noPitStop(uint8_t currentLap, Strategy strategy) {
    ActualTyreCompound currentCompound = strategy.perLapStrategy[currentLap-1].predicted.tyreCompound;
    strategy.perLapStrategy[currentLap].predicted.tyreCompound = currentCompound;
    strategy.perLapStrategy[currentLap].predicted.tyreHealth = strategy.perLapStrategy[currentLap-1].predicted.tyreHealth - StrategyConstants::tyreDefaults.at(currentCompound).tyreDegradation;
    strategy.perLapStrategy[currentLap].predicted.fuelInTank = strategy.perLapStrategy[currentLap-1].predicted.fuelInTank - StrategyConstants::tyreDefaults.at(currentCompound).fuelUsage;
    strategy.perLapStrategy[currentLap].predicted.lapTimeMS = strategy.perLapStrategy[currentLap-1].predicted.lapTimeMS + StrategyConstants::tyreDefaults.at(currentCompound).lapTimeIncrease;
    strategy.predictedRaceTime += strategy.perLapStrategy[currentLap].predicted.lapTimeMS;
    return strategy;
}

Strategy RaceStrategyPredictor::bruteForceFastestStrategy(Strategy strategy, uint8_t currentLap) {

    if (currentLap == 3) {
        return currentStrategy;
    }

    Strategy pitToC5 = bruteForceFastestStrategy(pitToTyre(ActualTyreCompound::C5, currentLap, strategy, track), currentLap+1);
    Strategy pitToC4 = bruteForceFastestStrategy(pitToTyre(ActualTyreCompound::C4, currentLap, strategy, track), currentLap+1);
    Strategy pitToC3 = bruteForceFastestStrategy(pitToTyre(ActualTyreCompound::C3, currentLap, strategy, track), currentLap+1);
    Strategy pitToC2 = bruteForceFastestStrategy(pitToTyre(ActualTyreCompound::C2, currentLap, strategy, track), currentLap+1);
    Strategy pitToC1 = bruteForceFastestStrategy(pitToTyre(ActualTyreCompound::C1, currentLap, strategy, track), currentLap+1);
    Strategy pitToInter = bruteForceFastestStrategy(pitToTyre(ActualTyreCompound::INTER, currentLap, strategy, track), currentLap+1);
    Strategy pitToWet = bruteForceFastestStrategy(pitToTyre(ActualTyreCompound::WET, currentLap, strategy, track), currentLap+1);

    if (currentLap == 0) {
        return std::min({pitToC5, pitToC4, pitToC3, pitToC2, pitToC2, pitToInter, pitToWet}, compareStrategies);
    } else {
        Strategy noPit = bruteForceFastestStrategy(noPitStop(currentLap, strategy), currentLap+1);
        return std::min({pitToC5, pitToC4, pitToC3, pitToC2, pitToC1, pitToInter, pitToWet, noPit}, compareStrategies);
    }

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
        if (currentLapNumber > 0) {
            currentStrategy.perLapStrategy[currentLapNumber - 1].actual.lapTimeMS = ld.lastLapTimeInMS;
        }

        currentLapNumber = ld.currentLapNum;
        currentStrategy.currentLapNumber = currentLapNumber;

    }
}

void RaceStrategyPredictor::handleEventPacket(const PacketData &packet) {}
void RaceStrategyPredictor::handleParticipantsPacket(const PacketData &packet) {}
void RaceStrategyPredictor::handleCarSetupPacket(const PacketData &packet) {}
void RaceStrategyPredictor::handleCarTelemetryPacket(const PacketData &packet) {}
void RaceStrategyPredictor::handleCarStatusPacket(const PacketData &packet) {}
void RaceStrategyPredictor::handleFinalClassificationPacket(const PacketData &packet) {}
void RaceStrategyPredictor::handleLobbyInfoPacket(const PacketData &packet) {}
void RaceStrategyPredictor::handleCarDamagePacket(const PacketData &packet) {}
void RaceStrategyPredictor::handleSessionHistoryPacket(const PacketData &packet) {}

#include "race_strategy_prediction.hpp"
#include "analysis.hpp"
#include "packets.hpp"

#define MINIMUM_FUEL_LEVEL 3

RaceStrategyPredictor::RaceStrategyPredictor(QObject *parent)
    : QObject{parent}
{

}

void RaceStrategyPredictor::predictStrategy(RaceWeekend raceWeekend, uint8_t raceLaps) {
    // Reset current strategy
    currentStrategy = {};

    totalRacingLaps = raceLaps;

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
    std::vector<float> predictedFuelRegressions;
    std::map<ActualTyreCompound, std::vector<float>> tyreDegradationRegressions;

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

            float l = 0; // l represents the total distance travelled in the stint

            // For each lap in the stint
            for (Lap lap : raceSimulation.lap()) {
                // For all telemetry in the lap
                for (Telemetry t : lap.telemetry()) {
                    fuelUsageValues.push_back(t.fuel_in_tank());
                    tyreDegradationValues.push_back(t.rear_left_tyre_damage());// TODO: CHANGE TO BE AN AVERAGE OF ALL TYRE'S DEGRADATIONS
                    lapDistanceValues.push_back(l + t.lap_distance());
                }
                l += raceWeekend.track_length();
            }

            LinearRegressionResult predictedFuelRegression = calculateLinearRegression(lapDistanceValues, fuelUsageValues);
            LinearRegressionResult tyreRegression = calculateLinearRegression(lapDistanceValues, tyreDegradationValues);

            // Negate to keep value as amount of fuel used per lap
            predictedFuelRegressions.push_back(- predictedFuelRegression.gradient * raceWeekend.track_length());
            tyreDegradationRegressions[getActualTyreCompound(raceSimulation.setup().actual_tyre_compound())].push_back(tyreRegression.gradient * raceWeekend.track_length());
        }
    }

    float averageFuelRegression = std::accumulate(predictedFuelRegressions.begin(), predictedFuelRegressions.end(), 0.0) / predictedFuelRegressions.size();

    int lastPitLap = 0;
    ActualTyreCompound currentCompound = ActualTyreCompound::C3;
    std::vector<ActualTyreCompound> usedCompounds = {currentCompound};

    for (int i = 0; i < totalRacingLaps; i++) {
        // Amount of fuel per lap
        currentStrategy.perLapStrategy[i].predicted.fuelInTank = averageFuelRegression * (totalRacingLaps - i) + MINIMUM_FUEL_LEVEL;
        currentStrategy.perLapStrategy[i].predicted.lapTimeMS = 100000;

        float tyreHealth = 100 - (tyreDegradationRegressions[currentCompound][0] * (i - lastPitLap)); //TODO: Should not be from 0, needs to be average

        currentStrategy.perLapStrategy[i].predicted.tyreCompound = currentCompound;
        currentStrategy.perLapStrategy[i].predicted.tyreHealth = tyreHealth;

        // If less than 40% tyre health, change tyres for next lap
        if (tyreHealth < 40) {
            currentCompound = ActualTyreCompound::C3;
            lastPitLap = i;
            usedCompounds.push_back(currentCompound);
        }



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

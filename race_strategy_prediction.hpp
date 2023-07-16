#ifndef RACE_STRATEGY_PREDICTION_HPP
#define RACE_STRATEGY_PREDICTION_HPP

#include "compiled_protos/RaceWeekend.pb.h"
#include "packet_handler.hpp"
#include "enums.hpp"
#include <QObject>

class TyreCompoundMap {
public:

    void setMap(ActualTyreCompound actual, VisualTyreCompound visual) {
        if ((actual == ActualTyreCompound::C1 && visual == VisualTyreCompound::HARD_VISUAL)
            || (actual == ActualTyreCompound::C2 && visual == VisualTyreCompound::MEDIUM_VISUAL)
            || (actual == ActualTyreCompound::C3 && visual == VisualTyreCompound::SOFT_VISUAL)) {
            hardTyreCompound = ActualTyreCompound::C1;
            mediumTyreCompound = ActualTyreCompound::C2;
            softTyreCompound = ActualTyreCompound::C3;
        }

        if ((actual == ActualTyreCompound::C2 && visual == VisualTyreCompound::HARD_VISUAL)
            || (actual == ActualTyreCompound::C3 && visual == VisualTyreCompound::MEDIUM_VISUAL)
            || (actual == ActualTyreCompound::C4 && visual == VisualTyreCompound::SOFT_VISUAL)) {
            hardTyreCompound = ActualTyreCompound::C2;
            mediumTyreCompound = ActualTyreCompound::C3;
            softTyreCompound = ActualTyreCompound::C4;
        }

        if ((actual == ActualTyreCompound::C3 && visual == VisualTyreCompound::HARD_VISUAL)
            || (actual == ActualTyreCompound::C4 && visual == VisualTyreCompound::MEDIUM_VISUAL)
            || (actual == ActualTyreCompound::C5 && visual == VisualTyreCompound::SOFT_VISUAL)) {
            hardTyreCompound = ActualTyreCompound::C3;
            mediumTyreCompound = ActualTyreCompound::C4;
            softTyreCompound = ActualTyreCompound::C5;
        }

        mapExists = true;
    }

    ActualTyreCompound getHardTyre() {
        return hardTyreCompound;
    }

    ActualTyreCompound getMediumTyre() {
        return mediumTyreCompound;
    }

    ActualTyreCompound getSoftTyre() {
        return softTyreCompound;
    }

    VisualTyreCompound getVisualTyreCompound(ActualTyreCompound actual) {
        if (actual == hardTyreCompound) return VisualTyreCompound::HARD_VISUAL;
        if (actual == mediumTyreCompound) return VisualTyreCompound::MEDIUM_VISUAL;
        if (actual == softTyreCompound) return VisualTyreCompound::SOFT_VISUAL;
        if (actual == ActualTyreCompound::INTER) return VisualTyreCompound::INTER_VISUAL;
        if (actual == ActualTyreCompound::WET) return VisualTyreCompound::WET_VISUAL;

        return VisualTyreCompound::HARD_VISUAL; // Default
    }

    bool exists() {
        return mapExists;
    }

private:
    bool mapExists = false;
    ActualTyreCompound hardTyreCompound;
    ActualTyreCompound mediumTyreCompound;
    ActualTyreCompound softTyreCompound;

};

struct LapDetails {
    uint32_t lapTimeMS;
    float fuelInTank;
    ActualTyreCompound tyreCompound;
    float tyreHealth;
};

struct LapStrategy
{
    LapDetails actual;
    LapDetails predicted;
};

struct Strategy
{
    uint8_t totalRacingLaps;
    uint8_t currentLapNumber;
    uint32_t predictedRaceTime;
    uint32_t predictedRaceTimeUncertainty;
    float startingFuelLoad;
    TyreCompoundMap compoundMapping;
    std::vector<LapStrategy> perLapStrategy;

    bool isPitLap(int lapNumber) {
        lapNumber--; // Make 0 indexed

        // Lap is a pit lap if the tyre compound changes for the next lap, or the tyre compound is the same, but the health
        // is higher, meaning a pitstop has occurred.
        return (perLapStrategy[lapNumber].predicted.tyreCompound != perLapStrategy[lapNumber + 1].predicted.tyreCompound) ||
               (perLapStrategy[lapNumber].predicted.tyreHealth < perLapStrategy[lapNumber + 1].predicted.tyreHealth);
    }

    uint8_t nextPitStop() {
        size_t start = currentLapNumber == 0 ? 1 : currentLapNumber;
        for (size_t i = start; i <= totalRacingLaps; i++) {
            if (isPitLap(i)) return i;
        }
        return 0;
    }
};

class RaceStrategyPredictor : public QObject, public PacketHandlerInterface {
    Q_OBJECT
public:
    explicit RaceStrategyPredictor(QObject *parent = nullptr);

    void handleMotionPacket(const PacketData &packet);
    void handleSessionPacket(const PacketData &packet);
    void handleLapPacket(const PacketData &packet);
    void handleEventPacket(const PacketData &packet);
    void handleParticipantsPacket(const PacketData &packet);
    void handleCarSetupPacket(const PacketData &packet);
    void handleCarTelemetryPacket(const PacketData &packet);
    void handleCarStatusPacket(const PacketData &packet);
    void handleFinalClassificationPacket(const PacketData &packet);
    void handleLobbyInfoPacket(const PacketData &packet);
    void handleCarDamagePacket(const PacketData &packet);
    void handleSessionHistoryPacket(const PacketData &packet);

    /**
     * @brief Predict the initial race strategy using the race weekend data generated
     * during the practice sessions
     *
     * @param[in] raceWeekend The race weekend data loaded from the protobuf file
     * @param[in] raceLaps  The number of laps to be completed in the race
     */
    void predictStrategy(RaceWeekend raceWeekend, uint8_t raceLaps);
    
    /**
     * @brief Update the current strategy using the live data coming from the game
     * 
     */
    void updateStrategy();

    /**
     * @brief Get the current strategy prediction being run
     * 
     */
    Strategy getStrategy() {
        return currentStrategy;
    };

private:
    TrackID track;
    uint8_t totalRacingLaps = 0;
    bool strategyInitialised = false;
    Strategy currentStrategy;
    uint8_t currentLapNumber = 0;

    float currentFuelInTank;
    float currentTyreHealth;

    void mockPredictStrategy(RaceWeekend);
    void simplePredictStrategy(RaceWeekend);
    Strategy bruteForceFastestStrategy(Strategy currentStrategy, uint8_t currentLap);

signals:
    void StrategyUpdate(Strategy);
};

#endif  // RACE_STRATEGY_PREDICTION_HPP

#ifndef RACE_STRATEGY_PREDICTION_HPP
#define RACE_STRATEGY_PREDICTION_HPP

#include "compiled_protos/RaceWeekend.pb.h"
#include "packet_handler.hpp"
#include "enums.hpp"
#include <QObject>

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
    std::vector<LapStrategy> perLapStrategy;

    bool isPitLap(int lapNumber) {
        lapNumber--; // Make 0 indexed

        // Lap is a pit lap if the tyre compound changes for the next lap, or the tyre compound is the same, but the health
        // is higher, meaning a pitstop has occurred.
        return (perLapStrategy[lapNumber].predicted.tyreCompound != perLapStrategy[lapNumber + 1].predicted.tyreCompound) ||
               (perLapStrategy[lapNumber].predicted.tyreHealth < perLapStrategy[lapNumber + 1].predicted.tyreHealth);
    }

    uint8_t nextPitStop() {
        for (size_t i = currentLapNumber; i <= totalRacingLaps; i++) {
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
    void predictStrategy(RaceWeekend, uint8_t);

    void mockPredictStrategy(RaceWeekend);
    void simplePredictStrategy(RaceWeekend);

    
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
    uint8_t totalRacingLaps = 0;
    bool strategyInitialised = false;
    Strategy currentStrategy;
    uint8_t currentLapNumber = 1; // TODO: THIS IS NOT GETTING UPDATED ANYWHERE ?!!

signals:
    void StrategyUpdate(Strategy);
};

#endif  // RACE_STRATEGY_PREDICTION_HPP

#include "race_strategy_prediction.hpp"
#include "packets.hpp"

RaceStrategyPredictor::RaceStrategyPredictor(QObject *parent)
    : QObject{parent}
{

}

void RaceStrategyPredictor::predictStrategy(RaceWeekend raceWeekend) {
    currentStrategy = {
        .currentLapNumber = currentLapNumber,
        .perLapStrategy = {
            {
                .actualLapTimeMS = 0,
                .targetLapTimeMS = 95000,
                .tyreCompound = ActualTyreCompound::C1,
            },
            {
                .actualLapTimeMS = 0,
                .targetLapTimeMS = 95100,
                .tyreCompound = ActualTyreCompound::C1,
            },
            {
                .actualLapTimeMS = 0,
                .targetLapTimeMS = 95200,
                .tyreCompound = ActualTyreCompound::C2,
            },
            {
                .actualLapTimeMS = 0,
                .targetLapTimeMS = 95300,
                .tyreCompound = ActualTyreCompound::C2,
            },
            {
                .actualLapTimeMS = 0,
                .targetLapTimeMS = 95400,
                .tyreCompound = ActualTyreCompound::C2,
            },
        }
    };
    strategyInitialised = true;
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
            currentStrategy.perLapStrategy[currentLapNumber - 1].actualLapTimeMS = ld.lastLapTimeInMS;
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

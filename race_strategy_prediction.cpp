#include "race_strategy_prediction.hpp"

RaceStrategyPredictor::RaceStrategyPredictor(QObject *parent)
    : QObject{parent}
{

}

void RaceStrategyPredictor::predictStrategy(RaceWeekend raceWeekend) {
    currentStrategy = {
        .currentLapNumber = currentLapNumber,
        .perLapStrategy = {
            {
                .targetLapTimeMS = 95000,
                .tyreCompound = ActualTyreCompound::C1,
            },
            {
                .targetLapTimeMS = 95100,
                .tyreCompound = ActualTyreCompound::C1,
            },
            {
                .targetLapTimeMS = 95200,
                .tyreCompound = ActualTyreCompound::C2,
            },
            {
                .targetLapTimeMS = 95300,
                .tyreCompound = ActualTyreCompound::C2,
            },
            {
                .targetLapTimeMS = 95400,
                .tyreCompound = ActualTyreCompound::C2,
            },
        }
    };
    strategyInitialised = true;
}

void RaceStrategyPredictor::updateStrategy() {
    StrategyUpdate(currentStrategy);
}


void RaceStrategyPredictor::handleMotionPacket(const PacketData &packet) {
    if (!strategyInitialised) return;
    updateStrategy();
}
void RaceStrategyPredictor::handleSessionPacket(const PacketData &packet) {}

void RaceStrategyPredictor::handleLapPacket(const PacketData &packet) {
    currentStrategy.currentLapNumber = packet.packet.lapData.lapData[packet.header.playerCarIndex].currentLapNum;
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

#include "race_strategy_prediction.h"

RaceStrategyPredictor::RaceStrategyPredictor() {}

RaceStrategyPredictor::~RaceStrategyPredictor() {}

void RaceStrategyPredictor::predictStrategy(RaceWeekend raceWeekend) {
    currentStrategy = {
        .perLapStrategy = {
            {
                .targetLapTimeMS = 95000,
                .tyreCompound = ActualTyreCompound::C1,
            },
            {
                .targetLapTimeMS = 95100,
                .tyreCompound = ActualTyreCompound::C2,
            },
            {
                .targetLapTimeMS = 95200,
                .tyreCompound = ActualTyreCompound::C3,
            },
            {
                .targetLapTimeMS = 95300,
                .tyreCompound = ActualTyreCompound::C4,
            },
            {
                .targetLapTimeMS = 95400,
                .tyreCompound = ActualTyreCompound::C5,
            },
        }
    };
}

void RaceStrategyPredictor::updateStrategy() {

}

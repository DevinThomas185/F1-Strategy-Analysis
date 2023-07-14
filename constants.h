#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "enums.hpp"
#include <map>

namespace StrategyConstants {

const int MINIMUM_FUEL_LEVEL = 3;
const int PITSTOP_LAPTIME_INCREASE = 20000; // 20,000 MS = 20 Seconds

struct TyreDefaults {
    float fuelUsage;
    float tyreDegradation;
    uint32_t lapTimeIncrease;
    uint32_t averageLapTimeDelta;
};

// TODO: Improve these default values
const std::map<ActualTyreCompound, TyreDefaults> tyreDefaults = {
    {
     ActualTyreCompound::C1,
     {
         .fuelUsage = 3,
         .tyreDegradation = 1,
         .lapTimeIncrease = 50,
         .averageLapTimeDelta = 0,
     }
    },
    {
     ActualTyreCompound::C2,
     {
         .fuelUsage = 3,
         .tyreDegradation = 1.5,
         .lapTimeIncrease = 100,
         .averageLapTimeDelta = 500,
     }
    },
    {
     ActualTyreCompound::C3,
     {
         .fuelUsage = 3,
         .tyreDegradation = 2,
         .lapTimeIncrease = 150,
         .averageLapTimeDelta = 1000,
     }
    },
    {
     ActualTyreCompound::C4,
     {
         .fuelUsage = 3,
         .tyreDegradation = 2.5,
         .lapTimeIncrease = 200,
         .averageLapTimeDelta = 1500,
     }
    },
    {
     ActualTyreCompound::C5,
     {
         .fuelUsage = 3,
         .tyreDegradation = 3,
         .lapTimeIncrease = 250,
         .averageLapTimeDelta = 2000,
     }
    },
    {
     ActualTyreCompound::INTER,
     {
         .fuelUsage = 3,
         .tyreDegradation = 2,
         .lapTimeIncrease = 150,
         .averageLapTimeDelta = 10000,
     }
    },
    {
     ActualTyreCompound::WET,
     {
         .fuelUsage = 3,
         .tyreDegradation = 1.5,
         .lapTimeIncrease = 100,
         .averageLapTimeDelta = 20000,
     }
    }
};

// TODO: Fill the rest of these defaults
const std::map<TrackID, uint32_t> averageLapTimeDefaults = {
    {TrackID::MELBOURNE, 0},
    {TrackID::PAUL_RICARD, 0},
    {TrackID::SHANGHAI, 0},
    {TrackID::SAKHIR, 93000},
    {TrackID::CATALUNYA, 0},
    {TrackID::MONACO, 0},
    {TrackID::MONTREAL, 0},
    {TrackID::SILVERSTONE, 0},
    {TrackID::HOCKENHEIM, 0},
    {TrackID::HUNGARORING, 0},
    {TrackID::SPA, 0},
    {TrackID::MONZA, 0},
    {TrackID::SINGAPORE, 0},
    {TrackID::SUZUKA, 0},
    {TrackID::ABU_DHABI, 0},
    {TrackID::TEXAS, 0},
    {TrackID::BRAZIL, 0},
    {TrackID::AUSTRIA, 0},
    {TrackID::SOCHI, 0},
    {TrackID::MEXICO, 0},
    {TrackID::BAKU, 0},
    {TrackID::SAKHIR_SHORT, 0},
    {TrackID::SILVERSTONE_SHORT, 0},
    {TrackID::TEXAS_SHORT, 0},
    {TrackID::SUZUKA_SHORT, 0},
    {TrackID::HANOI, 0},
    {TrackID::ZANDVOORT, 0},
    {TrackID::IMOLA, 0},
    {TrackID::PORTIMAO, 0},
    {TrackID::JEDDAH, 0},
    {TrackID::MIAMI, 0},
};

} // namespace StrategyConstants

#endif // CONSTANTS_H

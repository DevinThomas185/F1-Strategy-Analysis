#include <string>

#include "enums.hpp"

PacketType getPacketType(const PacketData& packet) {
    return static_cast<PacketType>(packet.header.packetId);
};

std::string eventStringCodeToString(const uint8_t* code) {
    return std::string(reinterpret_cast<const char *>(code), 4);
}

EventType eventStringCodeToEventType(const uint8_t code[4]) {
    std::string str = eventStringCodeToString(code);

    if (str == "SSTA") return ::SESSION_STARTED;
    else if (str == "SEND") return ::SESSION_ENDED;
    else if (str == "FTLP") return ::FASTEST_LAP;
    else if (str == "RTMT") return ::RETIREMENT;
    else if (str == "DRSE") return ::DRS_ENABLED;
    else if (str == "DRSD") return ::DRS_DISABLED;
    else if (str == "TMPT") return ::TEAM_MATE_IN_PITS;
    else if (str == "CHQF") return ::CHEQUERED_FLAG;
    else if (str == "RCWN") return ::RACE_WINNER;
    else if (str == "PENA") return ::PENALTY_ISSUED;
    else if (str == "SPTP") return ::SPEED_TRAP_TRIGGERED;
    else if (str == "STLG") return ::START_LIGHTS;
    else if (str == "LGOT") return ::LIGHTS_OUT;
    else if (str == "DTSV") return ::DRIVE_THROUGH_SERVED;
    else if (str == "SGSV") return ::STOP_AND_GO_SERVED;
    else if (str == "FLBK") return ::FLASHBACK;
    else if (str == "BUTN") return ::BUTTON_STATUS;

    // Default case when no match is found
    return ::SESSION_STARTED;
}

TeamID getTeamID(const uint8_t teamID) {
    return static_cast<TeamID>(teamID);
};

Colour getTeamColour(TeamID teamID) {
    switch (teamID) {
    case MERCEDES:
        return Colour(0, 210, 190);
    case FERRARI:
        return Colour(220, 0, 0);
    case RED_BULL_RACING:
        return Colour(6, 0, 239);
    case WILLIAMS:
        return Colour(0, 90, 255);
    case ASTON_MARTIN:
        return Colour(0, 111, 98);
    case ALPINE:
        return Colour(0, 144, 255);
    case ALPHATAURI:
        return Colour(43, 69, 98);
    case HAAS:
        return Colour(255, 255, 255);
    case MCLAREN:
        return Colour(255, 135, 0);
    case ALFA_ROMEO:
        return Colour(144, 0, 0);
    default:
        return Colour(0, 0, 0);
    }
}

DriverID getDriverID(const uint8_t driverID) {
    return static_cast<DriverID>(driverID);
};

TrackID getTrackID(const int8_t trackID) {
    return static_cast<TrackID>(trackID);
};

std::string getTrackString(TrackID trackID) {
    switch (trackID) {
    case MELBOURNE:
        return "Australia";
    case PAUL_RICARD:
        return "France";
    case SHANGHAI:
        return "China";
    case SAKHIR:
    case SAKHIR_SHORT:
        return "Bahrain";
    case CATALUNYA:
        return "Spain";
    case MONACO:
        return "Monaco";
    case MONTREAL:
        return "Canada";
    case SILVERSTONE:
    case SILVERSTONE_SHORT:
        return "Britain";
    case HOCKENHEIM:
        return "Germany";
    case HUNGARORING:
        return "Hungary";
    case SPA:
        return "Belgium";
    case MONZA:
        return "Italy";
    case SINGAPORE:
        return "Singapore";
    case SUZUKA:
    case SUZUKA_SHORT:
        return "Japan";
    case ABU_DHABI:
        return "Abu Dhabi";
    case TEXAS:
    case TEXAS_SHORT:
        return "USA";
    case BRAZIL:
        return "Brazil";
    case AUSTRIA:
        return "Austria";
    case SOCHI:
        return "Russia";
    case MEXICO:
        return "Mexico";
    case BAKU:
        return "Azerbaijan";
    case HANOI:
        return "Vietnam";
    case ZANDVOORT:
        return "Netherlands";
    case IMOLA:
        return "Imola";
    case PORTIMAO:
        return "Portugal";
    case JEDDAH:
        return "Saudi Arabia";
    case MIAMI:
        return "Miami";
    default:
        break;
    }
}


NationalityID getNationalityID(const uint8_t nationalityID) {
    return static_cast<NationalityID>(nationalityID);
};

GameModeID getGameModeID(const uint8_t gameModeID) {
    return static_cast<GameModeID>(gameModeID);
};

RulesetID getRulesetID(const uint8_t rulesetID) {
    return static_cast<RulesetID>(rulesetID);
};

SurfaceTypeID getSurfaceTypeID(const uint8_t surfaceTypeID) {
    return static_cast<SurfaceTypeID>(surfaceTypeID);
};

PenaltyTypeID getPenaltyTypeID(const uint8_t penaltyTypeID) {
    return static_cast<PenaltyTypeID>(penaltyTypeID);
};

InfringementTypeID getInfringementTypeID(const uint8_t infringementTypeID) {
    return static_cast<InfringementTypeID>(infringementTypeID);
};

Weather getWeather(const uint8_t weather) {
    return static_cast<Weather>(weather);
};

std::string getWeatherString(Weather weather) {
    switch(weather) {
    case CLEAR:
        return "CLEAR";
    case LIGHT_CLOUD:
        return "LIGHT CLOUD";
    case OVERCAST:
        return "OVERCAST";
    case LIGHT_RAIN:
        return "LIGHT RAIN";
    case HEAVY_RAIN:
        return "HEAVY RAIN";
    case STORM:
        return "STORM";
    default:
        return "UNKNOWN";
    }
};

SessionType getSessionType(const uint8_t sessionType) {
    return static_cast<SessionType>(sessionType);
};

std::string getSessionString(SessionType sessionType) {
    switch (sessionType) {
    case UNKNOWN:
        return "Unknown Session";
    case P1:
        return "FP1";
    case P2:
        return "FP2";
    case P3:
        return "FP3";
    case SHORT_P:
        return "Short Practice";
    case Q1:
        return "Q1";
    case Q2:
        return "Q2";
    case Q3:
        return "Q3";
    case SHORT_Q:
        return "Qualifying";
    case ONE_SHOT_Q:
        return "OSQ";
    case R:
        return "Race";
    case R2:
        return "Race 2";
    case R3:
        return "Race 3";
    case TIME_TRIAL_SESSION_TYPE:
        return "Time Trial";
    default:
        return "UNKNOWN";
    }
}

Flag getFlag(const int8_t flag) {
    return static_cast<Flag>(flag);
};

Formula getFormula(const uint8_t formula) {
    return static_cast<Formula>(formula);
};

SafetyCarStatus getSafetyCarStatus(const uint8_t safetyCarStatus) {
    return static_cast<SafetyCarStatus>(safetyCarStatus);
};

SessionLength getSessionLength(const uint8_t sessionLength) {
    return static_cast<SessionLength>(sessionLength);
};

PitStatus getPitStatus(const uint8_t pitStatus) {
    return static_cast<PitStatus>(pitStatus);
};

Sector getSector(const uint8_t sector) {
    return static_cast<Sector>(sector);
};

DriverStatus getDriverStatus(const uint8_t driverStatus) {
    return static_cast<DriverStatus>(driverStatus);
};

ResultStatus getResultStatus(const uint8_t resultStatus) {
    return static_cast<ResultStatus>(resultStatus);
};

FuelMix getFuelMix(const uint8_t fuelMix) {
    return static_cast<FuelMix>(fuelMix);
};

ActualTyreCompound getActualTyreCompound(const uint8_t actualTyreCompound) {
    return static_cast<ActualTyreCompound>(actualTyreCompound);
};

std::string getActualTyreName(ActualTyreCompound tyreCompound) {
    switch (tyreCompound) {
    case C5:
        return "C5";
    case C4:
        return "C4";
    case C3:
        return "C3";
    case C2:
        return "C2";
    case C1:
        return "C1";
    case INTER:
        return "I";
    case WET:
    case WET_CLASSIC:
    case WET_F2:
        return "W";
    case DRY_CLASSIC:
        return "DRY";
    case SUPER_SOFT:
        return "SS";
    case SOFT:
        return "S";
    case MEDIUM_TYRE:
        return "M";
    case HARD:
        return "H";
    default:
        return "T";
    }
}


VisualTyreCompound getVisualTyreCompound(const uint8_t visualTyreCompound) {
    return static_cast<VisualTyreCompound>(visualTyreCompound);
};

Colour getVisualTyreColour(VisualTyreCompound tyreCompound) {
    switch (tyreCompound) {
    case SOFT_VISUAL:
    case SOFT_F2_VISUAL:
        return Colour(222, 2, 2); // RED
    case MEDIUM_VISUAL:
    case MEDIUM_F2_VISUAL:
        return Colour(242, 222, 2); // YELLOW
    case HARD_VISUAL:
    case HARD_F2_VISUAL:
        return Colour(255, 255, 255); // WHITE
    case INTER_VISUAL:
        return Colour(0, 181, 18); // GREEN
    case WET_VISUAL:
    case WET_F2_VISUAL:
        return Colour(37, 162, 230); // BLUE
    default:
        return Colour(0, 0, 0); // BLACK
    }
}

ERSDeployMode getERSDeployMode(const uint8_t ersDeployMode) {
    return static_cast<ERSDeployMode>(ersDeployMode);
};

std::string getStintTypeString(StintType stintType) {
    switch (stintType) {
    case RACE_SIMULATION:
        return "Race Simulation";
    case QUALIFYING_SIMULATION:
        return "Qualifying Simulation";
    }
}

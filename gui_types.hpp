#ifndef GUI_TYPES_HPP
#define GUI_TYPES_HPP

#include <string>
#include <vector>

#include "enums.hpp"
#include "colour.h"

struct Participant {
    DriverID driverId;
    TeamID teamId;
    uint8_t raceNumber;
    NationalityID nationality;
    std::string name;
};

struct Participants {
    uint8_t playerCarIdx;
    uint8_t secondCarIdx;
    std::vector<Participant> participants;
};

using EventAnnouncement = std::string;

struct TyreData {
    ActualTyreCompound actualTyreCompound;
    VisualTyreCompound visualTyreCompound;
    uint8_t tyreAge;
};

struct PositionsTableRow {
    size_t _carIdx;
    LapData _lapData;
    std::string position;
    std::string driver;
    int positionChange;
    std::string sector1;
    std::string sector2;
    std::string lastlap;
    std::string interval;
    TyreData tyreData;
};

using PositionsTable = std::vector<PositionsTableRow>;

struct WeatherDataBox {
    std::string timeOffset;
    std::string status;
    std::string trackTemp;
    std::string airTemp;
    std::string rainPercent;
};

using WeatherData = std::vector<WeatherDataBox>;

struct DamageData {
    uint8_t rearLeftTyreWearPercent;
    uint8_t rearRightTyreWearPercent;
    uint8_t frontLeftTyreWearPercent;
    uint8_t frontRightTyreWearPercent;

    uint8_t rearLeftTyreDamagePercent;
    uint8_t rearRightTyreDamagePercent;
    uint8_t frontLeftTyreDamagePercent;
    uint8_t frontRightTyreDamagePercent;

    uint8_t rearLeftBrakeDamagePercent;
    uint8_t rearRightBrakeDamagePercent;
    uint8_t frontLeftBrakeDamagePercent;
    uint8_t frontRightBrakeDamagePercent;

    uint8_t frontLeftWingDamagePercent;
    uint8_t frontRightWingDamagePercent;

    uint8_t rearWingDamagePercent;

    uint8_t floorDamagePercent;
    uint8_t sidepodDamagePercent;
    uint8_t diffuserDamagePercent;

    std::string drsFault;
    std::string ersFault;

    uint8_t gearboxDamagePercent;
    uint8_t engineDamagePercent;

    uint8_t mguhWearPercent;
    uint8_t esWearPercent;
    uint8_t ceWearPercent;
    uint8_t iceWearPercent;
    uint8_t mgukWearPercent;
    uint8_t tcWearPercent;

    std::string engineBlownFault;
    std::string engineSeizedFault;
};

struct TemperaturePressureData {
    uint8_t rearLeftSurfaceTemperature;
    uint8_t rearRightSurfaceTemperature;
    uint8_t frontLeftSurfaceTemperature;
    uint8_t frontRightSurfaceTemperature;

    uint8_t rearLeftInnerTemperature;
    uint8_t rearRightInnerTemperature;
    uint8_t frontLeftInnerTemperature;
    uint8_t frontRightInnerTemperature;

    uint16_t rearLeftBrakeTemperature;
    uint16_t rearRightBrakeTemperature;
    uint16_t frontLeftBrakeTemperature;
    uint16_t frontRightBrakeTemperature;

    uint16_t engineTemperature;

    float rearLeftPressure;
    float rearRightPressure;
    float frontLeftPressure;
    float frontRightPressure;

    float setupRearLeftPressure;
    float setupRearRightPressure;
    float setupFrontLeftPressure;
    float setupFrontRightPressure;
};

struct WheelTelemetryData {
    uint16_t speed;
    uint8_t throttle;
    uint8_t brake;
    uint8_t clutch;
    int8_t steering;
    int8_t gear;
    uint16_t rpm;
    bool drsActivated;
    std::string revLights;
};

struct WheelLapData {
    std::string currentPosition;
    std::string currentLapTime;
    uint8_t currentLapNumber;
};

struct WheelStatusData {
    ERSDeployMode ersDeployMode;
    uint8_t ersPercent;
    uint8_t ersDeployedThisLap;
    std::string frontBrakeBias;
    float fuelRemainingLaps;
    bool drsAllowed;
};

struct PlotTelemetryData {
    uint16_t speed;
    uint8_t throttle;
    uint8_t brake;
    uint16_t rpm;
    int8_t gear;
    int8_t steering;
};

struct LapHistoryRow {
    uint8_t lap;
    std::string sector1;
    std::string sector2;
    std::string sector3;
    std::string lapTime;
    uint32_t _lapTimeMS;
    bool sector1Valid;
    bool sector2Valid;
    bool sector3Valid;
    bool lapValid;
    std::string tyre;
    Colour tyreColour;
};

struct LapHistoryTable {
    std::vector<LapHistoryRow> table;
    uint8_t bestLapTimeLap;
    uint8_t bestSector1Lap;
    uint8_t bestSector2Lap;
    uint8_t bestSector3Lap;
};

struct PositionalData {
    std::string driverLabel;
    Colour driverColour;
    float x;
    float y;
    float z;
};

using PositionalDataMap = std::vector<PositionalData>;

struct CurrentCarSetup {
    uint8_t frontWing;
    uint8_t differentialOnThrottle;
    uint8_t brakeBias;
};

struct LiveStrategyData {
    std::string driverAhead;
    std::string driverBehind;
    std::string driverAheadDelta;
    std::string driverBehindDelta;
    TyreData driverAheadTyreData;
    TyreData driverBehindTyreData;
    std::string driverAheadPosition;
    std::string driverBehindPosition;
    std::string lastLap;
    std::string currentPosition;
    std::string currentLapNumber;
};

#endif // GUI_TYPES_HPP

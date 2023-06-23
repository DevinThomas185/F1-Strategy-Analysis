#ifndef PACKETS_HPP
#define PACKETS_HPP

#include <stdint.h>

#pragma pack(push, 1)

struct PacketHeader
{
    uint16_t packetFormat;               // 2022
    uint8_t gameMajorVersion;            // Game major version - "X.00"
    uint8_t gameMinorVersion;            // Game minor version - "1.XX"
    uint8_t packetVersion;               // Version of this packet type, all start from 1
    uint8_t packetId;                    // Identifier for the packet type, see below
    uint64_t sessionUID;                 // Unique identifier for the session
    float sessionTime;                   // Session timestamp
    uint32_t frameIdentifier;            // Identifier for the frame the data was retrieved on
    uint8_t playerCarIndex;              // Index of player's car in the array
    uint8_t secondaryPlayerCarIndex;     // Index of secondary player's car in the array (splitscreen)
        // 255 if no second player
};


struct CarMotionData
{
    float worldPositionX;         // World space X position
    float worldPositionY;         // World space Y position
    float worldPositionZ;         // World space Z position
    float worldVelocityX;         // Velocity in world space X
    float worldVelocityY;         // Velocity in world space Y
    float worldVelocityZ;         // Velocity in world space Z
    int16_t worldForwardDirX;     // World space forward X direction (normalized)
    int16_t worldForwardDirY;     // World space forward Y direction (normalized)
    int16_t worldForwardDirZ;     // World space forward Z direction (normalized)
    int16_t worldRightDirX;       // World space right X direction (normalized)
    int16_t worldRightDirY;       // World space right Y direction (normalized)
    int16_t worldRightDirZ;       // World space right Z direction (normalized)
    float gForceLateral;          // Lateral G-Force component
    float gForceLongitudinal;     // Longitudinal G-Force component
    float gForceVertical;         // Vertical G-Force component
    float yaw;                    // Yaw angle in radians
    float pitch;                  // Pitch angle in radians
    float roll;                   // Roll angle in radians
};


struct PacketMotionData
{
    // PacketHeader header;                // Header
    CarMotionData carMotionData[22];    // Data for all cars on track

    // Extra player car ONLY data
    float suspensionPosition[4];        // Note: All wheel arrays have the following order: RL, RR, FL, FR
    float suspensionVelocity[4];        // RL, RR, FL, FR
    float suspensionAcceleration[4];    // RL, RR, FL, FR
    float wheelSpeed[4];                // Speed of each wheel
    float wheelSlip[4];                 // Slip ratio for each wheel
    float localVelocityX;               // Velocity in local space
    float localVelocityY;               // Velocity in local space
    float localVelocityZ;               // Velocity in local space
    float angularVelocityX;             // Angular velocity x-component
    float angularVelocityY;             // Angular velocity y-component
    float angularVelocityZ;             // Angular velocity z-component
    float angularAccelerationX;         // Angular acceleration x-component
    float angularAccelerationY;         // Angular acceleration y-component
    float angularAccelerationZ;         // Angular acceleration z-component
    float frontWheelsAngle;             // Current front wheels angle in radians
};


struct MarshalZone
{
    float zoneStart;                    // Fraction (0..1) of way through the lap the marshal zone starts
    int8_t zoneFlag;                    // -1 = invalid/unknown, 0 = none, 1 = green, 2 = blue, 3 = yellow, 4 = red
};

struct WeatherForecastSample
{
    uint8_t sessionType;                // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P, 5 = Q1, ...
    uint8_t timeOffset;                 // Time in minutes the forecast is for
    uint8_t weather;                    // Weather - 0 = clear, 1 = light cloud, 2 = overcast, ...
    int8_t trackTemperature;            // Track temp. in degrees Celsius
    int8_t trackTemperatureChange;      // Track temp. change – 0 = up, 1 = down, 2 = no change
    int8_t airTemperature;              // Air temp. in degrees Celsius
    int8_t airTemperatureChange;        // Air temp. change – 0 = up, 1 = down, 2 = no change
    uint8_t rainPercentage;             // Rain percentage (0-100)
};

struct PacketSessionData
{
    // PacketHeader header;                        // Header
    uint8_t weather;                            // Weather - 0 = clear, 1 = light cloud, 2 = overcast, ...
    int8_t trackTemperature;                    // Track temp. in degrees Celsius
    int8_t airTemperature;                      // Air temp. in degrees Celsius
    uint8_t totalLaps;                          // Total number of laps in this race
    uint16_t trackLength;                       // Track length in meters
    uint8_t sessionType;                        // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P, ...
    int8_t trackId;                             // -1 for unknown, see appendix
    uint8_t formula;                            // Formula, 0 = F1 Modern, 1 = F1 Classic, 2 = F2, ...
    uint16_t sessionTimeLeft;                   // Time left in session in seconds
    uint16_t sessionDuration;                   // Session duration in seconds
    uint8_t pitSpeedLimit;                      // Pit speed limit in kilometers per hour
    uint8_t gamePaused;                         // Whether the game is paused – network game only
    uint8_t isSpectating;                       // Whether the player is spectating
    uint8_t spectatorCarIndex;                  // Index of the car being spectated
    uint8_t sliProNativeSupport;                // SLI Pro support, 0 = inactive, 1 = active
    uint8_t numMarshalZones;                    // Number of marshal zones to follow
    MarshalZone marshalZones[21];               // List of marshal zones – max 21
    uint8_t safetyCarStatus;                    // 0 = no safety car, 1 = full, 2 = virtual, 3 = formation lap
    uint8_t networkGame;                        // 0 = offline, 1 = online
    uint8_t numWeatherForecastSamples;          // Number of weather samples to follow
    WeatherForecastSample weatherForecastSamples[56];    // Array of weather forecast samples
    uint8_t forecastAccuracy;                   // 0 = Perfect, 1 = Approximate
    uint8_t aiDifficulty;                       // AI Difficulty rating – 0-110
    uint32_t seasonLinkIdentifier;              // Identifier for season - persists
    uint32_t weekendLinkIdentifier;             // Identifier for weekend - persists
    uint32_t sessionLinkIdentifier;             // Identifier for session - persists
    uint8_t pitStopWindowIdealLap;              // Ideal lap to pit on for current strategy (player)
    uint8_t pitStopWindowLatestLap;             // Latest lap to pit on for current strategy (player)
    uint8_t pitStopRejoinPosition;              // Predicted position to rejoin at (player)
    uint8_t steeringAssist;                     // 0 = off, 1 = on
    uint8_t brakingAssist;                      // 0 = off, 1 = low, 2 = medium, 3 = high
    uint8_t gearboxAssist;                      // 1 = manual, 2 = manual & suggested gear, 3 = auto
    uint8_t pitAssist;                          // 0 = off, 1 = on
    uint8_t pitReleaseAssist;                   // 0 = off, 1 = on
    uint8_t ERSAssist;                          // 0 = off, 1 = on
    uint8_t DRSAssist;                          // 0 = off, 1 = on
    uint8_t dynamicRacingLine;                   // 0 = off, 1 = corners only, 2 = full
    uint8_t dynamicRacingLineType;               // 0 = 2D, 1 = 3D
    uint8_t gameMode;                            // Game mode id - see appendix
    uint8_t ruleSet;                             // Ruleset - see appendix
    uint32_t timeOfDay;                          // Local time of day - minutes since midnight
    uint8_t sessionLength;                       // 0 = None, 2 = Very Short, 3 = Short, 4 = Medium, ...
};


struct LapData
{
    uint32_t lastLapTimeInMS;                  // Last lap time in milliseconds
    uint32_t currentLapTimeInMS;               // Current time around the lap in milliseconds
    uint16_t sector1TimeInMS;                  // Sector 1 time in milliseconds
    uint16_t sector2TimeInMS;                  // Sector 2 time in milliseconds
    float lapDistance;                         // Distance vehicle is around current lap in meters – could be negative if line hasn’t been crossed yet
    float totalDistance;                       // Total distance traveled in session in meters – could be negative if line hasn’t been crossed yet
    float safetyCarDelta;                      // Delta in seconds for safety car
    uint8_t carPosition;                       // Car race position
    uint8_t currentLapNum;                     // Current lap number
    uint8_t pitStatus;                         // 0 = none, 1 = pitting, 2 = in pit area
    uint8_t numPitStops;                       // Number of pit stops taken in this race
    uint8_t sector;                            // 0 = sector1, 1 = sector2, 2 = sector3
    uint8_t currentLapInvalid;                 // Current lap invalid - 0 = valid, 1 = invalid
    uint8_t penalties;                         // Accumulated time penalties in seconds to be added
    uint8_t warnings;                          // Accumulated number of warnings issued
    uint8_t numUnservedDriveThroughPens;        // Num drive through pens left to serve
    uint8_t numUnservedStopGoPens;              // Num stop go pens left to serve
    uint8_t gridPosition;                      // Grid position the vehicle started the race in
    uint8_t driverStatus;                      // Status of driver - 0 = in garage, 1 = flying lap, 2 = in lap, 3 = out lap, 4 = on track
    uint8_t resultStatus;                      // Result status - 0 = invalid, 1 = inactive, 2 = active, 3 = finished, 4 = did not finish, 5 = disqualified, 6 = not classified, 7 = retired
    uint8_t pitLaneTimerActive;                // Pit lane timing, 0 = inactive, 1 = active
    uint16_t pitLaneTimeInLaneInMS;             // If active, the current time spent in the pit lane in ms
    uint16_t pitStopTimerInMS;                  // Time of the actual pit stop in ms
    uint8_t pitStopShouldServePen;              // Whether the car should serve a penalty at this stop
};

struct PacketLapData
{
    // PacketHeader header;                        // Header
    LapData lapData[22];                         // Lap data for all cars on track
    uint8_t timeTrialPBCarIdx;                   // Index of Personal Best car in time trial (255 if invalid)
    uint8_t timeTrialRivalCarIdx;                // Index of Rival car in time trial (255 if invalid)
};


union EventDataDetails
{
    struct FastestLap
    {
        uint8_t vehicleIdx;  // Vehicle index of car achieving fastest lap
        float lapTime;       // Lap time is in seconds
    } FastestLap;

    struct Retirement
    {
        uint8_t vehicleIdx;  // Vehicle index of car retiring
    } Retirement;

    struct TeamMateInPits
    {
        uint8_t vehicleIdx;  // Vehicle index of team mate
    } TeamMateInPits;

    struct RaceWinner
    {
        uint8_t vehicleIdx;  // Vehicle index of the race winner
    } RaceWinner;

    struct Penalty
    {
        uint8_t penaltyType;         // Penalty type – see Appendices
        uint8_t infringementType;    // Infringement type – see Appendices
        uint8_t vehicleIdx;          // Vehicle index of the car the penalty is applied to
        uint8_t otherVehicleIdx;     // Vehicle index of the other car involved
        uint8_t time;                // Time gained, or time spent doing action in seconds
        uint8_t lapNum;              // Lap the penalty occurred on
        uint8_t placesGained;        // Number of places gained by this
    } Penalty;

    struct SpeedTrap
    {
        uint8_t vehicleIdx;                   // Vehicle index of the vehicle triggering speed trap
        float speed;                          // Top speed achieved in kilometres per hour
        uint8_t isOverallFastestInSession;    // Overall fastest speed in session = 1, otherwise 0
        uint8_t isDriverFastestInSession;     // Fastest speed for driver in session = 1, otherwise 0
        uint8_t fastestVehicleIdxInSession;   // Vehicle index of the vehicle that is the fastest in this session
        float fastestSpeedInSession;          // Speed of the vehicle that is the fastest in this session
    } SpeedTrap;

    struct StartLights
    {
        uint8_t numLights;  // Number of lights showing
    } StartLights;

    struct DriveThroughPenaltyServed
    {
        uint8_t vehicleIdx;  // Vehicle index of the vehicle serving drive through
    } DriveThroughPenaltyServed;

    struct StopGoPenaltyServed
    {
        uint8_t vehicleIdx;  // Vehicle index of the vehicle serving stop go
    } StopGoPenaltyServed;

    struct Flashback
    {
        uint32_t flashbackFrameIdentifier;  // Frame identifier flashed back to
        float flashbackSessionTime;         // Session time flashed back to
    } Flashback;

    struct Buttons
    {
        uint32_t buttonStatus;  // Bit flags specifying which buttons are being pressed currently - see appendices
    } Buttons;
};

struct PacketEventData
{
    // PacketHeader header;                // Header
    uint8_t eventStringCode[4];         // Event string code, see below
    EventDataDetails eventDetails;      // Event details - should be interpreted differently for each type
};


struct ParticipantData
{
    uint8_t aiControlled;        // Whether the vehicle is AI (1) or Human (0) controlled
    uint8_t driverId;            // Driver id - see appendix, 255 if network human
    uint8_t networkId;           // Network id – unique identifier for network players
    uint8_t teamId;              // Team id - see appendix
    uint8_t myTeam;              // My team flag – 1 = My Team, 0 = otherwise
    uint8_t raceNumber;          // Race number of the car
    uint8_t nationality;         // Nationality of the driver
    char name[48];               // Name of participant in UTF-8 format – null terminated
        // Will be truncated with ... (U+2026) if too long
    uint8_t yourTelemetry;       // The player's UDP setting, 0 = restricted, 1 = public
};

struct PacketParticipantsData
{
    // PacketHeader header;         // Header
    uint8_t numActiveCars;       // Number of active cars in the data – should match number of
        // cars on HUD
    ParticipantData participants[22];
};

struct CarSetupData
{
    uint8_t frontWing;                  // Front wing aero
    uint8_t rearWing;                   // Rear wing aero
    uint8_t onThrottle;                 // Differential adjustment on throttle (percentage)
    uint8_t offThrottle;                // Differential adjustment off throttle (percentage)
    float frontCamber;                  // Front camber angle (suspension geometry)
    float rearCamber;                   // Rear camber angle (suspension geometry)
    float frontToe;                     // Front toe angle (suspension geometry)
    float rearToe;                      // Rear toe angle (suspension geometry)
    uint8_t frontSuspension;            // Front suspension
    uint8_t rearSuspension;             // Rear suspension
    uint8_t frontAntiRollBar;           // Front anti-roll bar
    uint8_t rearAntiRollBar;            // Front anti-roll bar
    uint8_t frontSuspensionHeight;      // Front ride height
    uint8_t rearSuspensionHeight;       // Rear ride height
    uint8_t brakePressure;              // Brake pressure (percentage)
    uint8_t brakeBias;                  // Brake bias (percentage)
    float rearLeftTyrePressure;         // Rear left tyre pressure (PSI)
    float rearRightTyrePressure;        // Rear right tyre pressure (PSI)
    float frontLeftTyrePressure;        // Front left tyre pressure (PSI)
    float frontRightTyrePressure;       // Front right tyre pressure (PSI)
    uint8_t ballast;                    // Ballast
    float fuelLoad;                     // Fuel load
};

struct PacketCarSetupData
{
    // PacketHeader header;                // Header
    CarSetupData carSetups[22];
};

struct CarTelemetryData
{
    uint16_t speed;                          // Speed of car in kilometres per hour
    float throttle;                          // Amount of throttle applied (0.0 to 1.0)
    float steer;                             // Steering (-1.0 (full lock left) to 1.0 (full lock right))
    float brake;                             // Amount of brake applied (0.0 to 1.0)
    uint8_t clutch;                          // Amount of clutch applied (0 to 100)
    int8_t gear;                             // Gear selected (1-8, N=0, R=-1)
    uint16_t engineRPM;                      // Engine RPM
    uint8_t drs;                             // 0 = off, 1 = on
    uint8_t revLightsPercent;                // Rev lights indicator (percentage)
    uint16_t revLightsBitValue;              // Rev lights (bit 0 = leftmost LED, bit 14 = rightmost LED)
    uint16_t brakesTemperature[4];           // Brakes temperature (celsius)
    uint8_t tyresSurfaceTemperature[4];      // Tyres surface temperature (celsius)
    uint8_t tyresInnerTemperature[4];        // Tyres inner temperature (celsius)
    uint16_t engineTemperature;              // Engine temperature (celsius)
    float tyresPressure[4];                  // Tyres pressure (PSI)
    uint8_t surfaceType[4];                  // Driving surface, see appendices
};

struct PacketCarTelemetryData
{
    // PacketHeader header;                     // Header
    CarTelemetryData carTelemetryData[22];
    uint8_t mfdPanelIndex;                    // Index of MFD panel open - 255 = MFD closed
        // Single player, race – 0 = Car setup, 1 = Pits
        // 2 = Damage, 3 = Engine, 4 = Temperatures
        // May vary depending on game mode
    uint8_t mfdPanelIndexSecondaryPlayer;     // See above
    int8_t suggestedGear;                     // Suggested gear for the player (1-8)
        // 0 if no gear suggested
};


struct CarStatusData
{
    uint8_t tractionControl;              // Traction control - 0 = off, 1 = medium, 2 = full
    uint8_t antiLockBrakes;               // 0 (off) - 1 (on)
    uint8_t fuelMix;                      // Fuel mix - 0 = lean, 1 = standard, 2 = rich, 3 = max
    uint8_t frontBrakeBias;               // Front brake bias (percentage)
    uint8_t pitLimiterStatus;             // Pit limiter status - 0 = off, 1 = on
    float fuelInTank;                     // Current fuel mass
    float fuelCapacity;                   // Fuel capacity
    float fuelRemainingLaps;              // Fuel remaining in terms of laps (value on MFD)
    uint16_t maxRPM;                      // Cars max RPM, point of rev limiter
    uint16_t idleRPM;                     // Cars idle RPM
    uint8_t maxGears;                     // Maximum number of gears
    uint8_t drsAllowed;                   // 0 = not allowed, 1 = allowed
    uint16_t drsActivationDistance;       // 0 = DRS not available, non-zero - DRS will be available in [X] metres
    uint8_t actualTyreCompound;           // F1 Modern - 16 = C5, 17 = C4, 18 = C3, 19 = C2, 20 = C1
        // 7 = inter, 8 = wet
        // F1 Classic - 9 = dry, 10 = wet
        // F2 – 11 = super soft, 12 = soft, 13 = medium, 14 = hard
        // 15 = wet
    uint8_t visualTyreCompound;           // F1 visual (can be different from actual compound)
        // 16 = soft, 17 = medium, 18 = hard, 7 = inter, 8 = wet
        // F1 Classic – same as above
        // F2 ‘19, 15 = wet, 19 – super soft, 20 = soft
        // 21 = medium , 22 = hard
    uint8_t tyresAgeLaps;                 // Age in laps of the current set of tyres
    int8_t vehicleFiaFlags;               // -1 = invalid/unknown, 0 = none, 1 = green
        // 2 = blue, 3 = yellow, 4 = red
    float ersStoreEnergy;                 // ERS energy store in Joules
    uint8_t ersDeployMode;                // ERS deployment mode, 0 = none, 1 = medium
        // 2 = hotlap, 3 = overtake
    float ersHarvestedThisLapMGUK;        // ERS energy harvested this lap by MGU-K
    float ersHarvestedThisLapMGUH;        // ERS energy harvested this lap by MGU-H
    float ersDeployedThisLap;             // ERS energy deployed this lap
    uint8_t networkPaused;                // Whether the car is paused in a network game
};

struct PacketCarStatusData
{
    // PacketHeader header;                  // Header
    CarStatusData carStatusData[22];
};


struct FinalClassificationData
{
    uint8_t position;                  // Finishing position
    uint8_t numLaps;                   // Number of laps completed
    uint8_t gridPosition;              // Grid position of the car
    uint8_t points;                    // Number of points scored
    uint8_t numPitStops;               // Number of pit stops made
    uint8_t resultStatus;              // Result status - 0 = invalid, 1 = inactive, 2 = active
        // 3 = finished, 4 = did not finish, 5 = disqualified
        // 6 = not classified, 7 = retired
    uint32_t bestLapTimeInMS;          // Best lap time of the session in milliseconds
    double totalRaceTime;              // Total race time in seconds without penalties
    uint8_t penaltiesTime;             // Total penalties accumulated in seconds
    uint8_t numPenalties;              // Number of penalties applied to this driver
    uint8_t numTyreStints;             // Number of tyre stints up to maximum
    uint8_t tyreStintsActual[8];       // Actual tyres used by this driver
    uint8_t tyreStintsVisual[8];       // Visual tyres used by this driver
    uint8_t tyreStintsEndLaps[8];      // The lap number stints end on
};

struct PacketFinalClassificationData
{
    // PacketHeader header;               // Header
    uint8_t numCars;                   // Number of cars in the final classification
    FinalClassificationData classificationData[22];
};


struct LobbyInfoData
{
    uint8_t aiControlled;            // Whether the vehicle is AI (1) or Human (0) controlled
    uint8_t teamId;                  // Team id - see appendix (255 if no team currently selected)
    uint8_t nationality;             // Nationality of the driver
    char name[48];                   // Name of participant in UTF-8 format – null terminated
        // Will be truncated with ... (U+2026) if too long
    uint8_t carNumber;               // Car number of the player
    uint8_t readyStatus;             // 0 = not ready, 1 = ready, 2 = spectating
};

struct PacketLobbyInfoData
{
    // PacketHeader header;             // Header
    uint8_t numPlayers;              // Number of players in the lobby data
    LobbyInfoData lobbyPlayers[22];
};

struct CarDamageData
{
    float tyresWear[4];             // Tyre wear (percentage)
    uint8_t tyresDamage[4];         // Tyre damage (percentage)
    uint8_t brakesDamage[4];        // Brakes damage (percentage)
    uint8_t frontLeftWingDamage;    // Front left wing damage (percentage)
    uint8_t frontRightWingDamage;   // Front right wing damage (percentage)
    uint8_t rearWingDamage;         // Rear wing damage (percentage)
    uint8_t floorDamage;            // Floor damage (percentage)
    uint8_t diffuserDamage;         // Diffuser damage (percentage)
    uint8_t sidepodDamage;          // Sidepod damage (percentage)
    uint8_t drsFault;               // Indicator for DRS fault, 0 = OK, 1 = fault
    uint8_t ersFault;               // Indicator for ERS fault, 0 = OK, 1 = fault
    uint8_t gearBoxDamage;          // Gear box damage (percentage)
    uint8_t engineDamage;           // Engine damage (percentage)
    uint8_t engineMGUHWear;         // Engine wear MGU-H (percentage)
    uint8_t engineESWear;           // Engine wear ES (percentage)
    uint8_t engineCEWear;           // Engine wear CE (percentage)
    uint8_t engineICEWear;          // Engine wear ICE (percentage)
    uint8_t engineMGUKWear;         // Engine wear MGU-K (percentage)
    uint8_t engineTCWear;           // Engine wear TC (percentage)
    uint8_t engineBlown;            // Engine blown, 0 = OK, 1 = fault
    uint8_t engineSeized;           // Engine seized, 0 = OK, 1 = fault
};

struct PacketCarDamageData
{
    // PacketHeader header;             // Header
    CarDamageData carDamageData[22];
};

struct LapHistoryData
{
    uint32_t lapTimeInMS;       // Lap time in milliseconds
    uint16_t sector1TimeInMS;   // Sector 1 time in milliseconds
    uint16_t sector2TimeInMS;   // Sector 2 time in milliseconds
    uint16_t sector3TimeInMS;   // Sector 3 time in milliseconds
    uint8_t lapValidBitFlags;   // 0x01 bit set-lap valid, 0x02 bit set-sector 1 valid
        // 0x04 bit set-sector 2 valid, 0x08 bit set-sector 3 valid
};

struct TyreStintHistoryData
{
    uint8_t endLap;                 // Lap the tyre usage ends on (255 of current tyre)
    uint8_t tyreActualCompound;     // Actual tyres used by this driver
    uint8_t tyreVisualCompound;     // Visual tyres used by this driver
};

struct PacketSessionHistoryData
{
    // PacketHeader header;                     // Header
    uint8_t carIdx;                          // Index of the car this lap data relates to
    uint8_t numLaps;                         // Num laps in the data (including current partial lap)
    uint8_t numTyreStints;                   // Number of tyre stints in the data
    uint8_t bestLapTimeLapNum;               // Lap the best lap time was achieved on
    uint8_t bestSector1LapNum;               // Lap the best Sector 1 time was achieved on
    uint8_t bestSector2LapNum;               // Lap the best Sector 2 time was achieved on
    uint8_t bestSector3LapNum;               // Lap the best Sector 3 time was achieved on
    LapHistoryData lapHistoryData[100];       // 100 laps of data max
    TyreStintHistoryData tyreStintsHistoryData[8];
};


struct PacketData
{
    PacketHeader header;
    union {
        PacketMotionData motionData;
        PacketSessionData sessionData;
        PacketLapData lapData;
        PacketEventData eventData;
        PacketParticipantsData participantsData;
        PacketCarSetupData carSetupData;
        PacketCarTelemetryData carTelemetryData;
        PacketCarStatusData carStatusData;
        PacketFinalClassificationData finalClassificationData;
        PacketLobbyInfoData lobbyInfoData;
        PacketCarDamageData carDamageData;
        PacketSessionHistoryData sessionHistoryData;
    } packet;
};

#pragma pack(pop)

#endif  // PACKETS_HPP

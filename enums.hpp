#ifndef ENUMS_HPP
#define ENUMS_HPP

#include <string>
#include "packets.hpp"
#include "colour.h"

enum TyreOrder {
    REAR_LEFT = 0,
    REAR_RIGHT = 1,
    FRONT_LEFT = 2,
    FRONT_RIGHT = 3,
};

enum PacketType {
    MOTION,
    SESSION,
    LAP_DATA,
    EVENT,
    PARTICIPANTS,
    CAR_SETUPS,
    CAR_TELEMETRY,
    CAR_STATUS,
    FINAL_CLASSIFICATION,
    LOBBY_INFO,
    CAR_DAMAGE,
    SESSION_HISTORY,
};

PacketType getPacketType(const PacketData &packet);

enum EventType {
    SESSION_STARTED,
    SESSION_ENDED,
    FASTEST_LAP,
    RETIREMENT,
    DRS_ENABLED,
    DRS_DISABLED,
    TEAM_MATE_IN_PITS,
    CHEQUERED_FLAG,
    RACE_WINNER,
    PENALTY_ISSUED,
    SPEED_TRAP_TRIGGERED,
    START_LIGHTS,
    LIGHTS_OUT,
    DRIVE_THROUGH_SERVED,
    STOP_AND_GO_SERVED,
    FLASHBACK,
    BUTTON_STATUS
};

std::string eventStringCodeToString(const uint8_t *code);

EventType eventStringCodeToEventType(const uint8_t code[4]);

enum TeamID {
    // F1 - 2022
    MERCEDES = 0,
    FERRARI = 1,
    RED_BULL_RACING = 2,
    WILLIAMS = 3,
    ASTON_MARTIN = 4,
    ALPINE = 5,
    ALPHATAURI = 6,
    HAAS = 7,
    MCLAREN = 8,
    ALFA_ROMEO = 9,

    // F1 - 2020
    MERCEDES_2020 = 85,
    FERRARI_2020 = 86,
    RED_BULL_2020 = 87,
    WILLIAMS_2020 = 88,
    RACING_POINT_2020 = 89,
    RENAULT_2020 = 90,
    ALPHATAURI_2020 = 91,
    HAAS_2020 = 92,
    MCLAREN_2020 = 93,
    ALFA_ROMEO_2020 = 94,

    // Super Cars
    ASTON_MARTIN_DB11_V12 = 95,
    ASTON_MARTIN_VANTAGE_F1_EDITION = 96,
    ASTON_MARTIN_VANTAGE_SAFETY_CAR = 97,
    FERRARI_F8_TRIBUTO = 98,
    FERRARI_ROMA = 99,
    MCLAREN_720S = 100,
    MCLAREN_ARTURA = 101,
    MERCEDES_AMG_GT_BLACK_SERIES = 117,
    MERCEDES_AMG_GT_BLACK_SERIES_SAFETY_CAR = 102,
    MERCEDES_AMG_GTR_PRO = 103,
    F1_CUSTOM_TEAM = 104,

    // F2 - 2021
    PREMA_2021 = 106,
    UNI_VIRTUOSI_2021 = 107,
    CARLIN_2021 = 108,
    HITECH_2021 = 109,
    ART_GP_2021 = 110,
    MP_MOTORSPORT_2021 = 111,
    CHAROUZ_2021 = 112,
    DAMS_2021 = 113,
    CAMPOS_2021 = 114,
    BWT_2021 = 115,
    TRIDENT_2021 = 116,

    // F2 - 2022
    PREMA_2022 = 118,
    VIRTUOSI_2022 = 119,
    CARLIN_2022 = 120,
    HITECH_2022 = 121,
    ART_GP_2022 = 122,
    MP_MOTORSPORT_2022 = 123,
    CHAROUZ_2022 = 124,
    DAMS_2022 = 125,
    CAMPOS_2022 = 126,
    VAN_AMERSFOORT_2022 = 127,
    TRIDENT_2022 = 128,
};

TeamID getTeamID(const uint8_t teamID);

Colour getTeamColour(TeamID teamID);

enum DriverID {
    //// F1 Teams
    // Red Bull Racing
    MAX_VERSTAPPEN = 9,
    SERGIO_PEREZ = 14,
    DANIEL_RICCIARDO = 2,

    // Ferrari
    CHARLES_LECLERC = 58,
    CARLOS_SAINZ = 0,
    ANTONIO_GIOVINAZZI = 74,

    // Mercedes
    LEWIS_HAMILTON = 7,
    GEORGE_RUSSELL = 50,
    MICK_SCHUMACHER = 81,

    // Alpine
    ESTEBAN_OCON = 17,
    PIERRE_GASLY = 59,

    // Mclaren
    LANDO_NORRIS = 54,
    OSCAR_PIASTRI = 112,

    // Alfa Romeo
    VALTTERI_BOTTAS = 15,
    GUANYU_ZHOU = 80,

    // Aston Martin
    FERNANDO_ALONSO = 3,
    LANCE_STROLL = 19,
    FELIPE_DRUGOVICH = 98,

    // Alphatauri
    NYCK_DE_VRIES = 48,
    YUKI_TSUNODA = 94,

    // Haas
    KEVIN_MAGNUSSEN = 11,
    NICO_HULKENBERG = 10,

    // Williams
    ALEXANDER_ALBON = 62,
    LOGAN_SARGEANT = 130,

    // Retired
    DANIIL_KVYAT = 1,
    FELIPE_MASSA = 4,
    KIMI_RAIKKONEN = 6,
    ROMAIN_GROSJEAN = 12,
    SEBASTIAN_VETTEL = 13,
    NICHOLAS_LATIFI = 63,
    ROBERT_KUBICA = 75,
    ALAIN_PROST = 76,
    AYRTON_SENNA = 77,
    NIKITA_MAZEPIN = 79,
    ANTHOINE_HUBERT = 87,
    MICHAEL_SCHUMACHER = 90,
    JENSON_BUTTON = 109,
    DAVID_COULTHARD = 110,
    NICO_ROSBERG = 111,
    MARK_WEBBER = 125,
    JACQUES_VILLENEUVE = 126,
    MIKA_HAKKINEN = 138,

    // Braking Point
    DEVON_BUTLER = 72,
    LUKAS_WEBER = 73,
    AIDAN_JACKSON = 102,
    CASPER_AKKERMAN = 103,

    //// F2
    // MP Motorsport
    JEHAN_DARUVALA = 95,
    DENNIS_HAUGER = 134,

    // Rodin Carlin
    ENZO_FITTIPALDI = 123,

    // ART Grand Prix
    THEO_POURCHAIRE = 115,

    // Prema Racing
    FREDERIK_VESTI = 128,

    // DAMS
    AYUMU_IWASA = 132,

    // Invicta Virtuosi Racing
    JACK_DOOHAN = 136,

    // PHM Racing by Charouz
    ROY_NISSANY = 100,

    // Trident
    CLEMENT_NOVOLAK = 133,

    // Van Amersfoort Racing
    RICHARD_VERSCHOOR = 116,
    JUAN_MANUEL_CORREA = 83,

    // Campos Racing
    RALPH_BOSCHUNG = 89,

    //// My Team
    ARRON_BARNES = 20,
    MARTIN_GILES = 21,
    ALEX_MURRAY = 22,
    LUCAS_ROTH = 23,
    IGOR_CORREIA = 24,
    SOPHIE_LEVASSEUR = 25,
    JONAS_SCHIFFER = 26,
    ALAIN_FOREST = 27,
    JAY_LETOURNEAU = 28,
    ESTO_SAARI = 29,
    YASAR_ATIYEH = 30,
    CALLISTO_CALABRESI = 31,
    NAOTA_IZUM = 32,
    HOWARD_CLARKE = 33,
    WILHELM_KAUFMANN = 34,
    MARIE_LAURSEN = 35,
    FLAVIO_NIEVES = 36,
    PETER_BELOUSOV = 37,
    KLIMEK_MICHALSKI = 38,
    SANTIAGO_MORENO = 39,
    BENJAMIN_COPPENS = 40,
    NOAH_VISSER = 41,
    GERT_WALDMULLER = 42,
    JULIAN_QUESADA = 43,
    DANIEL_JONES = 44,

    // Others
    ARTEM_MARKELOV = 45,
    TADASUKE_MAKINO = 46,
    SEAN_GELAEL = 47,
    JACK_AITKEN = 49,
    MAXIMILLIAN_GUNTHER = 51,
    NIREI_FUKUZUMI = 52,
    LUCA_GHIOTTO = 53,
    SERGIO_SETTE_CAMARA = 55,
    LOUIS_DELETRAZ = 56,
    ANTONIO_FUOCO = 57,
    DORIAN_BOCCOLACCI = 64,
    NIKO_KARI = 65,
    ROBERTO_MERHI = 66,
    ARJUN_MAINI = 67,
    ALESSIO_LORANDI = 68,
    RUBEN_MEIJER = 69,
    RASHID_NAIR = 70,
    JACK_TREMBLAY = 71,
    NOBUHARU_MATSUSHITA = 78,
    CALLUM_ILOTT = 82,
    JORDAN_KING = 84,
    MAHAVEER_RAGHUNATHAN = 85,
    TATIANA_CALDERON = 86,
    GUILIANO_ALESI = 88,
    DAN_TICKTUM = 91,
    MARCUS_ARMSTRONG = 92,
    CHRISTIAN_LUNDGAARD = 93,
    GULHERME_SAMAIA = 96,
    PEDRO_PIQUET = 97,
    ROBERT_SCHWARTZMAN = 99,
    MARINO_SATO = 101,
    LIAM_LAWSON = 113,
    JURI_VIPS = 114,
    LIRIM_ZENDELI = 117,
    DAVID_BECKMANN = 118,
    ALESSIO_DELEDDA = 121,
    BENT_VISCAAL = 122,
    JAKE_HUGHES = 127,
    OLLI_CALDWELL = 129,
    CEM_BOLUKBASI = 131,
    CALAN_WILLIAMS = 135,
    AMAURY_CORDEEL = 137,
};

DriverID getDriverID(const uint8_t driverID);

enum TrackID {
    MELBOURNE = 0,
    PAUL_RICARD = 1,
    SHANGHAI = 2,
    SAKHIR = 3,
    CATALUNYA = 4,
    MONACO = 5,
    MONTREAL = 6,
    SILVERSTONE = 7,
    HOCKENHEIM = 8,
    HUNGARORING = 9,
    SPA = 10,
    MONZA = 11,
    SINGAPORE = 12,
    SUZUKA = 13,
    ABU_DHABI = 14,
    TEXAS = 15,
    BRAZIL = 16,
    AUSTRIA = 17,
    SOCHI = 18,
    MEXICO = 19,
    BAKU = 20,
    SAKHIR_SHORT = 21,
    SILVERSTONE_SHORT = 22,
    TEXAS_SHORT = 23,
    SUZUKA_SHORT = 24,
    HANOI = 25,
    ZANDVOORT = 26,
    IMOLA = 27,
    PORTIMAO = 28,
    JEDDAH = 29,
    MIAMI = 30,
};

TrackID getTrackID(const int8_t trackID);

std::string getTrackString(TrackID trackID);

enum NationalityID {
    AMERICAN = 1,
    ARGENTINEAN = 2,
    AUSTRALIAN = 3,
    AUSTRIAN = 4,
    AZERBAIJANI = 5,
    BAHRAINI = 6,
    BELGIAN = 7,
    BOLIVIAN = 8,
    BRAZILIAN = 9,
    BRITISH = 10,
    BULGARIAN = 11,
    CAMEROONIAN = 12,
    CANADIAN = 13,
    CHILEAN = 14,
    CHINESE = 15,
    COLOMBIAN = 16,
    COSTA_RICAN = 17,
    CROATIAN = 18,
    CYPRIOT = 19,
    CZECH = 20,
    DANISH = 21,
    DUTCH = 22,
    ECUADORIAN = 23,
    ENGLISH = 24,
    EMIRIAN = 25,
    ESTONIAN = 26,
    FINNISH = 27,
    FRENCH = 28,
    GERMAN = 29,
    GHANAIAN = 30,
    GREEK = 31,
    GUATEMALAN = 32,
    HONDURAN = 33,
    HONG_KONG = 34,
    HUNGARIAN = 35,
    ICELANDER = 36,
    INDIAN = 37,
    INDONESIAN = 38,
    IRISH = 39,
    ISRAELI = 40,
    ITALIAN = 41,
    JAMAICAN = 42,
    JAPANESE = 43,
    JORDINIAN = 44,
    KUWAITI = 45,
    LATVIAN = 46,
    LEBANESE = 47,
    LITHUANIAN = 48,
    LUXEMBOURGER = 49,
    MALAYSIAN = 50,
    MALTESE = 51,
    MEXICAN = 52,
    MONEGASQUE = 53,
    NEW_ZEALANDER = 54,
    NICARAGUAN = 55,
    NORTHERN_IRISH = 56,
    NORWEGIAN = 57,
    OMANI = 58,
    PAKISTANI = 59,
    PANAMANIAN = 60,
    PARAGUAYAN = 61,
    PERUVIAN = 62,
    POLISH = 63,
    PORTUGUESE = 64,
    QATARI = 65,
    ROMANIAN = 66,
    RUSSIAN = 67,
    SALVADORAN = 68,
    SAUDI = 69,
    SCOTTISH = 70,
    SERBIAN = 71,
    SINGAPOREAN = 72,
    SLOVAKIAN = 73,
    SLOVENIAN = 74,
    SOUTH_KOREAN = 75,
    SOUTH_AFRICAN = 76,
    SPANISH = 77,
    SWEDISH = 78,
    SWISS = 79,
    THAI = 80,
    TURKISH = 81,
    URUGUAYAN = 82,
    UKRAINIAN = 83,
    VENEZUELAN = 84,
    BARBADIAN = 85,
    WELSH = 86,
    VIETNAMESE = 87,
};

NationalityID getNationalityID(const uint8_t nationalityID);

enum GameModeID {
    EVENT_MODE = 0,
    GRAND_PRIX = 3,
    TIME_TRIAL_GAME_MODE = 5,
    SPLIT_SCREEN = 6,
    ONLINE_CUSTOM = 7,
    ONLINE_LEAGUE = 8,
    CAREER_INVITATIONAL = 11,
    CHAMPIONSHIP_INVITATIONAL = 12,
    CHAMPIONSHIP = 13,
    ONLINE_CHAMPIONSHIP = 14,
    ONLINE_WEEKLY_EVENT = 15,
    CAREER_2022 = 19,
    CAREER_ONLINE_2022 = 20,
    BENCHMARK = 127,
};

GameModeID getGameModeID(const uint8_t gameModeID);

enum RulesetID {
    PRACTICE_QUALIFYING = 0,
    RACE = 1,
    TIME_TRIAL_RULESET = 2,
    TIME_ATTACK = 4,
    CHECKPOINT_CHALLENGE = 6,
    AUTOCROSS = 8,
    DRIFT = 9,
    AVERAGE_SPEED_ZONE = 10,
    RIVAL_DUEL = 11,
};

RulesetID getRulesetID(const uint8_t rulesetID);

enum SurfaceTypeID {
    TARMAC = 0,
    RUMBLE_STRIP = 1,
    CONCRETE = 2,
    ROCK = 3,
    GRAVEL = 4,
    MUD = 5,
    SAND = 6,
    GRASS = 7,
    WATER = 8,
    COBBLESTONE = 9,
    METAL = 10,
    RIDGED = 11,
};

SurfaceTypeID getSurfaceTypeID(const uint8_t surfaceTypeID);

enum ButtonFlags {
    A_BUTTON = 0x00000001,
    Y_BUTTON = 0x00000002,
    B_BUTTON = 0x00000004,
    X_BUTTON = 0x00000008,

    D_PAD_LEFT = 0x00000010,
    D_PAD_RIGHT = 0x00000020,
    D_PAD_UP = 0x00000040,
    D_PAD_DOWN = 0x00000080,

    OPTIONS_MENU = 0x00000100,
    LB_BUTTON = 0x00000200,
    RB_BUTTON = 0x00000400,
    LT_BUTTON = 0x00000800,

    RT_BUTTON = 0x00001000,
    LEFT_STICK_CLICK = 0x00002000,
    RIGHT_STICK_CLICK = 0x00004000,
    RIGHT_STICK_LEFT = 0x00008000,

    RIGHT_STICK_RIGHT = 0x00010000,
    RIGHT_STICK_UP = 0x00020000,
    RIGHT_STICK_DOWN = 0x00040000,
    SPECIAL = 0x00080000,

    UDP_ACTION_1 = 0x00100000,
    UDP_ACTION_2 = 0x00200000,
    UDP_ACTION_3 = 0x00400000,
    UDP_ACTION_4 = 0x00800000,

    UDP_ACTION_5 = 0x01000000,
    UDP_ACTION_6 = 0x02000000,
    UDP_ACTION_7 = 0x04000000,
    UDP_ACTION_8 = 0x08000000,

    UDP_ACTION_9 = 0x10000000,
    UDP_ACTION_10 = 0x20000000,
    UDP_ACTION_11 = 0x40000000,
    UDP_ACTION_12 = 0x80000000,
};

enum PenaltyTypeID {
    DRIVE_THROUGH = 0,
    STOP_AND_GO = 1,
    GRID_PENALTY = 2,
    PENALTY_REMINDER = 3,
    TIME_PENALTY = 4,
    WARNING = 5,
    DISQUALIFIED_PENALTY = 6,
    REMOVED_FROM_FORMATION_LAP = 7,
    PARKED_TOO_LONG_TIMER = 8,
    TYRE_REGULATIONS = 9,
    THIS_LAP_INVALIDATED = 10,
    THIS_AND_NEXT_LAP_INVALIDATED = 11,
    THIS_LAP_INVALIDATED_WITHOUT_REASON = 12,
    THIS_AND_NEXT_LAP_INVALIDATED_WITHOUT_REASON = 13,
    THIS_AND_PREVIOUS_LAP_INVALIDATED = 14,
    THIS_AND_PREVIOUS_LAP_INVALIDATED_WITHOUT_REASON = 15,
    RETIRED_PENALTY = 16,
    BLACK_FLAG_TIMER_PENALTY = 17,
};

PenaltyTypeID getPenaltyTypeID(const uint8_t penaltyTypeID);

enum InfringementTypeID {
    BLOCKING_BY_DRIVING_SLOW = 0,
    BLOCKING_BY_WRONG_WAY_DRIVING = 1,
    REVERSING_OFF_THE_START_LINE = 2,
    BIG_COLLISION = 3,
    SMALL_COLLISION = 4,
    COLLISION_FAILED_TO_HAND_BACK_POSITION_SINGLE = 5,
    COLLISION_FAILED_TO_HAND_BACK_POSITION_MULTIPLE = 6,
    CORNER_CUTTING_GAINED_TIME = 7,
    CORNER_CUTTING_OVERTAKE_SINGLE = 8,
    CORNER_CUTTING_OVERTAKE_MULTIPLE = 9,
    CROSSED_PITLANE_EXIT = 10,
    IGNORING_BLUE_FLAGS = 11,
    IGNORING_YELLOW_FLAGS = 12,
    IGNORING_DRIVE_THROUGH = 13,
    TOO_MANY_DRIVE_THROUGHS = 14,
    DRIVE_THROUGH_REMINDER_SERVE_WITHIN_N_LAPS = 15,
    DRIVE_THROUGH_REMINDER_SERVE_THIS_LAP = 16,
    PITLANE_SPEEDING = 17,
    PARKED_FOR_TOO_LONG = 18,
    IGNORING_TYRE_REGULATIONS = 19,
    TOO_MANY_PENALTIES = 20,
    MULTIPLE_WARNINGS = 21,
    APPROACHING_DISQUALIFICATION = 22,
    TYRE_REGULATIONS_SELECT_SINGLE = 23,
    TYRE_REGULATIONS_SELECT_MULTIPLE = 24,
    LAP_INVALIDATED_CORNER_CUTTING = 25,
    LAP_INVALIDATED_RUNNING_WIDE = 26,
    CORNER_CUTTING_RAN_WIDE_GAINED_TIME_MINOR = 27,
    CORNER_CUTTING_RAN_WIDE_GAINED_TIME_SIGNIFICANT = 28,
    CORNER_CUTTING_RAN_WIDE_GAINED_TIME_EXTREME = 29,
    LAP_INVALIDATED_WALL_RIDING = 30,
    LAP_INVALIDATED_FLASHBACK_USED = 31,
    LAP_INVALIDATED_RESET_TO_TRACK = 32,
    BLOCKING_THE_PITLANE = 33,
    JUMP_START = 34,
    SAFETY_CAR_TO_CAR_COLLISION = 35,
    SAFETY_CAR_ILLEGAL_OVERTAKE = 36,
    SAFETY_CAR_EXCEEDING_ALLOWED_PACE = 37,
    VIRTUAL_SAFETY_CAR_EXCEEDING_ALLOWED_PACE = 38,
    FORMATION_LAP_BELOW_ALLOWED_SPEED = 39,
    FORMATION_LAP_PARKING = 40,
    RETIRED_MECHANICAL_FAILURE = 41,
    RETIRED_TERMINALLY_DAMAGED = 42,
    SAFETY_CAR_FALLING_TOO_FAR_BACK = 43,
    BLACK_FLAG_TIMER_INFRINGEMENT = 44,
    UNSERVED_STOP_AND_GO_PENALTY = 45,
    UNSERVED_DRIVE_THROUGH_PENALTY = 46,
    ENGINE_COMPONENT_CHANGE = 47,
    GEARBOX_CHANGE = 48,
    PARC_FERME_CHANGE = 49,
    LEAGUE_GRID_PENALTY = 50,
    RETRY_PENALTY = 51,
    ILLEGAL_TIME_GAIN = 52,
    MANDATORY_PITSTOP = 53,
    ATTRIBUTE_ASSIGNED = 54,
};

InfringementTypeID getInfringementTypeID(const uint8_t infringementTypeID);

enum Weather {
    CLEAR = 0,
    LIGHT_CLOUD = 1,
    OVERCAST = 2,
    LIGHT_RAIN = 3,
    HEAVY_RAIN = 4,
    STORM = 5,
};

Weather getWeather(const uint8_t weather);
std::string getWeatherString(Weather weather);

enum SessionType {
    UNKNOWN = 0,
    P1 = 1,
    P2 = 2,
    P3 = 3,
    SHORT_P = 4,
    Q1 = 5,
    Q2 = 6,
    Q3 = 7,
    SHORT_Q = 8,
    ONE_SHOT_Q = 9,
    R = 10,
    R2 = 11,
    R3 = 12,
    TIME_TRIAL_SESSION_TYPE = 13,
};

SessionType getSessionType(const uint8_t sessionType);
std::string getSessionString(SessionType sessionType);

enum Flag {
    INVALID_UNKNOWN = -1,
    NO_FLAG = 0,
    GREEN = 1,
    BLUE = 2,
    YELLOW = 3,
    RED = 4,
};

Flag getFlag(const int8_t flag);

enum Formula {
    F1_MODERN = 0,
    F1_CLASSIC = 1,
    F2 = 2,
    F1_GENERIC = 3,
    BETA = 4,
    SUPERCARS = 5,
    ESPORTS = 6,
    F2_2021 = 7,
};

Formula getFormula(const uint8_t formula);

enum SafetyCarStatus {
    NO_SAFETY_CAR = 0,
    FULL_SAFETY_CAR = 1,
    VIRTUAL_SAFETY_CAR = 2,
    FORMATION_LAP = 3,
};

SafetyCarStatus getSafetyCarStatus(const uint8_t safetyCarStatus);

enum SessionLength {
    NO_SESSION = 0,
    VERY_SHORT = 2,
    SHORT = 3,
    MEDIUM = 4,
    MEDIUM_LONG = 5,
    LONG = 6,
    FULL_SESSION = 7,
};

SessionLength getSessionLength(const uint8_t sessionLength);

enum PitStatus {
    NOT_PITTING = 0,
    PITTING = 1,
    IN_PIT_LANE = 2,
};

PitStatus getPitStatus(const uint8_t pitStatus);

enum Sector {
    SECTOR_1 = 0,
    SECTOR_2 = 1,
    SECTOR_3 = 2,
};

Sector getSector(const uint8_t sector);

enum DriverStatus {
    IN_GARAGE = 0,
    FLYING_LAP = 1,
    IN_LAP = 2,
    OUT_LAP = 3,
    ON_TRACK = 4,
};

DriverStatus getDriverStatus(const uint8_t driverStatus);

enum ResultStatus {
    INVALID = 0,
    INACTIVE = 1,
    ACTIVE = 2,
    FINISHED = 3,
    DID_NOT_FINISH = 4,
    DISQUALIFIED_RESULT = 5,
    NOT_CLASSIFIED = 6,
    RETIRED_RESULT = 7,
};

ResultStatus getResultStatus(const uint8_t resultStatus);

enum FuelMix {
    LEAN = 0,
    STANDARD = 1,
    RICH = 2,
    MAX = 3,
};

FuelMix getFuelMix(const uint8_t fuelMix);

enum ActualTyreCompound {
    // F1 Modern
    C5 = 16,
    C4 = 17,
    C3 = 18,
    C2 = 19,
    C1 = 20,
    INTER = 7,
    WET = 8,

    // F1 Classic
    DRY_CLASSIC = 9,
    WET_CLASSIC = 10,

    // F2
    SUPER_SOFT = 11,
    SOFT = 12,
    MEDIUM_TYRE = 13,
    HARD = 14,
    WET_F2 = 15,
};

ActualTyreCompound getActualTyreCompound(const uint8_t actualTyreCompound);

std::string getActualTyreName(ActualTyreCompound tyreCompound);

enum VisualTyreCompound
{
    // F1 Modern and Classic
    SOFT_VISUAL = 16,
    MEDIUM_VISUAL = 17,
    HARD_VISUAL = 18,
    INTER_VISUAL = 7,
    WET_VISUAL = 8,

    // F2 - 2019
    WET_F2_VISUAL = 15,
    SUPER_SOFT_F2_VISUAL = 19,
    SOFT_F2_VISUAL = 20,
    MEDIUM_F2_VISUAL = 21,
    HARD_F2_VISUAL = 22,
};

VisualTyreCompound getVisualTyreCompound(const uint8_t visualTyreCompound);

Colour getVisualTyreColour(VisualTyreCompound tyreCompound);

enum ERSDeployMode {
    NO_ERS = 0,
    MEDIUM_ERS = 1,
    HOTLAP = 2,
    OVERTAKE = 3,
};

ERSDeployMode getERSDeployMode(const uint8_t ersDeployMode);


enum StintType {
    RACE_SIMULATION = 0,
    QUALIFYING_SIMULATION = 1,
};

const std::vector<StintType> stintTypes = {
    RACE_SIMULATION,
    QUALIFYING_SIMULATION,
};

std::string getStintTypeString(StintType stintType);

#endif // ENUMS_HPP

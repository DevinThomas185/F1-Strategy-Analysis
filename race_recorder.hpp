#ifndef RACE_RECORDER_HPP
#define RACE_RECORDER_HPP

#include <string>
#include <optional>
#include <fstream>
#include "packet_handler.hpp"
#include "enums.hpp"
#include "compiled_protos/RaceWeekend.pb.h"
#include <QObject>

class RaceRecorder : public QObject, public PacketHandlerInterface {
    Q_OBJECT
public:
    explicit RaceRecorder(QObject *parent = nullptr);

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

    void writeRaceToPB();
    void writeRaceToJSON();
    void savePendingData();

    void startStint(StintType stintType);

private:    
    bool currentlyRecording = false;

    RaceWeekend raceWeekend;
    uint8_t playerCarIndex;
    
    std::optional<SessionType> currentSession;
    std::optional<TrackID> trackId;

    std::optional<StintType> currentStintType;

    Practice* currentPractice;
    Stint* currentStint;
    Setup* currentSetup;
    Lap* currentLap;

    LapData lastLapData;
    CarTelemetryData lastTelemetryData;
    CarDamageData lastDamageData;
    CarStatusData lastStatusData;
    PacketMotionData lastMotionPacket; // Needs to be packet to retain extra player car only data

    uint8_t currentLapNum = 1;
    float currentDistance;
    DriverStatus driverStatus = DriverStatus::IN_GARAGE;

    void addTelemetryDataToLap();


    bool isMetadataSetUp() {
        return trackId.has_value() && currentSession.has_value();
    }

    std::string getFileName() {
//        auto now = std::chrono::system_clock::now();
//        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
//        std::tm* timeinfo = std::localtime(&currentTime);
//        char buffer[80];
//        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
//        return getTrackString(trackId.value()) + " " + buffer;
        return getTrackString(trackId.value());
    }

signals:
    void StintStarted(StintType);
    void StintEnded(StintType);
};

#endif  // RACE_RECORDER_HPP

#ifndef UDP_UPDATER_H
#define UDP_UPDATER_H

#include <QThread>
#include <QMainWindow>
#include <QWidget>
#include <vector>

#include "udp_listener.hpp"
#include "packet_handler.hpp"
#include "gui_types.hpp"
#include "race_recorder.hpp"

class UDPUpdater : public QThread, public PacketHandlerInterface
{
    Q_OBJECT
public:
    explicit UDPUpdater(QObject *parent = nullptr);
    void run();
    UDPListener udp_listener;
    bool enable_listening = false;

    void handleMotionPacket(const PacketData& packet);
    void handleSessionPacket(const PacketData& packet);
    void handleLapPacket(const PacketData& packet);
    void handleEventPacket(const PacketData& packet);
    void handleParticipantsPacket(const PacketData& packet);
    void handleCarSetupPacket(const PacketData& packet);
    void handleCarTelemetryPacket(const PacketData& packet);
    void handleCarStatusPacket(const PacketData& packet);
    void handleFinalClassificationPacket(const PacketData& packet);
    void handleLobbyInfoPacket(const PacketData& packet);
    void handleCarDamagePacket(const PacketData& packet);
    void handleSessionHistoryPacket(const PacketData& packet);

    bool participantsReceived = false;
    uint8_t driverSelected = 0;
    RaceRecorder raceRecorder;

private:

    std::vector<ParticipantData> participants_;

    bool changedParticipants(const PacketParticipantsData pd);
    std::string handlePenaltyIssued(const PacketEventData event);
    std::string handleInfringement(const EventDataDetails eventDetails);

    uint8_t motionDriverSelected = 0;
    uint8_t totalLaps = 0;
    uint16_t trackLength = 0;
    SessionType sessionType = UNKNOWN;
    TrackID track = SILVERSTONE;

    // Map of carIdx -> (map of lap -> (map of lapDistance -> currentLapTimeinMS)
    std::array<std::array<std::map<uint16_t, uint32_t>, 100>, 22> driverIntervalTimes;

signals:
    void ParticipantsUpdate(Participants);
    void EventAnnouncementUpdate(EventAnnouncement);
    void PositionsTableUpdate(PositionsTable);
    void WeatherUpdate(WeatherData);
    void DamageUpdate(DamageData);
    void TemperaturePressureUpdate(TemperaturePressureData);
    void WheelTelemetryUpdate(WheelTelemetryData);
    void TotalLapsUpdate(uint8_t);
    void TrackLengthUpdate(uint16_t);
    void TrackUpdate(TrackID);
    void WheelLapUpdate(WheelLapData);
    void LapDistanceUpdate(float);
    void WheelStatusUpdate(WheelStatusData);
    void PlotTelemetryUpdate(PlotTelemetryData);
    void LapHistoryTableUpdate(LapHistoryTable);
    void PositionalDataMapUpdate(PositionalDataMap);
    void SessionTypeUpdate(SessionType);
    void SafetyCarStatusUpdate(SafetyCarStatus);

public slots:
};

#endif // UDP_UPDATER_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "udp_updater.h"
#include "gui_types.hpp"
#include "enums.hpp"
#include "udpsettings.h"
#include "race_strategy_prediction.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    UDPUpdater *updater;

private:
    Ui::MainWindow *ui;
    UDPSettings udpSettings;
    int timerId;

    uint8_t playerCarIdx;
    uint8_t secondCarIdx;
    Participants mw_participants;

    void setupPlots();
    void replotTelemetryPlots();

    QVector<double> distancePlotValues;
    QVector<double> speedPlotValues;
    QVector<double> throttlePlotValues;
    QVector<double> brakePlotValues;
    QVector<double> rpmPlotValues;
    QVector<double> gearPlotValues;
    QVector<double> steeringPlotValues;

    float currentLapDistance = 0;

    uint32_t targetLapTimeMS = 0;

    uint16_t trackLength = 0;
    uint8_t totalLaps = 0;
    TrackID trackId;
    void setTrackMap();
    double zoomStart = 0;
    double zoomEnd = trackLength;
    void setZooms();

    StintType selectedStint = stintTypes[0];

    RaceWeekend loadedRaceWeekend;
    void updateLoadedRaceWeekendData();

    Practice selectedPractice;
    google::protobuf::RepeatedPtrField<Stint> selectedLoadedStints;
    Stint selectedLoadedStint;

    void updateRecordedTelemetryGraphs();
    Lap selectedLoadedLap1;
    Lap selectedLoadedLap2;

    uint8_t predictedLaps = 0;

    QVector<double> fuelUsageStrategyPlotValues;
    QVector<double> lapStrategyPlotValues;

protected:
    void timerEvent(QTimerEvent *event);

public slots:
    void onParticipantsUpdate(Participants);
    void onEventAnnouncementUpdate(EventAnnouncement);
    void onPositionsTableUpdate(PositionsTable);
    void onWeatherUpdate(WeatherData);
    void onDamageUpdate(DamageData);
    void onTemperaturePressureUpdate(TemperaturePressureData);
    void onWheelTelemetryUpdate(WheelTelemetryData);
    void onPlotTelemetryUpdate(PlotTelemetryData);
    void onTotalLapsUpdate(uint8_t);
    void onTrackLengthUpdate(uint16_t);
    void onTrackUpdate(TrackID);
    void onWheelLapUpdate(WheelLapData);
    void onLapDistanceUpdate(float);
    void onWheelStatusUpdate(WheelStatusData);
    void onLapHistoryTableUpdate(LapHistoryTable);
    void onPositionalDataMapUpdate(PositionalDataMap);
    void onSessionTypeUpdate(SessionType);
    void onStintStarted(StintType);
    void onStintEnded(StintType);
    void onSafetyCarStatusUpdate(SafetyCarStatus);
    void onCurrentSetupUpdate(CurrentCarSetup);
    void onDriverAheadAndBehindUpdate(LiveStrategyData);
    void onStrategyUpdate(Strategy);


private slots:
    void on_ddSelectDriver_currentIndexChanged(int index);
    void on_btnStartStopUDP_clicked();
    void on_btnPlus10Seconds_clicked();
    void on_btnMinus10Seconds_clicked();
    void on_btnPlus1Second_clicked();
    void on_btnMinus1Second_clicked();
    void on_btnPlus100MS_clicked();
    void on_btnMinus100MS_clicked();
    void on_btnResetZoom_clicked();
    void on_sldTelemetryEndZoom_valueChanged(int value);
    void on_sldTelemetryStartZoom_valueChanged(int value);
    void on_btnSaveRecording_clicked();
    void on_btnLoadRecording_clicked();
    void on_ddSelectStint_currentIndexChanged(int index);
    void on_btnStartStint_clicked();
    void on_ddSelectLoadedSession_currentIndexChanged(int index);
    void on_ddSelectLoadedStintType_currentIndexChanged(int index);
    void on_ddSelectLoadedStintNumber_currentIndexChanged(int index);
    void on_ddSelectLoadedLapNumberTelemetryLap1_currentIndexChanged(int index);
    void on_ddSelectLoadedLapNumberTelemetryLap2_currentIndexChanged(int index);
    void on_actionUDP_Settings_triggered();
    void on_btnPredictStrategy_clicked();
};
#endif // MAINWINDOW_H

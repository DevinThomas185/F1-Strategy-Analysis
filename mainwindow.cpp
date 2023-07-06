#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "formatting.hpp"
#include "compiled_protos/RaceWeekend.pb.h"

#include <ostream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <QTableWidgetItem>

#define TYRE_MIN_TEMP 40
#define TYRE_OPT_TEMP 90
#define TYRE_MAX_TEMP 160
#define BRAKE_MIN_TEMP 100
#define BRAKE_OPT_TEMP 500
#define BRAKE_MAX_TEMP 1100
#define ENGINE_MIN_TEMP 90
#define ENGINE_OPT_TEMP 120
#define ENGINE_MAX_TEMP 130
#define PRESSURE_THRESHOLD 3

Colour COLD_BLUE = Colour(4, 212, 212);
Colour HEALTHY_GREEN = Colour(27, 171, 5);
Colour BROKEN_RED = Colour(171, 5, 5);

Colour GREEN_FLAG = Colour(6, 204, 42);
Colour YELLOW_FLAG = Colour(214, 197, 2);
Colour BLUE_FLAG = Colour(0, 76, 207);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timerId = startTimer(100);

    setWindowTitle("F1 Analysis - Devin Thomas");

    updater = new UDPUpdater();
    udpSettings.updater = updater;
    connect(updater, SIGNAL(ParticipantsUpdate(Participants)), this, SLOT(onParticipantsUpdate(Participants)));
    connect(updater, SIGNAL(EventAnnouncementUpdate(EventAnnouncement)), this, SLOT(onEventAnnouncementUpdate(EventAnnouncement)));
    connect(updater, SIGNAL(PositionsTableUpdate(PositionsTable)), this, SLOT(onPositionsTableUpdate(PositionsTable)));
    connect(updater, SIGNAL(WeatherUpdate(WeatherData)), this, SLOT(onWeatherUpdate(WeatherData)));
    connect(updater, SIGNAL(DamageUpdate(DamageData)), this, SLOT(onDamageUpdate(DamageData)));
    connect(updater, SIGNAL(TemperaturePressureUpdate(TemperaturePressureData)), this, SLOT(onTemperaturePressureUpdate(TemperaturePressureData)));
    connect(updater, SIGNAL(WheelTelemetryUpdate(WheelTelemetryData)), this, SLOT(onWheelTelemetryUpdate(WheelTelemetryData)));
    connect(updater, SIGNAL(PlotTelemetryUpdate(PlotTelemetryData)), this, SLOT(onPlotTelemetryUpdate(PlotTelemetryData)));
    connect(updater, SIGNAL(TotalLapsUpdate(uint8_t)), this, SLOT(onTotalLapsUpdate(uint8_t)));
    connect(updater, SIGNAL(TrackLengthUpdate(uint16_t)), this, SLOT(onTrackLengthUpdate(uint16_t)));
    connect(updater, SIGNAL(TrackUpdate(TrackID)), this, SLOT(onTrackUpdate(TrackID)));
    connect(updater, SIGNAL(WheelLapUpdate(WheelLapData)), this, SLOT(onWheelLapUpdate(WheelLapData)));
    connect(updater, SIGNAL(LapDistanceUpdate(float)), this, SLOT(onLapDistanceUpdate(float)));
    connect(updater, SIGNAL(WheelStatusUpdate(WheelStatusData)), this, SLOT(onWheelStatusUpdate(WheelStatusData)));
    connect(updater, SIGNAL(LapHistoryTableUpdate(LapHistoryTable)), this, SLOT(onLapHistoryTableUpdate(LapHistoryTable)));
    connect(updater, SIGNAL(PositionalDataMapUpdate(PositionalDataMap)), this, SLOT(onPositionalDataMapUpdate(PositionalDataMap)));
    connect(updater, SIGNAL(SessionTypeUpdate(SessionType)), this, SLOT(onSessionTypeUpdate(SessionType)));
    connect(updater, SIGNAL(SafetyCarStatusUpdate(SafetyCarStatus)), this, SLOT(onSafetyCarStatusUpdate(SafetyCarStatus)));
    connect(updater, SIGNAL(CurrentSetupUpdate(CurrentCarSetup)), this, SLOT(onCurrentSetupUpdate(CurrentCarSetup)));
    connect(updater, SIGNAL(DriverAheadAndBehindUpdate(LiveStrategyData)), this, SLOT(onDriverAheadAndBehindUpdate(LiveStrategyData)));
    connect(&updater->raceRecorder, SIGNAL(StintStarted(StintType)), this, SLOT(onStintStarted(StintType)));
    connect(&updater->raceRecorder, SIGNAL(StintEnded(StintType)), this, SLOT(onStintEnded(StintType)));

    // Positions Table
    ui->tblPositionsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Stretch the columns
    ui->tblPositionsTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Stretch the rows

    // Lap History Table
    ui->tblLapHistory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Stretch the columns

    // Recorded Lap Table
    ui->tblRecordedLaps->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Stretch the columns

    // Set Stint Types
    for (auto stintType: stintTypes) {
        QString s = QString::fromStdString(getStintTypeString(stintType));
        ui->ddSelectStint->addItem(s);
        ui->ddSelectLoadedStintType->addItem(s);
    }
    ui->ddSelectStint->setCurrentIndex(0);
    ui->ddSelectLoadedStintType->setCurrentIndex(0);

    // TODO: Don't hardcode this
    ui->ddSelectLoadedSession->addItem("Practice 1");
    ui->ddSelectLoadedSession->addItem("Practice 2");
    ui->ddSelectLoadedSession->addItem("Practice 3");
    ui->ddSelectLoadedSession->setCurrentIndex(0);

    setupPlots();
}

MainWindow::~MainWindow()
{
    killTimer(timerId);
    delete ui;
}


void MainWindow::setupPlots() {
    // Speed Plot
    ui->pltSpeed->addGraph();
    ui->pltSpeed->yAxis->setLabel("Speed (MPH)");
    ui->pltSpeed->yAxis->setRange(0, 250);
    ui->pltRecordedSpeed->addGraph();
    ui->pltRecordedSpeed->addGraph();
    ui->pltRecordedSpeed->graph(1)->setPen(QPen(Qt::red));
    ui->pltRecordedSpeed->yAxis->setLabel("Speed (MPH)");
    ui->pltRecordedSpeed->yAxis->setRange(0, 250);

    // Throttle Plot
    ui->pltThrottle->addGraph();
    ui->pltThrottle->yAxis->setLabel("Throttle (%)");
    ui->pltThrottle->yAxis->setRange(0, 100);
    ui->pltRecordedThrottle->addGraph();
    ui->pltRecordedThrottle->addGraph();
    ui->pltRecordedThrottle->graph(1)->setPen(QPen(Qt::red));
    ui->pltRecordedThrottle->yAxis->setLabel("Throttle (%)");
    ui->pltRecordedThrottle->yAxis->setRange(0, 100);

    // Brake Plot
    ui->pltBrake->addGraph();
    ui->pltBrake->yAxis->setLabel("Brake (%)");
    ui->pltBrake->yAxis->setRange(0, 100);
    ui->pltRecordedBrake->addGraph();
    ui->pltRecordedBrake->addGraph();
    ui->pltRecordedBrake->graph(1)->setPen(QPen(Qt::red));
    ui->pltRecordedBrake->yAxis->setLabel("Brake (%)");
    ui->pltRecordedBrake->yAxis->setRange(0, 100);

    // RPM Plot
    ui->pltRPM->addGraph();
    ui->pltRPM->yAxis->setLabel("RPM");
    ui->pltRPM->yAxis->setRange(3000, 14000);
    ui->pltRecordedRPM->addGraph();
    ui->pltRecordedRPM->addGraph();
    ui->pltRecordedRPM->graph(1)->setPen(QPen(Qt::red));
    ui->pltRecordedRPM->yAxis->setLabel("RPM");
    ui->pltRecordedRPM->yAxis->setRange(3000, 14000);

    // Gear Plot
    ui->pltGear->addGraph();
    ui->pltGear->yAxis->setLabel("Gear");
    ui->pltGear->yAxis->setRange(-1, 8);
    ui->pltRecordedGear->addGraph();
    ui->pltRecordedGear->addGraph();
    ui->pltRecordedGear->graph(1)->setPen(QPen(Qt::red));
    ui->pltRecordedGear->yAxis->setLabel("Gear");
    ui->pltRecordedGear->yAxis->setRange(-1, 8);

    // Steering Plot
    ui->pltSteering->addGraph();
    ui->pltSteering->yAxis->setLabel("Steering (%)");
    ui->pltSteering->yAxis->setRange(-100, 100);
    ui->pltRecordedSteering->addGraph();
    ui->pltRecordedSteering->addGraph();
    ui->pltRecordedSteering->graph(1)->setPen(QPen(Qt::red));
    ui->pltRecordedSteering->yAxis->setLabel("Steering (%)");
    ui->pltRecordedSteering->yAxis->setRange(-100, 100);

    // Track Map (not track specific settings)
    ui->pltTrackMap->xAxis->setTicks(false);
    ui->pltTrackMap->yAxis->setTicks(false);
    ui->pltTrackMap->xAxis->grid()->setVisible(false);
    ui->pltTrackMap->yAxis->grid()->setVisible(false);

    // Fuel Usage
    ui->pltFuelUsage->addGraph();
    ui->pltFuelUsage->yAxis->setLabel("Fuel (kg)");
//    ui->pltFuelUsage->yAxis->setRange(0, 110);

    // Tyre Degradation
    ui->pltTyreDegradation->addGraph();
    ui->pltTyreDegradation->yAxis->setLabel("Tyre Damage (%)");
    ui->pltFuelUsage->yAxis->setRange(0, 100);

    replotTelemetryPlots();
}

void MainWindow::timerEvent(QTimerEvent *event) {
    replotTelemetryPlots();

    ui->pltTrackMap->replot();
}

void MainWindow::replotTelemetryPlots() {
    ui->pltSpeed->graph(0)->setData(distancePlotValues, speedPlotValues);
    ui->pltSpeed->replot();

    ui->pltThrottle->graph(0)->setData(distancePlotValues, throttlePlotValues);
    ui->pltThrottle->replot();

    ui->pltBrake->graph(0)->setData(distancePlotValues, brakePlotValues);
    ui->pltBrake->replot();

    ui->pltRPM->graph(0)->setData(distancePlotValues, rpmPlotValues);
    ui->pltRPM->replot();

    ui->pltGear->graph(0)->setData(distancePlotValues, gearPlotValues);
    ui->pltGear->replot();

    ui->pltSteering->graph(0)->setData(distancePlotValues, steeringPlotValues);
    ui->pltSteering->replot();
}

void MainWindow::onLapDistanceUpdate(float lapDistance) {
    if (lapDistance < currentLapDistance) {
        distancePlotValues.clear();
        speedPlotValues.clear();
        throttlePlotValues.clear();
        brakePlotValues.clear();
        rpmPlotValues.clear();
        gearPlotValues.clear();
        steeringPlotValues.clear();
    }
    currentLapDistance = lapDistance;
}

void MainWindow::setZooms() {
    ui->pltSpeed->xAxis->setRange(zoomStart, zoomEnd);
    ui->pltThrottle->xAxis->setRange(zoomStart, zoomEnd);
    ui->pltBrake->xAxis->setRange(zoomStart, zoomEnd);
    ui->pltRPM->xAxis->setRange(zoomStart, zoomEnd);
    ui->pltGear->xAxis->setRange(zoomStart, zoomEnd);
    ui->pltSteering->xAxis->setRange(zoomStart, zoomEnd);

    ui->lblTelemetryStartZoom->setText(QString::number(zoomStart) + "m");
    ui->lblTelemetryEndZoom->setText(QString::number(zoomEnd) + "m");
}

void MainWindow::onTrackLengthUpdate(uint16_t tl) {
    trackLength = tl;
    zoomEnd = tl;
    ui->sldTelemetryEndZoom->setValue(zoomEnd);

    on_btnResetZoom_clicked(); // Do the same as a reset
}

void MainWindow::onTrackUpdate(TrackID tId) {
    trackId = tId;

    // Set track map dimensions and image
    setTrackMap();
}

void MainWindow::setTrackMap() {
    ui->pltTrackMap->clearGraphs();
    ui->lblRaceWeekend->setText(QString::fromStdString(getTrackString(trackId)));

    int minX, maxX, minY, maxY = 0;
    std::string trackImageName;

    switch (trackId) {
    case MELBOURNE:
        minX = -1000;
        maxX = 1000;
        minY = -800;
        maxY = 800;
        trackImageName = "melbourne.jpg";
        break;
    case PAUL_RICARD:
        break;
    case SHANGHAI:
        break;
    case SAKHIR:
        minX = -800;
        maxX = 800;
        minY = -800;
        maxY = 800;
        trackImageName = "sakhir.jpg";
        break;
    case CATALUNYA:
        break;
    case MONACO:
        break; 
    case MONTREAL:
        break;
    case SILVERSTONE:
        break;
    case HOCKENHEIM:
        break;
    case HUNGARORING:
        break;
    case SPA:
        break;
    case MONZA:
        break;
    case SINGAPORE:
        break;
    case SUZUKA:
        break;
    case ABU_DHABI:
        break;
    case TEXAS:
        break;
    case BRAZIL:
        break;
    case AUSTRIA:
        break;
    case SOCHI:
        break;
    case MEXICO:
        break;
    case BAKU:
        break;
    case SAKHIR_SHORT:
        break;
    case SILVERSTONE_SHORT:
        break;
    case TEXAS_SHORT:
        break;
    case SUZUKA_SHORT:
        break;
    case HANOI:
        break;
    case ZANDVOORT:
        break;
    case IMOLA:
        break;
    case PORTIMAO:
        break;
    case JEDDAH:
        minX = -1700;
        maxX = 1700;
        minY = -700;
        maxY = 700;
        trackImageName = "jeddah.jpg";
        break;
    case MIAMI:
        break;
    }

    ui->pltTrackMap->addGraph();

    QCPScatterStyle scatterStyle;
    scatterStyle.setShape(QCPScatterStyle::ssCircle);
    scatterStyle.setSize(6);
    scatterStyle.setPen(QPen(Qt::blue));
    ui->pltTrackMap->graph(0)->setScatterStyle(scatterStyle);
    ui->pltTrackMap->graph(0)->setLineStyle(QCPGraph::lsNone);

    ui->pltTrackMap->xAxis->setRange(minX, maxX);
    ui->pltTrackMap->yAxis->setRange(minY, maxY);

    QCPItemPixmap *background = new QCPItemPixmap(ui->pltTrackMap);
    background->setPixmap(QPixmap(QString::fromStdString(":/images/tracks/" + trackImageName))); // Set the path to your image
    background->topLeft->setCoords(minX, maxY); // Set the top-left coordinates of the image
    background->bottomRight->setCoords(maxX, minY); // Set the bottom-right coordinates of the image
    background->setScaled(true, Qt::IgnoreAspectRatio);
}

void MainWindow::on_btnResetZoom_clicked()
{
    zoomStart = 0;
    zoomEnd = trackLength;

    ui->sldTelemetryStartZoom->setRange(zoomStart, zoomEnd-1);
    ui->sldTelemetryStartZoom->setValue(zoomStart);
    ui->sldTelemetryEndZoom->setRange(zoomStart+1, zoomEnd);
    ui->sldTelemetryEndZoom->setValue(zoomEnd);

    setZooms();
}

void MainWindow::on_sldTelemetryStartZoom_valueChanged(int value)
{
    zoomStart = value;
    setZooms();
}

void MainWindow::on_sldTelemetryEndZoom_valueChanged(int value)
{
    zoomEnd = value;
    setZooms();
}





void MainWindow::onPlotTelemetryUpdate(PlotTelemetryData plotTelemetry) {
    distancePlotValues.append(currentLapDistance);
    speedPlotValues.append(plotTelemetry.speed);
    throttlePlotValues.append(plotTelemetry.throttle);
    brakePlotValues.append(plotTelemetry.brake);
    rpmPlotValues.append(plotTelemetry.rpm);
    gearPlotValues.append(plotTelemetry.gear);
    steeringPlotValues.append(plotTelemetry.steering);
}

void MainWindow::onPositionalDataMapUpdate(PositionalDataMap positionalDataMap) {
    // Return if the map is not set yet
    if (ui->pltTrackMap->graphCount() == 0) return;

    // Remove labels
    for (int i = ui->pltTrackMap->itemCount() - 1; i >= 0; --i)
    {
        if (!qobject_cast<QCPItemPixmap *>(ui->pltTrackMap->item(i))) {
            ui->pltTrackMap->removeItem(i);
        }
    }
    ui->pltTrackMap->graph(0)->data()->clear(); // Remove positions

    // Plot z/x to rotate the map
    for (size_t i = 0; i < positionalDataMap.size(); i++) {
        PositionalData pd = positionalDataMap[i]; // SHOULD BE i // CHANGE BACK
        ui->pltTrackMap->graph(0)->addData(pd.z, pd.x);

        // Add driver name label at each data point
        QCPItemText *label = new QCPItemText(ui->pltTrackMap);
        label->setText(QString::fromStdString(pd.driverLabel));
        label->setColor(QColor(QString::fromStdString(pd.driverColour.getHexCode())));
        label->setBrush(QBrush(QColor("grey")));
        label->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);
        label->position->setCoords(pd.z, pd.x);
    }
}



void MainWindow::onParticipantsUpdate(Participants participants) {
    ui->ddSelectDriver->clear();

    mw_participants = participants;
    playerCarIdx = participants.playerCarIdx;
    secondCarIdx = participants.secondCarIdx;

    for (size_t i = 0; i < participants.participants.size(); i++) {
        ui->ddSelectDriver->addItem(QString::fromStdString(participants.participants[i].name));
    }
    ui->ddSelectDriver->setCurrentIndex(playerCarIdx);
}

void MainWindow::onEventAnnouncementUpdate(EventAnnouncement eventString)
{
    ui->lblEventAnnouncement->setText(QString::fromStdString(eventString));
}

void MainWindow::onPositionsTableUpdate(PositionsTable positionsTable)
{
    QFont font = QFont();
    font.setPointSize(18);
    while (ui->tblPositionsTable->rowCount() < positionsTable.size()) {
        ui->tblPositionsTable->insertRow(0);
    }

    for (int r = 0; r < ui->tblPositionsTable->rowCount(); r++) {
        PositionsTableRow row = positionsTable[r];

        QTableWidgetItem *position = new QTableWidgetItem(QString::fromStdString(row.position));
        position->setFlags(position->flags() &  ~Qt::ItemIsEditable);
        position->setTextAlignment(Qt::AlignCenter);
        position->setFont(font);

        if (row.position == "1") position->setForeground(QBrush(QColor("#f0c800")));
        if (row.position == "2") position->setForeground(QBrush(QColor("#b3b3b3")));
        if (row.position == "3") position->setForeground(QBrush(QColor("#e35700")));

        ui->tblPositionsTable->setItem(r, 0, position);

        QTableWidgetItem *driver = new QTableWidgetItem(QString::fromStdString(row.driver));
        driver->setFlags(driver->flags() &  ~Qt::ItemIsEditable);
        driver->setFont(font);

        if (playerCarIdx == row._carIdx) driver->setForeground(QBrush(QColor("#6ec0fa")));
        if (secondCarIdx == row._carIdx) driver->setForeground(QBrush(QColor("#e30510")));

        ui->tblPositionsTable->setItem(r, 1, driver);

        std::string pc = row.positionChange > 0 ? "+" + std::to_string(row.positionChange) :
                         row.positionChange == 0 ? "0" : std::to_string(row.positionChange);

        QTableWidgetItem *positionChange = new QTableWidgetItem(QString::fromStdString(pc));
        positionChange->setFlags(positionChange->flags() &  ~Qt::ItemIsEditable);
        positionChange->setTextAlignment(Qt::AlignCenter);
        positionChange->setFont(font);
        if (row.positionChange > 0) positionChange->setForeground(QBrush(QColor("#06b800"))); // Gained positions
        if (row.positionChange < 0) positionChange->setForeground(QBrush(QColor("#e60000"))); // Lost positions
        ui->tblPositionsTable->setItem(r, 2, positionChange);

        QTableWidgetItem *sector1 = new QTableWidgetItem(QString::fromStdString(row.sector1));
        sector1->setFlags(sector1->flags() &  ~Qt::ItemIsEditable);
        sector1->setFont(font);
        ui->tblPositionsTable->setItem(r, 3, sector1);

        QTableWidgetItem *sector2 = new QTableWidgetItem(QString::fromStdString(row.sector2));
        sector2->setFlags(sector2->flags() &  ~Qt::ItemIsEditable);
        sector2->setFont(font);
        ui->tblPositionsTable->setItem(r, 4, sector2);

        QTableWidgetItem *lastLap = new QTableWidgetItem(QString::fromStdString(row.lastlap));
        lastLap->setFlags(lastLap->flags() &  ~Qt::ItemIsEditable);
        lastLap->setFont(font);
        ui->tblPositionsTable->setItem(r, 5, lastLap);

        QTableWidgetItem *interval = new QTableWidgetItem(QString::fromStdString(row.interval));
        interval->setFlags(interval->flags() &  ~Qt::ItemIsEditable);
        interval->setFont(font);
        ui->tblPositionsTable->setItem(r, 6, interval);

        QTableWidgetItem *tyreAge = new QTableWidgetItem(QString::number(row.tyreData.tyreAge));
        tyreAge->setFlags(tyreAge->flags() &  ~Qt::ItemIsEditable);
        tyreAge->setTextAlignment(Qt::AlignCenter);
        tyreAge->setFont(font);
        tyreAge->setForeground(QBrush(QColor(QString::fromStdString(getVisualTyreColour(row.tyreData.visualTyreCompound).getHexCode()))));
        ui->tblPositionsTable->setItem(r, 7, tyreAge);
    }
}

void MainWindow::onWeatherUpdate(WeatherData weather) {
    size_t numSamples = weather.size();

    if (numSamples >= 1) {
        ui->gbWeather1->setTitle(QString::fromStdString(weather[0].timeOffset));
        ui->lblWeather1Status->setText(QString::fromStdString(weather[0].status));
        ui->lblWeather1Track->setText(QString::fromStdString(weather[0].trackTemp));
        ui->lblWeather1Air->setText(QString::fromStdString(weather[0].airTemp));
        ui->lblWeather1Rain->setText(QString::fromStdString(weather[0].rainPercent));
    }
    if (numSamples >= 2) {
        ui->gbWeather2->setTitle(QString::fromStdString(weather[1].timeOffset));
        ui->lblWeather2Status->setText(QString::fromStdString(weather[1].status));
        ui->lblWeather2Track->setText(QString::fromStdString(weather[1].trackTemp));
        ui->lblWeather2Air->setText(QString::fromStdString(weather[1].airTemp));
        ui->lblWeather2Rain->setText(QString::fromStdString(weather[1].rainPercent));
    }
    if (numSamples >= 3) {
        ui->gbWeather3->setTitle(QString::fromStdString(weather[2].timeOffset));
        ui->lblWeather3Status->setText(QString::fromStdString(weather[2].status));
        ui->lblWeather3Track->setText(QString::fromStdString(weather[2].trackTemp));
        ui->lblWeather3Air->setText(QString::fromStdString(weather[2].airTemp));
        ui->lblWeather3Rain->setText(QString::fromStdString(weather[2].rainPercent));
    }
    if (numSamples >= 4) {
        ui->gbWeather4->setTitle(QString::fromStdString(weather[3].timeOffset));
        ui->lblWeather4Status->setText(QString::fromStdString(weather[3].status));
        ui->lblWeather4Track->setText(QString::fromStdString(weather[3].trackTemp));
        ui->lblWeather4Air->setText(QString::fromStdString(weather[3].airTemp));
        ui->lblWeather4Rain->setText(QString::fromStdString(weather[3].rainPercent));
    }
    if (numSamples >= 5) {
        ui->gbWeather5->setTitle(QString::fromStdString(weather[4].timeOffset));
        ui->lblWeather5Status->setText(QString::fromStdString(weather[4].status));
        ui->lblWeather5Track->setText(QString::fromStdString(weather[4].trackTemp));
        ui->lblWeather5Air->setText(QString::fromStdString(weather[4].airTemp));
        ui->lblWeather5Rain->setText(QString::fromStdString(weather[4].rainPercent));
    }
    if (numSamples >= 6) {
        ui->gbWeather6->setTitle(QString::fromStdString(weather[5].timeOffset));
        ui->lblWeather6Status->setText(QString::fromStdString(weather[5].status));
        ui->lblWeather6Track->setText(QString::fromStdString(weather[5].trackTemp));
        ui->lblWeather6Air->setText(QString::fromStdString(weather[5].airTemp));
        ui->lblWeather6Rain->setText(QString::fromStdString(weather[5].rainPercent));
    }

    if (numSamples >= 7) {
        ui->gbWeather7->setTitle(QString::fromStdString(weather[6].timeOffset));
        ui->lblWeather7Status->setText(QString::fromStdString(weather[6].status));
        ui->lblWeather7Track->setText(QString::fromStdString(weather[6].trackTemp));
        ui->lblWeather7Air->setText(QString::fromStdString(weather[6].airTemp));
        ui->lblWeather7Rain->setText(QString::fromStdString(weather[6].rainPercent));
    }

    if (numSamples >= 8) {
        ui->gbWeather8->setTitle(QString::fromStdString(weather[7].timeOffset));
        ui->lblWeather8Status->setText(QString::fromStdString(weather[7].status));
        ui->lblWeather8Track->setText(QString::fromStdString(weather[7].trackTemp));
        ui->lblWeather8Air->setText(QString::fromStdString(weather[7].airTemp));
        ui->lblWeather8Rain->setText(QString::fromStdString(weather[7].rainPercent));
    }

    if (numSamples >= 9) {
        ui->gbWeather9->setTitle(QString::fromStdString(weather[8].timeOffset));
        ui->lblWeather9Status->setText(QString::fromStdString(weather[8].status));
        ui->lblWeather9Track->setText(QString::fromStdString(weather[8].trackTemp));
        ui->lblWeather9Air->setText(QString::fromStdString(weather[8].airTemp));
        ui->lblWeather9Rain->setText(QString::fromStdString(weather[8].rainPercent));
    }



}

QString formatPercentage(uint8_t percent) {
    return QString::number(100 - percent) + QString("%");
}

std::string damageColour(uint8_t percent) {
    // Calculate the color interpolation based on the value
    double t = static_cast<double>(percent) / 100.0;
    uint8_t r = static_cast<uint8_t>(HEALTHY_GREEN.r + t * (BROKEN_RED.r - HEALTHY_GREEN.r));
    uint8_t g = static_cast<uint8_t>(HEALTHY_GREEN.g + t * (BROKEN_RED.g - HEALTHY_GREEN.g));
    uint8_t b = static_cast<uint8_t>(HEALTHY_GREEN.b + t * (BROKEN_RED.b - HEALTHY_GREEN.b));

    // Convert RGB values to hex string
    std::stringstream hexStream;
    hexStream << "#" << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(r);
    hexStream << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(g);
    hexStream << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(b);
    return hexStream.str();
}

void MainWindow::onDamageUpdate(DamageData damage) {
    ui->lblRearLeftTyreWearPercent->setText("Wear: " + formatPercentage(damage.rearLeftTyreWearPercent));
    ui->lblRearRightTyreWearPercent->setText("Wear: " + formatPercentage(damage.rearRightTyreWearPercent));
    ui->lblFrontLeftTyreWearPercent->setText("Wear: " + formatPercentage(damage.frontLeftTyreWearPercent));
    ui->lblFrontRightTyreWearPercent->setText("Wear: " + formatPercentage(damage.frontRightTyreWearPercent));

    ui->lblRearLeftTyreDamagePercent->setText("Life: " + formatPercentage(damage.rearLeftTyreDamagePercent));
    ui->wgtRearLeftTyre->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.rearLeftTyreDamagePercent)));
    ui->lblRearRightTyreDamagePercent->setText("Life: " + formatPercentage(damage.rearRightTyreDamagePercent));
    ui->wgtRearRightTyre->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.rearRightTyreDamagePercent)));
    ui->lblFrontLeftTyreDamagePercent->setText("Life: " + formatPercentage(damage.frontLeftTyreDamagePercent));
    ui->wgtFrontLeftTyre->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.frontLeftTyreDamagePercent)));
    ui->lblFrontRightTyreDamagePercent->setText("Life: " + formatPercentage(damage.frontRightTyreDamagePercent));
    ui->wgtFrontRightTyre->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.frontRightTyreDamagePercent)));

    ui->lblRearLeftBrakeDamagePercent->setText(formatPercentage(damage.rearLeftBrakeDamagePercent));
    ui->wgtRearLeftBrake->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.rearLeftBrakeDamagePercent)));
    ui->lblRearRightBrakeDamagePercent->setText(formatPercentage(damage.rearRightBrakeDamagePercent));
    ui->wgtRearRightBrake->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.rearRightBrakeDamagePercent)));
    ui->lblFrontLeftBrakeDamagePercent->setText(formatPercentage(damage.frontLeftBrakeDamagePercent));
    ui->wgtFrontLeftBrake->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.frontLeftBrakeDamagePercent)));
    ui->lblFrontRightBrakeDamagePercent->setText(formatPercentage(damage.frontRightBrakeDamagePercent));
    ui->wgtFrontRightBrake->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.frontRightBrakeDamagePercent)));

    ui->lblFrontLeftWingDamagePercent->setText(formatPercentage(damage.frontLeftWingDamagePercent));
    ui->wgtFrontLeftWing->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.frontLeftWingDamagePercent)));
    ui->lblFrontRightWingDamagePercent->setText(formatPercentage(damage.frontRightWingDamagePercent));
    ui->wgtFrontRightWing->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.frontRightWingDamagePercent)));

    ui->lblRearWingDamagePercent->setText(formatPercentage(damage.rearWingDamagePercent));
    ui->wgtRearWing->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.rearWingDamagePercent)));

    ui->lblFloorDamagePercent->setText(formatPercentage(damage.floorDamagePercent));
    ui->wgtFloor->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.floorDamagePercent)));
    ui->lblSidepodDamagePercent->setText(formatPercentage(damage.sidepodDamagePercent));
    ui->wgtSidepod->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.sidepodDamagePercent)));
    ui->lblDiffuserDamagePercent->setText(formatPercentage(damage.diffuserDamagePercent));
    ui->wgtDiffuser->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.diffuserDamagePercent)));

    ui->lblDRSFault->setText(QString::fromStdString("DRS: " + damage.drsFault));
    ui->wgtDRS->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.drsFault == "OK" ? 0 : 100)));
    ui->lblERSFault->setText(QString::fromStdString("ERS: " + damage.ersFault));
    ui->wgtERS->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.ersFault == "OK" ? 0 : 100)));

    ui->lblGearboxDamagePercent->setText("Gearbox: " + formatPercentage(damage.gearboxDamagePercent));
    ui->wgtGearbox->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.gearboxDamagePercent)));
    ui->lblEngineDamagePercent->setText("Engine: " + formatPercentage(damage.engineDamagePercent));
    ui->wgtEngine->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.engineDamagePercent)));

    ui->lblICEWearPercent->setText("ICE: " + formatPercentage(damage.iceWearPercent));
    ui->wgtICE->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.iceWearPercent)));
    ui->lblCEWearPercent->setText("CE: " + formatPercentage(damage.ceWearPercent));
    ui->wgtCE->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.ceWearPercent)));
    ui->lblESWearPercent->setText("ES: " + formatPercentage(damage.esWearPercent));
    ui->wgtES->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.esWearPercent)));
    ui->lblTCWearPercent->setText("TC: " + formatPercentage(damage.tcWearPercent));
    ui->wgtTC->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.tcWearPercent)));
    ui->lblMGUHWearPercent->setText("MGU-H: " + formatPercentage(damage.mguhWearPercent));
    ui->wgtMGUH->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.mguhWearPercent)));
    ui->lblMGUKWearPercent->setText("MGU-K: " + formatPercentage(damage.mgukWearPercent));
    ui->wgtMGUK->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.mgukWearPercent)));

    ui->lblEngineBlownFault->setText(QString::fromStdString("Blown: " + damage.engineBlownFault));
    ui->wgtEngineBlown->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.engineBlownFault == "OK" ? 0 : 100)));
    ui->lblEngineSeizedFault->setText(QString::fromStdString("Seized: " + damage.engineSeizedFault));
    ui->wgtEngineSeized->setStyleSheet(QString::fromStdString("background-color:" + damageColour(damage.engineSeizedFault == "OK" ? 0 : 100)));
}

std::string temperatureColour(double temperature, double minTemp, double optimalTemp, double maxTemp) {
    // Interpolate the RGB values based on the temperature percentage
    Colour colour(0, 0, 0);
    if (temperature < optimalTemp) {
        // Interpolate between blue and green
        double greenPercentage = (temperature - minTemp) / (optimalTemp - minTemp);
        colour.r = COLD_BLUE.r + std::round(greenPercentage * (HEALTHY_GREEN.r - COLD_BLUE.r));
        colour.g = COLD_BLUE.g + std::round(greenPercentage * (HEALTHY_GREEN.g - COLD_BLUE.g));
        colour.b = COLD_BLUE.b + std::round(greenPercentage * (HEALTHY_GREEN.b - COLD_BLUE.b));
    } else {
        // Interpolate between green and red
        double redPercentage = (temperature - optimalTemp) / (maxTemp - optimalTemp);
        colour.r = HEALTHY_GREEN.r + std::round(redPercentage * (BROKEN_RED.r - HEALTHY_GREEN.r));
        colour.g = HEALTHY_GREEN.g + std::round(redPercentage * (BROKEN_RED.g - HEALTHY_GREEN.g));
        colour.b = HEALTHY_GREEN.b + std::round(redPercentage * (BROKEN_RED.b - HEALTHY_GREEN.b));
    }

    return colour.getHexCode();
}

std::string pressureColour(float pressure, float optimalPressure) {
    // Interpolate the RGB values based on the pressure percentage
    float minPressure = optimalPressure - PRESSURE_THRESHOLD;
    float maxPressure = optimalPressure + PRESSURE_THRESHOLD;
    Colour colour(0, 0, 0);
    if (pressure < optimalPressure) {
        // Interpolate between blue and green
        double greenPercentage = (pressure - minPressure) / (optimalPressure - minPressure);
        colour.r = BROKEN_RED.r + std::round(greenPercentage * (HEALTHY_GREEN.r - BROKEN_RED.r));
        colour.g = BROKEN_RED.g + std::round(greenPercentage * (HEALTHY_GREEN.g - BROKEN_RED.g));
        colour.b = BROKEN_RED.b + std::round(greenPercentage * (HEALTHY_GREEN.b - BROKEN_RED.b));
    } else {
        // Interpolate between green and red
        double redPercentage = (pressure - optimalPressure) / (maxPressure - optimalPressure);
        colour.r = HEALTHY_GREEN.r + std::round(redPercentage * (BROKEN_RED.r - HEALTHY_GREEN.r));
        colour.g = HEALTHY_GREEN.g + std::round(redPercentage * (BROKEN_RED.g - HEALTHY_GREEN.g));
        colour.b = HEALTHY_GREEN.b + std::round(redPercentage * (BROKEN_RED.b - HEALTHY_GREEN.b));
    }

    return colour.getHexCode();
}

void MainWindow::onTemperaturePressureUpdate(TemperaturePressureData tempsPressure) {
    ui->lblRearLeftSurfaceTemperature->setText(QString::fromStdString(formatTemperature(tempsPressure.rearLeftSurfaceTemperature)));
    ui->wgtRearLeftSurfaceTemperature->setStyleSheet(QString::fromStdString("background-color:" + temperatureColour(tempsPressure.rearLeftSurfaceTemperature, TYRE_MIN_TEMP, TYRE_OPT_TEMP, TYRE_MAX_TEMP)));
    ui->lblRearRightSurfaceTemperature->setText(QString::fromStdString(formatTemperature(tempsPressure.rearRightSurfaceTemperature)));
    ui->wgtRearRightSurfaceTemperature->setStyleSheet(QString::fromStdString("background-color:" + temperatureColour(tempsPressure.rearRightSurfaceTemperature, TYRE_MIN_TEMP, TYRE_OPT_TEMP, TYRE_MAX_TEMP)));
    ui->lblFrontLeftSurfaceTemperature->setText(QString::fromStdString(formatTemperature(tempsPressure.frontLeftSurfaceTemperature)));
    ui->wgtFrontLeftSurfaceTemperature->setStyleSheet(QString::fromStdString("background-color:" + temperatureColour(tempsPressure.frontLeftSurfaceTemperature, TYRE_MIN_TEMP, TYRE_OPT_TEMP, TYRE_MAX_TEMP)));
    ui->lblFrontRightSurfaceTemperature->setText(QString::fromStdString(formatTemperature(tempsPressure.frontRightSurfaceTemperature)));
    ui->wgtFrontRightSurfaceTemperature->setStyleSheet(QString::fromStdString("background-color:" + temperatureColour(tempsPressure.frontRightSurfaceTemperature, TYRE_MIN_TEMP, TYRE_OPT_TEMP, TYRE_MAX_TEMP)));

    ui->lblRearLeftInnerTemperature->setText(QString::fromStdString(formatTemperature(tempsPressure.rearLeftInnerTemperature)));
    ui->wgtRearLeftInnerTemperature->setStyleSheet(QString::fromStdString("background-color:" + temperatureColour(tempsPressure.rearLeftInnerTemperature, TYRE_MIN_TEMP, TYRE_OPT_TEMP, TYRE_MAX_TEMP)));
    ui->lblRearRightInnerTemperature->setText(QString::fromStdString(formatTemperature(tempsPressure.rearRightInnerTemperature)));
    ui->wgtRearRightInnerTemperature->setStyleSheet(QString::fromStdString("background-color:" + temperatureColour(tempsPressure.rearRightInnerTemperature, TYRE_MIN_TEMP, TYRE_OPT_TEMP, TYRE_MAX_TEMP)));
    ui->lblFrontLeftInnerTemperature->setText(QString::fromStdString(formatTemperature(tempsPressure.frontLeftInnerTemperature)));
    ui->wgtFrontLeftInnerTemperature->setStyleSheet(QString::fromStdString("background-color:" + temperatureColour(tempsPressure.frontLeftInnerTemperature, TYRE_MIN_TEMP, TYRE_OPT_TEMP, TYRE_MAX_TEMP)));
    ui->lblFrontRightInnerTemperature->setText(QString::fromStdString(formatTemperature(tempsPressure.frontRightInnerTemperature)));
    ui->wgtFrontRightInnerTemperature->setStyleSheet(QString::fromStdString("background-color:" + temperatureColour(tempsPressure.frontRightInnerTemperature, TYRE_MIN_TEMP, TYRE_OPT_TEMP, TYRE_MAX_TEMP)));

    ui->lblRearLeftBrakeTemperature->setText(QString::fromStdString(formatTemperature(tempsPressure.rearLeftBrakeTemperature)));
    ui->wgtRearLeftBrakeTemperature->setStyleSheet(QString::fromStdString("background-color:" + temperatureColour(tempsPressure.rearLeftBrakeTemperature, BRAKE_MIN_TEMP, BRAKE_OPT_TEMP, BRAKE_MAX_TEMP)));
    ui->lblRearRightBrakeTemperature->setText(QString::fromStdString(formatTemperature(tempsPressure.rearRightBrakeTemperature)));
    ui->wgtRearRightBrakeTemperature->setStyleSheet(QString::fromStdString("background-color:" + temperatureColour(tempsPressure.rearRightBrakeTemperature, BRAKE_MIN_TEMP, BRAKE_OPT_TEMP, BRAKE_MAX_TEMP)));
    ui->lblFrontLeftBrakeTemperature->setText(QString::fromStdString(formatTemperature(tempsPressure.frontLeftBrakeTemperature)));
    ui->wgtFrontLeftBrakeTemperature->setStyleSheet(QString::fromStdString("background-color:" + temperatureColour(tempsPressure.frontLeftBrakeTemperature, BRAKE_MIN_TEMP, BRAKE_OPT_TEMP, BRAKE_MAX_TEMP)));
    ui->lblFrontRightBrakeTemperature->setText(QString::fromStdString(formatTemperature(tempsPressure.frontRightBrakeTemperature)));
    ui->wgtFrontRightBrakeTemperature->setStyleSheet(QString::fromStdString("background-color:" + temperatureColour(tempsPressure.frontRightBrakeTemperature, BRAKE_MIN_TEMP, BRAKE_OPT_TEMP, BRAKE_MAX_TEMP)));

    ui->lblEngineTemperature->setText(QString::fromStdString(formatTemperature(tempsPressure.engineTemperature)));
    ui->wgtEngineTemperature->setStyleSheet(QString::fromStdString("background-color:" + temperatureColour(tempsPressure.engineTemperature, ENGINE_MIN_TEMP, ENGINE_OPT_TEMP, ENGINE_MAX_TEMP)));

    ui->lblRearLeftPressure->setText(QString::fromStdString(formatPressure(tempsPressure.rearLeftPressure)));
    ui->wgtRearLeftPressure->setStyleSheet(QString::fromStdString("background-color:" + pressureColour(tempsPressure.rearLeftPressure, tempsPressure.setupRearLeftPressure)));
    ui->lblRearRightPressure->setText(QString::fromStdString(formatPressure(tempsPressure.rearRightPressure)));
    ui->wgtRearRightPressure->setStyleSheet(QString::fromStdString("background-color:" + pressureColour(tempsPressure.rearRightPressure, tempsPressure.setupRearRightPressure)));
    ui->lblFrontLeftPressure->setText(QString::fromStdString(formatPressure(tempsPressure.frontLeftPressure)));
    ui->wgtFrontLeftPressure->setStyleSheet(QString::fromStdString("background-color:" + pressureColour(tempsPressure.frontLeftPressure, tempsPressure.setupFrontLeftPressure)));
    ui->lblFrontRightPressure->setText(QString::fromStdString(formatPressure(tempsPressure.frontRightPressure)));
    ui->wgtFrontRightPressure->setStyleSheet(QString::fromStdString("background-color:" + pressureColour(tempsPressure.frontRightPressure, tempsPressure.setupFrontRightPressure)));

}

void MainWindow::onWheelTelemetryUpdate(WheelTelemetryData wheelTelemetry) {
    ui->lcdThrottle->display(wheelTelemetry.throttle);
    ui->pbThrottle->setValue(wheelTelemetry.throttle);

    ui->lcdBrake->display(wheelTelemetry.brake);
    ui->pbBrake->setValue(wheelTelemetry.brake);

    ui->lcdClutch->display(wheelTelemetry.clutch);
    ui->pbClutch->setValue(wheelTelemetry.clutch);

    ui->lcdSpeed->display(wheelTelemetry.speed);
    ui->lcdRPM->display(wheelTelemetry.rpm);

    switch (wheelTelemetry.gear) {
    case -1:
        ui->lblGear->setText("R");
        break;
    case 0:
        ui->lblGear->setText("N");
        break;
    default:
        ui->lblGear->setText(QString::number(wheelTelemetry.gear));
        break;
    }

    ui->lblRevLights->setText(QString::fromStdString(wheelTelemetry.revLights));

    if (wheelTelemetry.steering < 0) {
        ui->pbRightSteering->setValue(0);
        ui->pbLeftSteering->setValue(abs(wheelTelemetry.steering));
    } else {
        ui->pbRightSteering->setValue(wheelTelemetry.steering);
        ui->pbLeftSteering->setValue(0);
    }

    if (wheelTelemetry.drsActivated) {
        ui->lblDRSActivated->setText("🔵");
    } else {
        ui->lblDRSActivated->setText("");
    }
}

void MainWindow::onTotalLapsUpdate(uint8_t totalLaps) {
    ui->lblLapTotal->setText("/" + QString::number(totalLaps));
}

void MainWindow::onWheelLapUpdate(WheelLapData wheelLap) {
    ui->lblCurrentPosition->setText(QString::fromStdString(wheelLap.currentPosition));
    ui->lblCurrentLapTime->setText(QString::fromStdString(wheelLap.currentLapTime));
    ui->lblCurrentLap->setText(QString::fromStdString(wheelLap.currentLapNumber));
}

void MainWindow::onWheelStatusUpdate(WheelStatusData wheelStatus) {
    ui->lcdERSPercent->display(wheelStatus.ersPercent);
    ui->pbERSPercent->setValue(wheelStatus.ersPercent);
    ui->lcdERSDeployedThisLap->display(wheelStatus.ersDeployedThisLap);
    ui->pbERSDeployedThisLap->setValue(wheelStatus.ersDeployedThisLap);
    ui->lblBrakeBalance->setText("BB " + QString::fromStdString(wheelStatus.frontBrakeBias));

    if (wheelStatus.fuelRemainingLaps > 0) {
        ui->lblFuelRemainingLaps->setStyleSheet("color: #00C717"); // GREEN > 0
    } else {
        ui->lblFuelRemainingLaps->setStyleSheet("color: #CF0808"); // RED < 0

    }
    ui->lblFuelRemainingLaps->setText("+" + QString::number(wheelStatus.fuelRemainingLaps, 'g', 3));

    std::string ersDeployColour;
    switch (wheelStatus.ersDeployMode) {
    case NO_ERS:
        ersDeployColour = "#FFFFFF"; // WHITE
        break;
    case MEDIUM_ERS:
        ersDeployColour = "#FC8200"; // ORANGE
        break;
    case HOTLAP:
        ersDeployColour = "#CF0808"; // RED
        break;
    case OVERTAKE:
        ersDeployColour = "#00C717"; // GREEN
        break;
    default:
        break;
    }
    ui->wgtERSBattery->setStyleSheet(QString::fromStdString("background-color:" + ersDeployColour));

    if (wheelStatus.drsAllowed) {
        ui->lblDRSAllowed->setText("🔵");
    } else {
        ui->lblDRSAllowed->setText("");
    }

}

void MainWindow::onLapHistoryTableUpdate(LapHistoryTable lapHistoryTable) {
    QFont font = QFont();
    font.setPointSize(18);

    QBrush invalid("#ff5e5e");
    QBrush fastest("#6000c7");

    while (ui->tblLapHistory->rowCount() < lapHistoryTable.table.size()) {
        ui->tblLapHistory->insertRow(0);
    }

    // Plot backwards (Lap 1 at the bottom, most recent at top)
    for (size_t r = 0; r < lapHistoryTable.table.size(); r++) {
        LapHistoryRow row = lapHistoryTable.table[r];

        QTableWidgetItem *lap = new QTableWidgetItem(QString::number(row.lap));
        lap->setFlags(lap->flags() &  ~Qt::ItemIsEditable);
        lap->setTextAlignment(Qt::AlignCenter);
        lap->setFont(font);
        if (!row.lapValid) lap->setBackground(invalid);
        if (lapHistoryTable.bestLapTimeLap == row.lap) lap->setForeground(fastest);
        ui->tblLapHistory->setItem(r, 0, lap);

        QTableWidgetItem *sector1 = new QTableWidgetItem(QString::fromStdString(row.sector1));
        sector1->setFlags(sector1->flags() &  ~Qt::ItemIsEditable);
        sector1->setFont(font);
        if (!row.sector1Valid) sector1->setBackground(invalid);
        if (lapHistoryTable.bestSector1Lap == row.lap) sector1->setForeground(fastest);
        ui->tblLapHistory->setItem(r, 1, sector1);

        QTableWidgetItem *sector2 = new QTableWidgetItem(QString::fromStdString(row.sector2));
        sector2->setFlags(sector2->flags() &  ~Qt::ItemIsEditable);
        sector2->setFont(font);
        if (!row.sector2Valid) sector2->setBackground(invalid);
        if (lapHistoryTable.bestSector2Lap == row.lap) sector2->setForeground(fastest);
        ui->tblLapHistory->setItem(r, 2, sector2);

        QTableWidgetItem *sector3 = new QTableWidgetItem(QString::fromStdString(row.sector3));
        sector3->setFlags(sector3->flags() &  ~Qt::ItemIsEditable);
        sector3->setFont(font);
        if (!row.sector3Valid) sector3->setBackground(invalid);
        if (lapHistoryTable.bestSector3Lap == row.lap) sector3->setForeground(fastest);
        ui->tblLapHistory->setItem(r, 3, sector3);

        QTableWidgetItem *lapTime = new QTableWidgetItem(QString::fromStdString(row.lapTime));
        lapTime->setFlags(lapTime->flags() &  ~Qt::ItemIsEditable);
        lapTime->setFont(font);
        if (!row.lapValid) lapTime->setBackground(invalid);
        if (lapHistoryTable.bestLapTimeLap == row.lap) lapTime->setForeground(fastest);
        ui->tblLapHistory->setItem(r, 4, lapTime);

        QTableWidgetItem *tyre = new QTableWidgetItem(QString::fromStdString(row.tyre));
        tyre->setFlags(tyre->flags() &  ~Qt::ItemIsEditable);
        tyre->setTextAlignment(Qt::AlignCenter);
        tyre->setFont(font);
        tyre->setForeground(QBrush(QColor(QString::fromStdString(row.tyreColour.getHexCode()))));
        ui->tblLapHistory->setItem(r, 5, tyre);


        QTableWidgetItem *targetDelta = new QTableWidgetItem(QString::fromStdString(formatDelta(targetLapTimeMS, row._lapTimeMS)));
        targetDelta->setFlags(targetDelta->flags() &  ~Qt::ItemIsEditable);
        targetDelta->setFont(font);
        if (row._lapTimeMS < targetLapTimeMS) targetDelta->setForeground(QBrush(QColor("green")));
        if (row._lapTimeMS > targetLapTimeMS) targetDelta->setForeground(QBrush(QColor("red")));
        ui->tblLapHistory->setItem(r, 6, targetDelta);
    }
}

void MainWindow::onSessionTypeUpdate(SessionType sessionType) {
    ui->lblSession->setText(QString::fromStdString(getSessionString(sessionType)));
}

void MainWindow::onStintStarted(StintType stintType) {
    ui->lblStintStatus->setText(QString::fromStdString("🟢 " + getStintTypeString(stintType)));
}

void MainWindow::onStintEnded(StintType stintType) {
    ui->lblStintStatus->setText(QString::fromStdString("🔴 " + getStintTypeString(stintType)));
}

void MainWindow::onSafetyCarStatusUpdate(SafetyCarStatus safetyCarStatus) {
    switch (safetyCarStatus) {
    case SafetyCarStatus::NO_SAFETY_CAR:
        ui->lblSafetyCarStatus->setText("");
        ui->lblSafetyCarStatus->setStyleSheet(QString::fromStdString("background-color: " + GREEN_FLAG.getHexCode()));
        break;
    case SafetyCarStatus::FORMATION_LAP:
        ui->lblSafetyCarStatus->setText("FORMATION LAP");
        ui->lblSafetyCarStatus->setStyleSheet(QString::fromStdString("background-color: " + BLUE_FLAG.getHexCode()));
        break;
    case SafetyCarStatus::VIRTUAL_SAFETY_CAR:
        ui->lblSafetyCarStatus->setText("VIRTUAL SAFETY CAR");
        ui->lblSafetyCarStatus->setStyleSheet(QString::fromStdString("background-color: " + YELLOW_FLAG.getHexCode()));
        break;
    case SafetyCarStatus::FULL_SAFETY_CAR:
        ui->lblSafetyCarStatus->setText("SAFETY CAR");
        ui->lblSafetyCarStatus->setStyleSheet(QString::fromStdString("background-color: " + YELLOW_FLAG.getHexCode()));
        break;
    }
}

void MainWindow::onCurrentSetupUpdate(CurrentCarSetup currentCarSetup) {
    ui->lblCurrentFrontWing->setText(QString::number(currentCarSetup.frontWing));
    ui->lblCurrentBrakeBias->setText(QString::number(currentCarSetup.brakeBias) + "%");
    ui->lblCurrentDifferential->setText(QString::number(currentCarSetup.differentialOnThrottle) + "%");
}

void MainWindow::onDriverAheadAndBehindUpdate(LiveStrategyData liveStrategyData) {
    ui->lblDriverAhead->setText(QString::fromStdString(liveStrategyData.driverAhead));
    ui->lblDriverBehind->setText(QString::fromStdString(liveStrategyData.driverBehind));
    ui->lblDriverAheadDelta->setText(QString::fromStdString(liveStrategyData.driverAheadDelta));
    ui->lblDriverBehindDelta->setText(QString::fromStdString(liveStrategyData.driverBehindDelta));
    ui->lblDriverAheadTyreAge->setText(QString::number(liveStrategyData.driverAheadTyreData.tyreAge));
    ui->lblDriverAheadTyreAge->setStyleSheet(QString::fromStdString("color : " + getVisualTyreColour(liveStrategyData.driverAheadTyreData.visualTyreCompound).getHexCode()));
    ui->lblDriverBehindTyreAge->setText(QString::number(liveStrategyData.driverBehindTyreData.tyreAge));
    ui->lblDriverBehindTyreAge->setStyleSheet(QString::fromStdString("color : " + getVisualTyreColour(liveStrategyData.driverBehindTyreData.visualTyreCompound).getHexCode()));
    ui->lblDriverAheadPosition->setText(QString::fromStdString(liveStrategyData.driverAheadPosition));
    ui->lblDriverBehindPosition->setText(QString::fromStdString(liveStrategyData.driverBehindPosition));
    ui->lblLastLapTimeStrategy->setText(QString::fromStdString(liveStrategyData.lastLap));
    ui->lblCurrentPositionStrategy->setText(QString::fromStdString(liveStrategyData.currentPosition));
}



void MainWindow::on_ddSelectDriver_currentIndexChanged(int index) {
    if (index >= 0) updater->driverSelected = index;
}

void MainWindow::on_btnStartStopUDP_clicked()
{
    if (updater->enable_listening) {
        updater->enable_listening = false;
        ui->lblListeningStatus->setText("🔴 Stopped Listening");
        ui->btnStartStopUDP->setText("Start Listening");
    } else {
        updater->enable_listening = true;
        ui->lblListeningStatus->setText("🟢 Currently Listening");
        ui->btnStartStopUDP->setText("Stop Listening");

        updater->start();
    }
}

void MainWindow::on_btnPlus10Seconds_clicked()
{
    targetLapTimeMS += (10 * 1000);
    ui->lblTargetLapTime->setText(QString::fromStdString(formatLapTimeMS(targetLapTimeMS)));
}


void MainWindow::on_btnMinus10Seconds_clicked()
{
    // Only minus if result is > 0;
    if (targetLapTimeMS > (10 * 1000)) targetLapTimeMS -= (10 * 1000);
    ui->lblTargetLapTime->setText(QString::fromStdString(formatLapTimeMS(targetLapTimeMS)));
}


void MainWindow::on_btnPlus1Second_clicked()
{
    targetLapTimeMS += 1000;
    ui->lblTargetLapTime->setText(QString::fromStdString(formatLapTimeMS(targetLapTimeMS)));
}


void MainWindow::on_btnMinus1Second_clicked()
{
    // Only minus if result is > 0;
    if (targetLapTimeMS > 1000) targetLapTimeMS -= 1000;
    ui->lblTargetLapTime->setText(QString::fromStdString(formatLapTimeMS(targetLapTimeMS)));
}


void MainWindow::on_btnPlus100MS_clicked()
{
    targetLapTimeMS += 100;
    ui->lblTargetLapTime->setText(QString::fromStdString(formatLapTimeMS(targetLapTimeMS)));
}


void MainWindow::on_btnMinus100MS_clicked()
{
    // Only minus if result is > 0;
    if (targetLapTimeMS > 100) targetLapTimeMS -= 100;
    ui->lblTargetLapTime->setText(QString::fromStdString(formatLapTimeMS(targetLapTimeMS)));
}


void MainWindow::on_btnSaveRecording_clicked()
{
    updater->raceRecorder.writeRaceToJSON();
    updater->raceRecorder.writeRaceToPB();
}

RaceWeekend loadRaceFromFile(const QString& filePath) {
    // Convert QString file path to std::string
    std::string filePathStr = filePath.toStdString();

    // Open the Protobuf file
    std::ifstream inputFile(filePathStr, std::ios::binary);
    if (!inputFile) {
        // Handle file opening error
        throw std::runtime_error("Failed to open Protobuf file: " + filePathStr);
    }

    // Create an instance of the Protobuf message
    RaceWeekend message;

    // Read and parse the Protobuf data
    if (!message.ParseFromIstream(&inputFile)) {
        // Handle parsing error
        throw std::runtime_error("Failed to parse Protobuf file: " + filePathStr);
    }

    // Close the input file stream
    inputFile.close();

    // Return the loaded Protobuf message
    return message;
}

void plotRegressionLine(QCustomPlot* customPlot, const LinearRegressionResult& result) {
    customPlot->graph(0)->data()->clear(); // Remove positions

    // Create a QVector for x values
    QVector<double> xValues;
    xValues << customPlot->xAxis->range().lower << customPlot->xAxis->range().upper;

    // Calculate the corresponding y values using the regression line equation: y = mx + b
    QVector<double> yValues;
    for (const double& x : xValues) {
        double y = result.gradient * x + result.y_intercept;
        yValues << y;
    }

    // Create and configure the graph
    customPlot->addGraph();
    customPlot->graph()->setData(xValues, yValues);
    customPlot->graph()->setPen(QPen(Qt::red)); // Set the line color and style

    // Rescale the axes to fit the new graph
    customPlot->rescaleAxes();
    customPlot->replot();
}

void MainWindow::updateLoadedRaceWeekendData() {
    ui->pltFuelUsage->graph(0)->data()->clear();
    ui->pltTyreDegradation->graph(0)->data()->clear();
    ui->tblRecordedLaps->clearContents();

    // Add lap data to table
    QFont font = QFont();
    font.setPointSize(18);

    while (ui->tblRecordedLaps->rowCount() < selectedLoadedStint.lap_size()) {
        ui->tblRecordedLaps->insertRow(0);
    }

    for (size_t i = 0; i < selectedLoadedStint.lap_size(); i++) {
        Lap lap = selectedLoadedStint.lap()[i];

        // If there is no laptime recorded, do not make a row for this data
        if (lap.lap_time() == 0) continue;

        QTableWidgetItem *lapNumber = new QTableWidgetItem(QString::number(i+1));
        lapNumber->setFlags(lapNumber->flags() &  ~Qt::ItemIsEditable);
        lapNumber->setTextAlignment(Qt::AlignCenter);
        lapNumber->setFont(font);
        ui->tblRecordedLaps->setItem(i, 0, lapNumber);

        QTableWidgetItem *sector1 = new QTableWidgetItem(QString::fromStdString(formatSectorMS(lap.sector_1())));
        sector1->setFlags(sector1->flags() &  ~Qt::ItemIsEditable);
        sector1->setTextAlignment(Qt::AlignCenter);
        sector1->setFont(font);
        ui->tblRecordedLaps->setItem(i, 1, sector1);

        QTableWidgetItem *sector2 = new QTableWidgetItem(QString::fromStdString(formatSectorMS(lap.sector_2())));
        sector2->setFlags(sector2->flags() &  ~Qt::ItemIsEditable);
        sector2->setTextAlignment(Qt::AlignCenter);
        sector2->setFont(font);
        ui->tblRecordedLaps->setItem(i, 2, sector2);

        QTableWidgetItem *sector3 = new QTableWidgetItem(QString::fromStdString(formatSectorMS(lap.sector_3())));
        sector3->setFlags(sector3->flags() &  ~Qt::ItemIsEditable);
        sector3->setTextAlignment(Qt::AlignCenter);
        sector3->setFont(font);
        ui->tblRecordedLaps->setItem(i, 3, sector3);

        QTableWidgetItem *lapTime = new QTableWidgetItem(QString::fromStdString(formatLapTimeMS(lap.lap_time())));
        lapTime->setFlags(lapTime->flags() &  ~Qt::ItemIsEditable);
        lapTime->setTextAlignment(Qt::AlignCenter);
        lapTime->setFont(font);
        ui->tblRecordedLaps->setItem(i, 4, lapTime);
    }

    // Fill the setup components
    Setup s = selectedLoadedStint.setup();
    ui->lblSetupFrontWing->setText(QString::number(s.front_wing()));
    ui->lblSetupRearWing->setText(QString::number(s.rear_wing()));
    ui->lblSetupDifferentialOnThrottle->setText(QString::number(s.differential_on_throttle()) + "%");
    ui->lblSetupDifferentialOffThrottle->setText(QString::number(s.differential_off_throttle()) + "%");
    ui->lblSetupFrontCamber->setText(QString::number(s.front_camber()) + "°");
    ui->lblSetupRearCamber->setText(QString::number(s.rear_camber()) + "°");
    ui->lblSetupFrontToe->setText(QString::number(s.front_toe()) + "°");
    ui->lblSetupRearToe->setText(QString::number(s.rear_toe()) + "°");
    ui->lblSetupFrontSuspension->setText(QString::number(s.front_suspension()));
    ui->lblSetupRearSuspension->setText(QString::number(s.rear_suspension()));
    ui->lblSetupFrontAntiRollBar->setText(QString::number(s.front_anti_roll_bar()));
    ui->lblSetupRearAntiRollBar->setText(QString::number(s.rear_anti_roll_bar()));
    ui->lblSetupFrontRideHeight->setText(QString::number(s.front_suspension_height()));
    ui->lblSetupRearRideHeight->setText(QString::number(s.rear_suspension_height()));
    ui->lblSetupBrakePressure->setText(QString::number(s.brake_pressure()) + "%");
    ui->lblSetupBrakeBias->setText(QString::number(s.brake_bias()) + "%");
    ui->lblSetupRearLeftTyrePressure->setText(QString::number(s.rear_left_tyre_pressure()) + " psi");
    ui->lblSetupRearRightTyrePressure->setText(QString::number(s.rear_right_tyre_pressure()) + " psi");
    ui->lblSetupFrontLeftTyrePressure->setText(QString::number(s.front_left_tyre_pressure()) + " psi");
    ui->lblSetupFrontRightTyrePressure->setText(QString::number(s.front_right_tyre_pressure()) + " psi");
    ui->lblSetupBallast->setText(QString::number(s.ballast()) + " kg");
    ui->lblSetupFuelLoad->setText(QString::number(s.fuel_load()) + " kg");
    ui->lblSetupTyre->setText(QString::fromStdString(getActualTyreName(getActualTyreCompound(s.actual_tyre_compound()))));
    ui->lblSetupTyre->setStyleSheet(QString::fromStdString("color:" + getVisualTyreColour(getVisualTyreCompound(s.visual_tyre_compound())).getHexCode()));

    QVector<double> fuelUsagePlotValues;
    QVector<double> tyreDegradationPlotValues;
    QVector<double> lapDistancePlotValues;
    float l = 0;

    for (auto lap : selectedLoadedStint.lap()) {
        for (auto t : lap.telemetry()) {
            fuelUsagePlotValues.append(t.fuel_in_tank());
            tyreDegradationPlotValues.append(t.rear_left_tyre_damage());
            lapDistancePlotValues.append(l + t.lap_distance());
        }
        if (lap.telemetry_size() > 0) l = lap.telemetry()[lap.telemetry_size() - 1].lap_distance();
    }

    std::vector<double> fuelValues(fuelUsagePlotValues.begin(), fuelUsagePlotValues.end());
    std::vector<double> tyreValues(tyreDegradationPlotValues.begin(), tyreDegradationPlotValues.end());
    std::vector<double> distanceValues(lapDistancePlotValues.begin(), lapDistancePlotValues.end());

    predictedFuelRegression = calculateLinearRegression(distanceValues, fuelValues);
    LinearRegressionResult tyreRegression = calculateLinearRegression(distanceValues, tyreValues);

    ui->pltFuelUsage->graph(0)->setData(lapDistancePlotValues, fuelUsagePlotValues);
    ui->pltFuelUsage->rescaleAxes();
    plotRegressionLine(ui->pltFuelUsage, predictedFuelRegression);

    ui->lblFuelUsagePerLap->setText(QString::number(abs(predictedFuelRegression.gradient) * loadedRaceWeekend.track_length()) + " kg/lap");

    ui->pltTyreDegradation->graph(0)->setData(lapDistancePlotValues, tyreDegradationPlotValues);
    ui->pltTyreDegradation->rescaleAxes();
    plotRegressionLine(ui->pltTyreDegradation, tyreRegression);

    updateFuelPrediction();

    // TODO: previous linear regression needs to be cleared each load
    ui->lblTyreDegradationPerLap->setText(QString::number(abs(tyreRegression.gradient) * loadedRaceWeekend.track_length()) + " %/lap");
}


void MainWindow::on_btnLoadRecording_clicked()
{
    // Open file dialog
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Select Protobuf File", "", "Protobuf Files (*.protobuf *.pb)");
    if (filePath.isEmpty()) {
        qDebug() << "No file selected.";
        return;
    }

    loadedRaceWeekend = loadRaceFromFile(filePath);

    // UI changes
    ui->tblRecordedLaps->clearContents();

    // TODO: Change the drop downs here

    updateLoadedRaceWeekendData();
}

void MainWindow::on_ddSelectStint_currentIndexChanged(int index)
{
    selectedStint = stintTypes[index];
}


void MainWindow::on_btnStartStint_clicked()
{
    updater->raceRecorder.startStint(selectedStint);
}


void MainWindow::on_ddSelectLoadedSession_currentIndexChanged(int index)
{
    // Reset number selection of this stint
    ui->ddSelectLoadedStintNumber->clear();

    // TODO: race_sessions should not be hardcoded
    switch (index) {
    case 0:
        selectedPractice = loadedRaceWeekend.race_sessions().fp1();
        break;
    case 1:
        selectedPractice = loadedRaceWeekend.race_sessions().fp2();
        break;
    case 2:
        selectedPractice = loadedRaceWeekend.race_sessions().fp3();
        break;
    }
}


void MainWindow::on_ddSelectLoadedStintType_currentIndexChanged(int index)
{
    StintType st = stintTypes[index];
    int numberOfStints = 0;

    // Reset number selection of this stint
    ui->ddSelectLoadedStintNumber->clear();

    switch (st) {
    case RACE_SIMULATION:
        selectedLoadedStints = selectedPractice.race_simulation();
        numberOfStints = selectedPractice.race_simulation_size();
        break;
    case QUALIFYING_SIMULATION:
        selectedLoadedStints = selectedPractice.qualifying_simulation();
        numberOfStints = selectedPractice.qualifying_simulation_size();
        break;
    }

    // Add the number of these stints for this session
    for (int i = 1; i <= numberOfStints; i++) {
        ui->ddSelectLoadedStintNumber->addItem(QString::number(i));
    }

    // If there is a stint, update the table, otherwise clear it
    if (numberOfStints > 0) {
        ui->ddSelectLoadedStintNumber->setCurrentIndex(0);
        selectedLoadedStint = selectedLoadedStints[0];
        updateLoadedRaceWeekendData();
    }
    else {
        ui->tblRecordedLaps->clearContents();
    }
}


void MainWindow::on_ddSelectLoadedStintNumber_currentIndexChanged(int index)
{
    // index = -1 when clearing the combobox of the stint numbers
    if (index < 0) {
        ui->tblRecordedLaps->clearContents();
        return;
    }
    selectedLoadedStint = selectedLoadedStints[index];

    // Set the number of laps for the telemetry tab
    ui->ddSelectLoadedLapNumberTelemetryLap1->clear();
    ui->ddSelectLoadedLapNumberTelemetryLap2->clear();
    for (int i = 1; i <= selectedLoadedStint.lap_size(); i++) {
        ui->ddSelectLoadedLapNumberTelemetryLap1->addItem(QString::number(i));
        ui->ddSelectLoadedLapNumberTelemetryLap2->addItem(QString::number(i));
    }

    updateLoadedRaceWeekendData();
}

void MainWindow::on_ddSelectLoadedLapNumberTelemetryLap1_currentIndexChanged(int index)
{
    if (index < 0) return; // index = -1 when clearing the combobox of lap numbers
    selectedLoadedLap1 = selectedLoadedStint.lap()[index];
    updateRecordedTelemetryGraphs();
}

void MainWindow::on_ddSelectLoadedLapNumberTelemetryLap2_currentIndexChanged(int index)
{
    if (index < 0) return; // index = -1 when clearing the combobox of lap numbers
    selectedLoadedLap2 = selectedLoadedStint.lap()[index];
    updateRecordedTelemetryGraphs();
}

void MainWindow::updateRecordedTelemetryGraphs() {
    // Clear graphs
    ui->pltRecordedSpeed->graph(0)->data()->clear();
    ui->pltRecordedThrottle->graph(0)->data()->clear();
    ui->pltRecordedBrake->graph(0)->data()->clear();
    ui->pltRecordedRPM->graph(0)->data()->clear();
    ui->pltRecordedGear->graph(0)->data()->clear();
    ui->pltRecordedSteering->graph(0)->data()->clear();

    ui->pltRecordedSpeed->graph(1)->data()->clear();
    ui->pltRecordedThrottle->graph(1)->data()->clear();
    ui->pltRecordedBrake->graph(1)->data()->clear();
    ui->pltRecordedRPM->graph(1)->data()->clear();
    ui->pltRecordedGear->graph(1)->data()->clear();
    ui->pltRecordedSteering->graph(1)->data()->clear();


    QVector<double> speedRecordedValuesLap1;
    QVector<double> throttleRecordedValuesLap1;
    QVector<double> brakeRecordedValuesLap1;
    QVector<double> rpmRecordedValuesLap1;
    QVector<double> gearRecordedValuesLap1;
    QVector<double> steeringRecordedValuesLap1;
    QVector<double> distanceRecordedValuesLap1;

    QVector<double> speedRecordedValuesLap2;
    QVector<double> throttleRecordedValuesLap2;
    QVector<double> brakeRecordedValuesLap2;
    QVector<double> rpmRecordedValuesLap2;
    QVector<double> gearRecordedValuesLap2;
    QVector<double> steeringRecordedValuesLap2;
    QVector<double> distanceRecordedValuesLap2;

    for (auto t : selectedLoadedLap1.telemetry()) {
        speedRecordedValuesLap1.append(convertKPHtoMPH((uint16_t)t.speed()));
        throttleRecordedValuesLap1.append(t.throttle() * 100);
        brakeRecordedValuesLap1.append(t.brake() * 100);
        rpmRecordedValuesLap1.append(t.engine_rpm());
        gearRecordedValuesLap1.append(t.gear());
        steeringRecordedValuesLap1.append(t.steer() * 100);
        distanceRecordedValuesLap1.append(t.lap_distance());
    }

    for (auto t : selectedLoadedLap2.telemetry()) {
        speedRecordedValuesLap2.append(convertKPHtoMPH((uint16_t)t.speed()));
        throttleRecordedValuesLap2.append(t.throttle() * 100);
        brakeRecordedValuesLap2.append(t.brake() * 100);
        rpmRecordedValuesLap2.append(t.engine_rpm());
        gearRecordedValuesLap2.append(t.gear());
        steeringRecordedValuesLap2.append(t.steer() * 100);
        distanceRecordedValuesLap2.append(t.lap_distance());
    }

    ui->pltRecordedSpeed->graph(0)->setData(distanceRecordedValuesLap1, speedRecordedValuesLap1);
    ui->pltRecordedSpeed->graph(1)->setData(distanceRecordedValuesLap2, speedRecordedValuesLap2);
    ui->pltRecordedSpeed->xAxis->setRange(0, loadedRaceWeekend.track_length());
    ui->pltRecordedSpeed->replot();

    ui->pltRecordedThrottle->graph(0)->setData(distanceRecordedValuesLap1, throttleRecordedValuesLap1);
    ui->pltRecordedThrottle->graph(1)->setData(distanceRecordedValuesLap2, throttleRecordedValuesLap2);
    ui->pltRecordedThrottle->xAxis->setRange(0, loadedRaceWeekend.track_length());
    ui->pltRecordedThrottle->replot();

    ui->pltRecordedBrake->graph(0)->setData(distanceRecordedValuesLap1, brakeRecordedValuesLap1);
    ui->pltRecordedBrake->graph(1)->setData(distanceRecordedValuesLap2, brakeRecordedValuesLap2);
    ui->pltRecordedBrake->xAxis->setRange(0, loadedRaceWeekend.track_length());
    ui->pltRecordedBrake->replot();

    ui->pltRecordedRPM->graph(0)->setData(distanceRecordedValuesLap1, rpmRecordedValuesLap1);
    ui->pltRecordedRPM->graph(1)->setData(distanceRecordedValuesLap2, rpmRecordedValuesLap2);
    ui->pltRecordedRPM->xAxis->setRange(0, loadedRaceWeekend.track_length());
    ui->pltRecordedRPM->replot();

    ui->pltRecordedGear->graph(0)->setData(distanceRecordedValuesLap1, gearRecordedValuesLap1);
    ui->pltRecordedGear->graph(1)->setData(distanceRecordedValuesLap2, gearRecordedValuesLap2);
    ui->pltRecordedGear->xAxis->setRange(0, loadedRaceWeekend.track_length());
    ui->pltRecordedGear->replot();

    ui->pltRecordedSteering->graph(0)->setData(distanceRecordedValuesLap1, steeringRecordedValuesLap1);
    ui->pltRecordedSteering->graph(1)->setData(distanceRecordedValuesLap2, steeringRecordedValuesLap2);
    ui->pltRecordedSteering->xAxis->setRange(0, loadedRaceWeekend.track_length());
    ui->pltRecordedSteering->replot();
}


void MainWindow::on_btnPredictedLapsPlus1_clicked()
{
    predictedLaps += 1;
    ui->lblPredictedTotalLaps->setText(QString::number(predictedLaps) + " Laps");
    updateFuelPrediction();
}


void MainWindow::on_btnPredictedLapsMinus1_clicked()
{
    // Only minus if result is > 0;
    if (predictedLaps > 1) predictedLaps -= 1;
    ui->lblPredictedTotalLaps->setText(QString::number(predictedLaps) + " Laps");
    updateFuelPrediction();
}


void MainWindow::on_btnPredictedLapsPlus10_clicked()
{
    predictedLaps += 10;
    ui->lblPredictedTotalLaps->setText(QString::number(predictedLaps) + " Laps");
    updateFuelPrediction();
}


void MainWindow::on_btnPredictedLapsMinus10_clicked()
{
    // Only minus if result is > 0;
    if (predictedLaps > 10) predictedLaps -= 10;
    ui->lblPredictedTotalLaps->setText(QString::number(predictedLaps) + " Laps");
    updateFuelPrediction();
}

void MainWindow::updateFuelPrediction() {
    ui->lblPredictedFuel->setText(QString::number(predictedLaps * loadedRaceWeekend.track_length() * abs(predictedFuelRegression.gradient)) + " kg");
}

void MainWindow::on_actionUDP_Settings_triggered()
{
    udpSettings.show();
}


QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++20


# Disable the unused parameter warning
QMAKE_CXXFLAGS_WARN_OFF -= -Wunused-parameter

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    analysis.cpp \
    compiled_protos/Lap.pb.cc \
    compiled_protos/Practice.pb.cc \
    compiled_protos/Qualifying.pb.cc \
    compiled_protos/QualifyingSession.pb.cc \
    compiled_protos/Race.pb.cc \
    compiled_protos/RaceSessions.pb.cc \
    compiled_protos/RaceWeekend.pb.cc \
    compiled_protos/Setup.pb.cc \
    compiled_protos/SprintRaceSessions.pb.cc \
    compiled_protos/SprintRaceSessions2023.pb.cc \
    compiled_protos/Stint.pb.cc \
    compiled_protos/Telemetry.pb.cc \
    enums.cpp \
    formatting.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    race_recorder.cpp \
    race_strategy_prediction.cpp \
    udp_listener.cpp \
    udp_updater.cpp \
    udpsettings.cpp

HEADERS += \
    analysis.hpp \
    colour.h \
    compiled_protos/Lap.pb.h \
    compiled_protos/Practice.pb.h \
    compiled_protos/Qualifying.pb.h \
    compiled_protos/QualifyingSession.pb.h \
    compiled_protos/Race.pb.h \
    compiled_protos/RaceSessions.pb.h \
    compiled_protos/RaceWeekend.pb.h \
    compiled_protos/Setup.pb.h \
    compiled_protos/SprintRaceSessions.pb.h \
    compiled_protos/SprintRaceSessions2023.pb.h \
    compiled_protos/Stint.pb.h \
    compiled_protos/Telemetry.pb.h \
    enums.hpp \
    formatting.hpp \
    gui_types.hpp \
    mainwindow.h \
    packet_handler.hpp \
    packets.hpp \
    qcustomplot.h \
    race_recorder.hpp \
    race_strategy_prediction.hpp \
    udp_listener.hpp \
    udp_updater.h \
    udpsettings.h

FORMS += \
    mainwindow.ui \
    udpsettings.ui

RESOURCES += \
    images/tracks/sakhir.jpg \
    images/tracks/jeddah.jpg \
    images/tracks/melbourne.jpg

PROTOBUF_PATH = /usr/local/Cellar/protobuf/21.12

INCLUDEPATH += $${PROTOBUF_PATH}/include

LIBS += -L$${PROTOBUF_PATH}/lib -lprotobuf

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    compiled_protos/race.json \
    compiled_protos/race.pb

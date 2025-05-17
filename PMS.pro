QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CarParkingSpace.cpp \
    EVCarParkingSpace.cpp \
    EVMotorcycleParkingSpace.cpp \
    MotorcycleParkingSpace.cpp \
    ParkingLot.cpp \
    ParkingManager.cpp \
    ParkingSpace.cpp \
    TruckParkingSpace.cpp \
    Vehicle.cpp \
    createacc.cpp \
    lcdmanager.cpp \
    logmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    parkingslip.cpp \
    signin.cpp

HEADERS += \
    CarParkingSpace.h \
    EVCarParkingSpace.h \
    EVMotorcycleParkingSpace.h \
    MotorcycleParkingSpace.h \
    ParkingLot.h \
    ParkingManager.h \
    ParkingSpace.h \
    TruckParkingSpace.h \
    Vehicle.h \
    createacc.h \
    lcdmanager.h \
    logmanager.h \
    mainwindow.h \
    parkingslip.h \
    signin.h

FORMS += \
    createacc.ui \
    mainwindow.ui \
    signin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc

DISTFILES += \
    Ahmed/Downloads/createacc.png

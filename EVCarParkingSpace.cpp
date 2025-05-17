#include "EVCarParkingSpace.h"

EVCarParkingSpace::EVCarParkingSpace(int id) : ParkingSpace(id) {}

EVCarParkingSpace::~EVCarParkingSpace() {}

QString EVCarParkingSpace::getVehicleType() const {
    return "EV Car";
}

double EVCarParkingSpace::calculateFee() const {
    if (!occupied) return 0.0;

    double hours = entryTime.secsTo(QDateTime::currentDateTime()) / 3600.0;
    if(hours < 1) return 400;
    return hours * 400;
}

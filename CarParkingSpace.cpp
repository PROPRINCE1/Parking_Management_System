#include "CarParkingSpace.h"

CarParkingSpace::CarParkingSpace(int id) : ParkingSpace(id) {}

CarParkingSpace::~CarParkingSpace() {}

QString CarParkingSpace::getVehicleType() const {
    return "Car";
}

double CarParkingSpace::calculateFee() const {
    if (!occupied) return 0.0;

    double hours = entryTime.secsTo(QDateTime::currentDateTime()) / 3600.0;
    if(hours < 1) return 200;
    return hours * 200;
}

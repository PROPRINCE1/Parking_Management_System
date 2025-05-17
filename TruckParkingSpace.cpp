#include "TruckParkingSpace.h"

TruckParkingSpace::TruckParkingSpace(int id) : ParkingSpace(id) {}

TruckParkingSpace::~TruckParkingSpace() {}

QString TruckParkingSpace::getVehicleType() const {
    return "Truck";
}

double TruckParkingSpace::calculateFee() const {
    if (!occupied) return 0.0;

    double hours = entryTime.secsTo(QDateTime::currentDateTime()) / 3600.0;
    if(hours < 1) return 500;
    return hours * 500;
}

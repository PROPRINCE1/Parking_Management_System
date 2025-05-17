#include "ParkingSpace.h"

ParkingSpace::ParkingSpace(int id)
    : spaceID(id), occupied(false), licensePlate("") {}

ParkingSpace::~ParkingSpace() {}

bool ParkingSpace::isOccupied() const {
    return occupied;
}

int ParkingSpace::getSpaceID() const {
    return spaceID;
}

QString ParkingSpace::getLicensePlate() const {
    return licensePlate;
}

QDateTime ParkingSpace::getEntryTime() const {
    return entryTime;
}

void ParkingSpace::parkVehicle(const QString& plate) {
    occupied = true;
    licensePlate = plate;
    entryTime = QDateTime::currentDateTime();
}

void ParkingSpace::removeVehicle() {
    occupied = false;
    licensePlate = "";
}

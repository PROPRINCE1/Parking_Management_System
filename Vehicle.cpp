#include "Vehicle.h"

Vehicle::Vehicle(const QString& plate, const QString& type)
    : licensePlate(plate), vehicleType(type) {}

Vehicle::~Vehicle() {}

QString Vehicle::getLicensePlate() const {
    return licensePlate;
}

QString Vehicle::getVehicleType() const {
    return vehicleType;
}

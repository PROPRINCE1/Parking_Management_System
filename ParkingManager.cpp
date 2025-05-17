#include "ParkingManager.h"

ParkingManager::ParkingManager() {}

ParkingManager::~ParkingManager() {}

bool ParkingManager::parkVehicle(const QString& vehicleType, const QString& licensePlate) {
    return parkingLot->parkVehicle(vehicleType, licensePlate);
}

double ParkingManager::removeVehicle(const QString& licensePlate) {
    return parkingLot->removeVehicle(licensePlate);
}

void ParkingManager::displayAvailableSpaces() const {
    parkingLot->displayAvailableSpaces();
}

void ParkingManager::resizeParkingLot(int newCar,int newBike,int newTruck, int newEC, int newEB){
    parkingLot->resizeParkingLot(newCar, newBike, newTruck, newEC, newEB);
}

int ParkingManager::getAvailableSpacesCount(const QString& vehicleType) const {
    return parkingLot->getAvailableSpaces(vehicleType);
}

QString ParkingManager::getVehicleTypeForLicensePlate(const QString& licensePlate) const {
    return parkingLot->getVehicleTypeForLicensePlate(licensePlate);
}

int ParkingManager::getSpaceIdForLicensePlate(const QString& licensePlate) const {
    return parkingLot->getSpaceIdForLicensePlate(licensePlate);
}

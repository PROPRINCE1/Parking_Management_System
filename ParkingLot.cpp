#include "ParkingLot.h"
#include "CarParkingSpace.h"
#include "MotorcycleParkingSpace.h"
#include "TruckParkingSpace.h"
#include "EVCarParkingSpace.h"
#include "EVMotorcycleParkingSpace.h"
#include <iostream>

ParkingLot::ParkingLot(int car, int bike, int truck, int ec, int eb) {
    initializeSpaces(car,bike,truck,ec,eb);
}
ParkingLot::ParkingLot(const ParkingLot& other) {
    carSpace = other.carSpace;
    bikeSpace = other.bikeSpace;
    truckSpace = other.truckSpace;
    ecSpace = other.ecSpace;
    ebSpace = other.ebSpace;
    for (const auto& space : other.allSpaces) {
        ParkingSpace* newSpace = createSpaceForType(space->getVehicleType(), space->getSpaceID());
        if (space->isOccupied()) {
            newSpace->parkVehicle(space->getLicensePlate());
        }
        allSpaces.push_back(newSpace);
    }
}

void ParkingLot::initializeSpaces(int car, int bike, int truck, int ec, int eb) {
    vector<QString> vehicleTypes = {
        "Car", "Motorcycle", "Truck", "EV Car", "EV Motorcycle"
    };
    int var=0;
    int iteration_var = car;
    for (const auto& type : vehicleTypes) {
        if(type == "Car") iteration_var = car;
        if(type == "Motorcycle") iteration_var = bike;
        if(type == "Truck") iteration_var = truck;
        if(type == "EV Car") iteration_var = ec;
        if(type == "EV Motorcycle") iteration_var = eb;
        for (int i = 1; i <= iteration_var; i++) {
            ParkingSpace* space = createSpaceForType(type, i+var);
            if (space) {
                allSpaces.push_back(space);
            }
        }
        var+=MAX_SPACES;
    }
}

int ParkingLot::getStartIndex(const QString& vehicleType) const {
    if (vehicleType == "Car") return 1;
    if (vehicleType == "Motorcycle") return MAX_SPACES + 1;
    if (vehicleType == "Truck") return 2 * MAX_SPACES + 1;
    if (vehicleType == "EV Car") return 3 * MAX_SPACES + 1;
    if (vehicleType == "EV Motorcycle") return 4 * MAX_SPACES + 1;
    return -1;
}

int ParkingLot::getEndIndex(const QString& vehicleType) const {
    if (vehicleType == "Car") return MAX_SPACES;
    if (vehicleType == "Motorcycle") return 2 * MAX_SPACES;
    if (vehicleType == "Truck") return 3 * MAX_SPACES;
    if (vehicleType == "EV Car") return 4 * MAX_SPACES;
    if (vehicleType == "EV Motorcycle") return 5 * MAX_SPACES;
    return -1;
}

void ParkingLot::resizeParkingLot(int newCar, int newBike, int newTruck, int newEC, int newEB) {
    ParkingLot tempLot(*this);
    carSpace = newCar;
    bikeSpace = newBike;
    truckSpace = newTruck;
    ecSpace = newEC;
    ebSpace = newEB;

    allSpaces.clear();
    initializeSpaces(carSpace,bikeSpace,truckSpace,ecSpace,ebSpace);

    for (const auto& oldSpace : tempLot.allSpaces) {
        if (oldSpace->isOccupied()) {
            ParkingSpace* newSpace = findSpaceByLicensePlate(oldSpace->getLicensePlate());
            if (newSpace) {
                newSpace->parkVehicle(oldSpace->getLicensePlate());
            }
        }
    }
}

ParkingSpace* ParkingLot::createSpaceForType(const QString& type, int id) {
    if (type == "Car") return new CarParkingSpace(id);
    if (type == "Motorcycle") return new MotorcycleParkingSpace(id);
    if (type == "Truck") return new TruckParkingSpace(id);
    if (type == "EV Car") return new EVCarParkingSpace(id);
    if (type == "EV Motorcycle") return new EVMotorcycleParkingSpace(id);
    return nullptr;
}

ParkingLot::~ParkingLot() {
    for (auto space : allSpaces) {
        delete space;
    }
}

ParkingSpace* ParkingLot::findAvailableSpace(const QString& vehicleType) {
    for (auto space : allSpaces) {
        if (space->getVehicleType() == vehicleType && !space->isOccupied()) {
            return space;
        }
    }
    return nullptr;
}

bool ParkingLot::parkVehicle(const QString& vehicleType, const QString& licensePlate) {
    ParkingSpace* space = findAvailableSpace(vehicleType);
    if (space) {
        space->parkVehicle(licensePlate);
        return true;
    }
    return false;
}

ParkingSpace* ParkingLot::findSpaceByLicensePlate(const QString& licensePlate) const {
    for (auto space : allSpaces) {
        if (space->isOccupied() && space->getLicensePlate() == licensePlate) {
            return space;
        }
    }
    return nullptr;
}

double ParkingLot::removeVehicle(const QString& licensePlate) {
    ParkingSpace* space = findSpaceByLicensePlate(licensePlate);
    if (space) {
        double fee = space->calculateFee();
        space->removeVehicle();
        return fee;
    }
    return 0.0;
}

QString ParkingLot::getVehicleTypeForLicensePlate(const QString& licensePlate) const {
    ParkingSpace* space = findSpaceByLicensePlate(licensePlate);
    return space ? space->getVehicleType() : "";
}

int ParkingLot::getSpaceIdForLicensePlate(const QString& licensePlate) const {
    ParkingSpace* space = findSpaceByLicensePlate(licensePlate);
    return space ? space->getSpaceID() : -1;
}

void ParkingLot::displayAvailableSpaces() const {
    cout << "Available Spaces:\n";

    for (const auto& type : {"Car", "Motorcycle", "Truck", "EV Car", "EV Motorcycle"}) {
        int available = getAvailableSpaces(type);
        cout << type << ": " << available << "/" << MAX_SPACES << "\n";
    }
}

int ParkingLot::getTotalSpaces(const QString& vehicleType) const {
    int count = 0;
    for (auto space : allSpaces) {
        if (space->getVehicleType() == vehicleType) {
            count++;
        }
    }
    return count;
}

int ParkingLot::getAvailableSpaces(const QString& vehicleType) const {
    int count = 0;
    for (auto space : allSpaces) {
        if (space->getVehicleType() == vehicleType && !space->isOccupied()) {
            count++;
        }
    }
    return count;
}

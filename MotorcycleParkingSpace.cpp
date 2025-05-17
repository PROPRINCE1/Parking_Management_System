#include "MotorcycleParkingSpace.h"

MotorcycleParkingSpace::MotorcycleParkingSpace(int id) : ParkingSpace(id) {}

MotorcycleParkingSpace::~MotorcycleParkingSpace() {}

QString MotorcycleParkingSpace::getVehicleType() const {
    return "Motorcycle";
}

double MotorcycleParkingSpace::calculateFee() const {
    if (!occupied) return 0.0;

    double hours = entryTime.secsTo(QDateTime::currentDateTime()) / 3600.0;
    if(hours < 1) return 50;
    return hours * 50;
}

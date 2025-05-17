#include "EVMotorcycleParkingSpace.h"

EVMotorcycleParkingSpace::EVMotorcycleParkingSpace(int id) : ParkingSpace(id) {}

EVMotorcycleParkingSpace::~EVMotorcycleParkingSpace() {}

QString EVMotorcycleParkingSpace::getVehicleType() const {
    return "EV Motorcycle";
}

double EVMotorcycleParkingSpace::calculateFee() const {
    if (!occupied) return 0.0;

    double hours = entryTime.secsTo(QDateTime::currentDateTime()) / 3600.0;
    if(hours < 1) return 300;
    return hours * 300;
}

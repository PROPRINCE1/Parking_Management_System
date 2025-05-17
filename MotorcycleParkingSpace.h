#ifndef MOTORCYCLEPARKINGSPACE_H
#define MOTORCYCLEPARKINGSPACE_H

#include "ParkingSpace.h"

class MotorcycleParkingSpace : public ParkingSpace {
public:
    MotorcycleParkingSpace(int id);
    ~MotorcycleParkingSpace() override;

    QString getVehicleType() const override;
    double calculateFee() const override;
};

#endif // MOTORCYCLEPARKINGSPACE_H

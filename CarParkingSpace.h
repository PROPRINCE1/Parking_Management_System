#ifndef CARPARKINGSPACE_H
#define CARPARKINGSPACE_H

#include "ParkingSpace.h"

class CarParkingSpace : public ParkingSpace {
public:
    CarParkingSpace(int id);
    ~CarParkingSpace() override;

    QString getVehicleType() const override;
    double calculateFee() const override;
};

#endif // CARPARKINGSPACE_H

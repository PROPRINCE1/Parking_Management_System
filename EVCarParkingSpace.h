#ifndef EVCARPARKINGSPACE_H
#define EVCARPARKINGSPACE_H

#include "ParkingSpace.h"

class EVCarParkingSpace : public ParkingSpace {
public:
    EVCarParkingSpace(int id);
    ~EVCarParkingSpace() override;

    QString getVehicleType() const override;
    double calculateFee() const override;
};

#endif // EVCARPARKINGSPACE_H

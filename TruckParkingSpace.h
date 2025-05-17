#ifndef TRUCKPARKINGSPACE_H
#define TRUCKPARKINGSPACE_H

#include "ParkingSpace.h"

class TruckParkingSpace : public ParkingSpace {
public:
    TruckParkingSpace(int id);
    ~TruckParkingSpace() override;

    QString getVehicleType() const override;
    double calculateFee() const override;
};

#endif

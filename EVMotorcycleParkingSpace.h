#ifndef EVMOTORCYCLEPARKINGSPACE_H
#define EVMOTORCYCLEPARKINGSPACE_H

#include "ParkingSpace.h"

class EVMotorcycleParkingSpace : public ParkingSpace {
public:
    EVMotorcycleParkingSpace(int id);
    ~EVMotorcycleParkingSpace() override;

    QString getVehicleType() const override;
    double calculateFee() const override;
};

#endif // EVMOTORCYCLEPARKINGSPACE_H

// Anil Ilaga 22002044

#ifndef HW1_PARKINGSYSTEM_H
#define HW1_PARKINGSYSTEM_H
#include "ParkingLot.h"

class ParkingSystem
{
public:
    ParkingSystem();
    ~ParkingSystem();

    void createLot(int id, int rows, int columns);
    void removeLot(int id);
    void listLots();
    void lotContents(int id);
    void parkCar(int lotId, string location, string carType, int plateNo );//location,type,plateId
    void findCar(int plateNumber);
    void removeCar(int plateNumber);
    int findLotIndex(int lotId);

private:
    ParkingLot* lots;
    int totalLots;
    int totalCars;
    int* carIds;
};


#endif //HW1_PARKINGSYSTEM_H

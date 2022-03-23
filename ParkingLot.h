// Anil Ilaga 22002044

#ifndef HW1_PARKINGLOT_H
#define HW1_PARKINGLOT_H
#include "Car.h"

class ParkingLot
{
public:
    ParkingLot();
    ParkingLot(int ,int, int);
    ~ParkingLot();
    void parkCar(int,string ,int ,int);
    void listCars();
    void removeCar(int carId);
    int getEmpty();
    int getId();
    int getRow();
    int getColumn();
    char getLastLetter();
    void showCar(int plateId,int,int);
    bool isThere(int plateId,int &r,int &c);
    ParkingLot& operator= (const ParkingLot& );
    void updateCars();
    void printLot();
    void initializeLetters();
    int isParkable(const int carId,const string carType, int row, int column);
    void removeAllCars();


private:
    int lotId;
    int emptyPlaces;
    int r;
    int c;
    int totalCars;
    int totalArea;
    Car** lot;
    char* letters;
    int* parkedCars;
};


#endif //HW1_PARKINGLOT_H

// Anil Ilaga 22002044

#include "Car.h"

Car::Car()
{
    carId = -1;
    type = "+";
}

int Car::getId(){ return carId; }
string Car::getType() { return type; }
Car& Car::operator= (const Car& c){
    this->carId = c.carId;
    this->type = c.type;
    return *this;
}

void Car::setId(int id) { carId = id; }
void Car::setType(string carType){ type = carType; }

// Anil Ilaga 22002044

#ifndef HW1_CAR_H
#define HW1_CAR_H


#include <iostream>
using namespace std;

class Car
{
public:
    Car();

    int getId();
    void setId(int);
    string getType();
    void setType(string);
    Car& operator= (const Car& );

private:
    int carId;
    string type;
};


#endif //HW1_CAR_H

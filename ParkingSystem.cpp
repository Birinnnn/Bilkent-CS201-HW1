// Anil Ilaga 22002044

#include <iostream>
using namespace std;
#include "ParkingSystem.h"

ParkingSystem::ParkingSystem()
{
    totalLots = 0;
    totalCars = 0;
    lots = NULL;
    carIds = NULL;
}

ParkingSystem::~ParkingSystem()
{
        delete [] carIds;
        delete [] lots;
}
void ParkingSystem::createLot(int id, int rows, int columns){
    int index = findLotIndex(id);
    if( index != -1){
        cout << "Cannot create the parking lot " << id << ", a lot with this ID already exists" << endl;
    }
    else{
        if( rows <= 0 || rows >= 13 || columns >= 13 || columns <= 0){//Checking bounds
            cout << "Cannot create the parking lot "<< id <<", dimensions exceed acceptable bounds" << endl;
        }
        else{//Bounds are accepted
            totalLots++;
            if( totalLots == 1){//Only 1 member
                lots = new ParkingLot[1];
                lots[0] = ParkingLot(id,rows,columns);
            }
            else {  //More than 1 member
                ParkingLot *temp = lots;
                lots = new ParkingLot[totalLots];

                //Copying lots via overloaded assignment tool.
                for (int i = 0; i < totalLots - 1; i++) {
                    lots[i] = temp[i];
                }
                lots[totalLots - 1] = ParkingLot(id,rows,columns);//Adding the new lot
                delete [] temp;
                temp = NULL;
            }
            cout << "Parking lot with ID "<< id << " and dimensions (" << rows << "," << columns <<") has been added to the system" << endl;
        }
    }
}

int ParkingSystem::findLotIndex(int lotId){
    for( int i = 0; i < totalLots; i++){
        if( lots[i].getId() == lotId)
            return i;
    }
    return -1;
}

void ParkingSystem::removeLot(int id){
    int index = findLotIndex(id);

    if( index != -1){
        if( totalLots >= 2){//There will be at least 1 lot.
            ParkingLot* temp = new ParkingLot[totalLots-1];//New pointer for copying lots.

            for(int i = 0; i < totalLots-1; i++){//Lots are being copied by overloaded assignment operator except the given lot.
                if( i < index){
                    temp[i] = lots[i];
                }
                else if( i >= index){
                    temp[i] = lots[i+1];
                }
            }
            lots[index].removeAllCars();//Deleting cars from given lot.

            cout << "Lot " << id <<" has been successfully removed from the system." << endl;
            delete [] lots;
            totalLots--;
            lots = temp;
        }
        else if( totalLots == 1){
            delete[] lots;
            totalLots--;
        }
    }
    else{
        cout << " is not in the system." << endl;
    }
}

void ParkingSystem::listLots(){
    if( totalLots <= 0)
        cout << "No lots to list"<< endl;
    else{
        cout << "List of lots:" << endl;
        for( int i = 0; i < totalLots; i++){
            cout << "ID: " << lots[i].getId() << ", Dim: (" << lots[i].getRow() << "," << lots[i].getColumn()
                 << "), number of empty parking spaces: " << lots[i].getEmpty();
            if( i != totalLots-1)
                cout << endl;
        }
    }
}

void ParkingSystem::lotContents(int id){
    int index = findLotIndex(id);
    if( index == -1 ){
        cout << "There is no parking lot with id: " << id << " in the system."<< endl;
    }
    else{
        cout << "ID: " << id << ", (" << lots[index].getRow() << "," << lots[index].getColumn()
             << "), empty slots: " << lots[index].getEmpty() << ", parked cars: ";
        lots[index].listCars();
        lots[index].printLot();
    }
}

void ParkingSystem::parkCar(int lotId, string location, string carType, int plateNumber ) {
    int index = findLotIndex(lotId);
    char letter = location[0];
    bool isPlateUnique = true;

    for (int i = 0; i < totalCars; i++) {
        if (carIds[i] == plateNumber)
            isPlateUnique = false; //If plate is found
    }
    if (index == -1)
        cout << "Lot " << lotId << " is not in the system." << endl;
    if ( isPlateUnique && index != -1) {
            int row = lots[index].getRow() - (lots[index].getLastLetter() - letter)-1;//Converting the location row to integer.
            int column = -1;

            string str;
            //Converting the column to the integer.
            if (location.length() == 2)
                str = location.substr(1, 2);
            if (str == "1")
                column = 0;
            else if (str == "2")
                column = 1;
            else if (str == "3")
                column = 2;
            else if (str == "4")
                column = 3;
            else if (str == "5")
                column = 4;
            else if (str == "6")
                column = 5;
            else if (str == "7")
                column = 6;
            else if (str == "8")
                column = 7;
            else if (str == "9")
                column = 8;
            else if (location.length() == 3) {
                str = location.substr(1, 3);
                if (str == "10")
                    column = 9;
                else if (str == "11")
                    column = 10;
                else if (str == "12")
                    column = 11;
            }
            if( row == 0 && carType == "b"){//B type occupies 2 places and the bottom part should be given
                cout << "Cannot park heavy-duty car with number plate "
                     << plateNumber << ", at location " << location << ", not enough space." << endl;
            }
            else{
                int isParkable = lots[index].isParkable(plateNumber, carType, row, column);
                if ( isParkable == 1 ){
                    lots[index].parkCar(plateNumber,carType,row,column);
                    if( carType == "b"){
                        cout << "Heavy-duty ";
                    }
                    else if( carType == "a"){
                        cout << "Light-duty ";
                    }
                    cout << "car with number plate " << plateNumber << " has been parked at location " << location << ", lot "
                         << lotId << endl;

                    totalCars++;
                    if (totalCars == 1) {
                        carIds = new int(plateNumber);
                    } else if (totalCars > 1) {
                        int *temp = carIds;
                        carIds = new int[totalCars];
                        for (int i = 0; i < totalCars - 1; i++) {
                            carIds[i] = temp[i];
                        }
                        carIds[totalCars - 1] = plateNumber;
                        delete [] temp;
                    }
                }
                else if ( isParkable == 0){ //There is another car at given location.
                    cout << "Cannot park heavy-duty car with number plate " << plateNumber
                         << " at location " << location << ", already occupied" << endl;
                }
                else{//Can not be parked because of bounds.
                    cout << "Given location is out of bounds" << endl;
                }
            }
    }
}

void ParkingSystem::findCar(int plateNumber) {
    int row, column;
    bool isInside = false;
    row = -1;
    column = -1;

    for( int i = 0; i < totalCars; i++){
        if( carIds[i] == plateNumber){
            isInside = true;//The car is in.
        }
    }
    if( isInside ){
        for (int j = 0; j < totalLots; j++) {
            if( lots[j].isThere(plateNumber,row,column) )
                lots[j].showCar(plateNumber,row,column);
        }
    }
    else{
        cout << "The car with number plate "<< plateNumber << " is not in the system" << endl;
    }

}
void ParkingSystem::removeCar(int plateNumber) {
    int row, column,lotIndex,carIndex;
    lotIndex = -1;
    carIndex = -1;

    //Remove from carIds
    for(int i = 0; i< totalCars; i++){
        if( carIds[i] == plateNumber){
            carIndex = i;
        }
    }
    if( carIndex == -1){
        cout << "The car with number plate " << plateNumber << " is not in the system" << endl;
    }
    else{//We have the car
        if( totalCars > 1){
            int *temp = carIds;
            carIds = new int[totalCars-1];
            for(int i = 0; i < carIndex; i++){
                carIds[i] = temp[i];
            }
            for(int i = carIndex; i < totalCars-1;i++){
                carIds[i] = temp[i+1];
            }
            delete [] temp;
            temp = NULL;
        }
        else if( totalCars == 1){
            delete [] carIds;
            carIds = NULL;
        }

        //Remove from parkingLot
        for(int i = 0; i < totalLots; i++){
            if( lots[i].isThere(plateNumber,row,column))
                lotIndex = i;
        }
        //System has 0 lots.
        if( totalLots == 0){
            cout << "There are no lots to remove a car";
            return;
        }
        //The lot is in the system.
        if( totalLots > 0 && lotIndex != -1){
            lots[lotIndex].removeCar(plateNumber);
        }
        totalCars--;
    }
}
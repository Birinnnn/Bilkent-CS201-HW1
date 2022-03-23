// Anil Ilaga 22002044

#include "ParkingLot.h"

ParkingLot::ParkingLot()
{
    lotId = -1;
    emptyPlaces = -1;
    r = 0;
    c = 0;
    totalCars = 0;
    totalArea = 0;
    parkedCars = NULL;
    lot = NULL;
    letters = NULL;
}
ParkingLot::ParkingLot(int givenLotId,int row, int column){
    lotId = givenLotId;
    r = row;
    c = column;
    totalCars = 0;
    totalArea = row*column;
    emptyPlaces = row*column;
    parkedCars = NULL;
    if( row > 0 && column > 0){
        lot = new Car*[row];
        initializeLetters();
        for( int i = 0; i < row; i++){
            lot[i] = new Car[column];
        }
    }
    else{
        letters = NULL;
        lot = NULL;
    }
}

void ParkingLot::initializeLetters(){
    letters = new char[r];
    for( int j = 0; j < r; j++){
        if( j == 0 ){ letters[0] = 'A'; }
        else if( j == 1){ letters[j] = 'B';}
        else if( j == 2){ letters[j] = 'C';}
        else if( j == 3){ letters[j] = 'D';}
        else if( j == 4){ letters[j] = 'E';}
        else if( j == 5){ letters[j] = 'F';}
        else if( j == 6){ letters[j] = 'G';}
        else if( j == 7){ letters[j] = 'H';}
        else if( j == 8){ letters[j] = 'I';}
        else if( j == 9){ letters[j] = 'J';}
        else if( j == 10){ letters[j] = 'K';}
        else if( j == 11){ letters[j] = 'L';}
    }
}
bool ParkingLot::isThere(int plateId ,int &row, int &column){
    if( plateId > -1){
        for(int i = 0; i < r;i++){
            for(int j = 0;j<c;j++){
                if( lot[i][j].getId() == plateId ){
                    row = i;
                    column = j;
                    return true;
                }
            }
        }
    }
    return false;
}

void ParkingLot::removeAllCars(){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if( lot[i][j].getId() != -1 ){
                removeCar( lot[i][j].getId() );
            }
        }
    }
}

void ParkingLot::showCar(int plateId,int row,int column){

    if( plateId > -1){
        if( lot[row][column].getId() == plateId){
            if( lot[row][column].getType() == "a")
                cout << "Light-duty ";
            else if( lot[row][column].getType() == "b")
                cout << "Heavy-duty";
            else{
                cout << "Wrong type";
                return;
            }
        cout << " car with number plate " << plateId << " is at location " << letters[row] << column+1
             << ", lot " << lotId << endl;
        }
    }
}

ParkingLot::~ParkingLot()
{
    for( int i = 0; i < r; i++){
        delete [] lot[r-i-1];

    }

    if( r > 0){
        delete [] lot;
        delete [] letters;
    }
    if( totalCars > 0){
        delete [] parkedCars;
    }
}

int ParkingLot::getId(){
    return lotId;
}
int ParkingLot::getRow(){
    return r;
}
int ParkingLot::getColumn(){
    return c;
}

void ParkingLot::listCars(){
    if( totalCars == 0){
        cout << "no cars yet" << endl;
    }
    else{
        updateCars();
        for(int i = 0; i < totalCars-1; i++){
            cout << parkedCars[i] << ", ";
        }
        cout << parkedCars[totalCars-1] << endl;
    }
}

void ParkingLot::updateCars(){
    int index = 0;
    if( totalCars > 0){
        delete [] parkedCars;
        parkedCars = new int[totalCars];
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                if(lot[i][j].getId() != -1 && lot[i][j].getType() != "+"){
                    parkedCars[index] = lot[i][j].getId();
                    index++;
                }
            }
        }
    }
    else if(totalCars == 0){
        delete[] parkedCars;
        parkedCars = NULL;
    }

}

char ParkingLot:: getLastLetter(){
    return letters[r-1];
}
void ParkingLot::printLot(){
    cout << endl << "   ";
    for(int i = 0; i < c; i++){
        cout << i+1 << " ";
    }
    cout << endl;
    for(int i = 0; i < r; i ++){
        for(int j = 0; j < c; j++){
            if( j == 0)
                cout << letters[i] << "  " << lot[i][j].getType() << " ";
            else if( j <= 8)
                cout << lot[i][j].getType() << " ";
            else if( j > 8)
                cout << lot[i][j].getType() << "  ";
        }
        cout << endl;
    }
}


int ParkingLot::isParkable(const int carId,const string carType, int row, int column){
    if( row < r &&  column < c && row >= 0 && column >= 0){
        if( lot[row][column].getType() == "+"){
            if( carType == "b" && row > 0){
                if( lot[row-1][column].getType() == "+"){
                    return 1;
                }
            }
            else if( carType == "a" && lot[row][column].getId() == -1){
                return 1;
            }
        }
        else{
            return 0;
        }
    }
    return -1;
}

void ParkingLot::parkCar(const int carId,const string carType, int row,int column){
    if(isParkable(carId, carType,row,column) == 1){
        if(carType == "b" ){
                lot[row-1][column].setType("b");
                lot[row][column].setId( carId );
                lot[row][column].setType(carType);
                emptyPlaces -= 2;
        }
        else if( carType == "a" ){
            lot[row][column].setId( carId );
            lot[row][column].setType(carType);
            emptyPlaces--;
        }
        totalCars++;
        if( totalCars == 1){
            parkedCars = new int[totalCars];
            parkedCars[0] = carId;
        }
        else if( totalCars > 1){
            updateCars();
        }
    }
}

ParkingLot& ParkingLot::operator= (const ParkingLot& givenLot){ //Check
    if( this == &givenLot)//To avoid self assignment
        return *this;
        //Deleting pointers if it should
        if( this->r  != givenLot.r || this->c != givenLot.c ){
            if( r > 0 && c > 0){
                for( int i = 0; i<r;i++){
                    delete [] lot[i];
                }
                delete [] lot;
                delete [] letters;
            }
        }

        if( totalCars != givenLot.totalCars && totalCars > 0){
            delete[] parkedCars;
        }
        //Copying pointers
        if( givenLot.totalCars > 0){
            parkedCars = new int[givenLot.totalCars];
            for( int i = 0; i < givenLot.totalCars;i++){
                parkedCars[i] = givenLot.parkedCars[i];
            }
        }
        else{
            parkedCars = NULL;
        }
        //Copying data members.
        this->lotId = givenLot.lotId;
        this->totalCars = givenLot.totalCars;
        this->r = givenLot.r;
        this->c = givenLot.c;
        this->emptyPlaces = givenLot.emptyPlaces;
        this->totalArea = givenLot.totalArea;
        //Creating pointers with new values
        if( givenLot.r > 0 && givenLot.c > 0){
            letters = new char[givenLot.r];
            this->lot = new Car* [givenLot.r];
            for( int i = 0; i < givenLot.r; i++){
                lot[i] = new Car[givenLot.c];
            }
        }
        else{
            letters = NULL;
            lot = NULL;
        }
        //Initializing pointers
        for(int i = 0; i < r;i++){
            letters[i] = givenLot.letters[i];
            for(int j = 0; j<c;j++){
                lot[i][j] = givenLot.lot[i][j];
            }
        }

        return *this;
}

int ParkingLot::getEmpty(){
    return emptyPlaces;
}

void ParkingLot::removeCar(const int carId){
    for( int i = 0; i < r; i++){
        for( int j = 0; j < c; j++){
            if( lot[i][j].getId() == carId && carId != -1){
                if( lot[i][j].getType() == "b"){
                    lot[i-1][j].setType("+");
                    emptyPlaces++;
                    cout << "Heavy-duty";
                }
                else{
                    cout << "Light-duty";
                }
                lot[i][j].setType("+") ;
                lot[i][j].setId(-1);
                totalCars--;
                emptyPlaces++;
                cout << " car with number plate " << carId << " car has been removed from slot "
                     << letters[i] << j+1 << ", lot " << lotId << endl;
                updateCars();
            }
        }
    }
}
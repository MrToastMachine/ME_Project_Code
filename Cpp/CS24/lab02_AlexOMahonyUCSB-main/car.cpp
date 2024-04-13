// Alex O'Mahony - 6872774 
// This is the only file to submit.

#include "car.hpp"
#include <cstddef>
#include <cstring>
#include "perf.hpp"
// #include .......

using namespace std;

Car::Car(){
    //cout<<"Car Created!! - Method 1"<<endl;

    manufacturer = nullptr;
    model = nullptr;
    zeroToSixtyNs = 0;
    headonDragCoeff = 0;
    horsepower = 0;
    backseatDoors = None;
    seatCount = 0; 
}

Car::Car(char const* const manufacturerName, char const* const modelName, PerformanceStats perf, uint8_t numSeats, DoorKind backseatDoorDesign){
    //cout<<"Car Created!! - Method 2"<<endl;

    manufacturer = new char[sizeof(manufacturerName)];
    model = new char[sizeof(modelName)];
    strcpy(manufacturer, manufacturerName);
    strcpy(model, modelName);

    zeroToSixtyNs = perf.zeroToSixtyNs;
    headonDragCoeff = perf.headonDragCoeff;
    horsepower = perf.horsepower;
    backseatDoors = backseatDoorDesign;
    seatCount = numSeats;
}

Car::Car(Car const& o){
    //cout<<"Car Created!! - Method 3"<<endl;
    manufacturer = new char[sizeof(o.manufacturer)];
    model = new char[sizeof(o.model)];

    strcpy(manufacturer,o.manufacturer);
    strcpy(model,o.model);

    zeroToSixtyNs = o.zeroToSixtyNs;
    headonDragCoeff = o.headonDragCoeff;
    horsepower = o.horsepower;
    backseatDoors = o.backseatDoors;
    seatCount = o.seatCount;
}

Car& Car::operator=(Car const& o){
    // Car newCar = Car(o.manufacturer,o.model,o.getStats(),o.seatCount,o.backseatDoors);
    manufacturer = o.manufacturer;
    model = o.model;
    zeroToSixtyNs = o.zeroToSixtyNs;
    headonDragCoeff = o.headonDragCoeff;
    horsepower = o.horsepower;
    backseatDoors = o.backseatDoors;
    seatCount = o.seatCount;

    return *this;
}

Car::~Car(){
    //cout<<"Deleting Car: "<<manufacturer<<", "<<model<<endl;
    delete []manufacturer;
    delete []model;
}

char const* Car::getManufacturer() const{
    return manufacturer;
}

char const* Car::getModel() const{
    return model;
}

PerformanceStats Car::getStats() const{
    return PerformanceStats(horsepower,zeroToSixtyNs, headonDragCoeff);
}

uint8_t Car::getSeatCount() const{
    return seatCount;
}

DoorKind Car::getBackseatDoors() const{
    return backseatDoors;
}

void Car::manufacturerChange(char const* const newManufacturer){
    manufacturer = new char[sizeof(newManufacturer)];
    strcpy(manufacturer, newManufacturer);
    // *manufacturer = new char[size];
}

void Car::modelNameChange(char const* const newModelName){
    model = new char[sizeof(newModelName)];
    strcpy(model, newModelName);
}

void Car::reevaluateStats(PerformanceStats newStats){
    zeroToSixtyNs = newStats.zeroToSixtyNs;
    headonDragCoeff = newStats.headonDragCoeff;
    horsepower = newStats.horsepower;
}

void Car::recountSeats(uint8_t newSeatCount){
    seatCount = newSeatCount;
}

void Car::reexamineDoors(DoorKind newDoorKind){
    backseatDoors = newDoorKind;
}

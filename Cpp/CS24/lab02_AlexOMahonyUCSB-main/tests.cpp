#include <iostream>
#include "car.cpp"

using namespace std;

void ptrTesting(){
    int* p = nullptr;
    int x = 5;

    p = &x;

    cout<<"x = "<<x<<endl;
    cout<<"p = "<<p<<endl;
    cout<<"*p = "<<*p<<endl;

    cout<<"Making Changes!!"<<endl;
    
    *p = 16;

    cout<<"x = "<<x<<endl;
    cout<<"p = "<<p<<endl;
    cout<<"*p = "<<*p<<endl;
}

void testCharPtr(){
    char const* const manName = "Groon";
    char* man;
    char* endLoc;

    man = (char*) malloc(sizeof(manName));
    strcpy(man, manName);
    // strcpy(man, manName);

    endLoc = man;
    // cout<<strcpy(manufacturer,manufacturerName)<<endl;

    cout<<"manufacturerName: "<<manName<<endl;
    cout<<"manufacturer: "<<man<<endl;
    cout<<"endLoc: "<<endLoc<<endl;
    
}

void testConstructor(){
    cout<<"Testing Constructors"<<endl;
    PerformanceStats p(3000,4,0.4);
    DoorKind d = Hinge;

    char const* const man = "Beans";
    char const* const mod = "v200";
    uint8_t nSeats = 4;
    
    Car moon(man, mod,p,nSeats,d);

    Car BEAEN(moon);

    cout<<"Finished Constructor Testing"<<endl;
}

void testGetMan(){
    cout<<"Testing getManufacturer"<<endl;

    PerformanceStats p(3000,4,0.4);
    DoorKind d = Hinge;

    char const* const man = "Toyota";
    char const* const mod = "Prius";
    uint8_t nSeats = 4;
    
    Car toy(man, mod,p,nSeats,d);

    cout<<"Manufacturer: "<<toy.getManufacturer()<<endl;
}

void testGetPerf(){
    cout<<"Testing getStats"<<endl;

    PerformanceStats p(3000,4,0.4);
    DoorKind d = Hinge;

    char const* const man = "Toyota";
    char const* const mod = "Prius";
    uint8_t nSeats = 4;
    
    Car toy(man, mod,p,nSeats,d);


    PerformanceStats info = toy.getStats();
    cout<<info.horsepower<<endl;
    cout<<info.zeroToSixtyNs<<endl;
    cout<<info.headonDragCoeff<<endl;
}

void testManuChange(){
    cout<<"Testing manufacturer change"<<endl;

    PerformanceStats p(3000,4,0.4);
    DoorKind d = Hinge;

    char const* const man = "Toyota";
    char const* const mod = "Prius";
    uint8_t nSeats = 4;
    
    Car toy(man, mod,p,nSeats,d);

    char const* const newMan = "Renault";
    toy.manufacturerChange(newMan);
    cout<<"Changed Manufacturer!!"<<endl;
    cout<<"New Man: "<<toy.getManufacturer()<<endl;
}

void testModChange(){
    cout<<"Testing manufacturer change"<<endl;

    PerformanceStats p(3000,4,0.4);
    DoorKind d = Hinge;

    char const* const man = "Toyota";
    char const* const mod = "Prius";
    uint8_t nSeats = 4;
    
    Car toy(man, mod,p,nSeats,d);

    char const* const newMod = "Corolla";
    toy.modelNameChange(newMod);
    cout<<"Changed Manufacturer!!"<<endl;
    cout<<"New Mod: "<<toy.getModel()<<endl;
}

void testNewStats(){
    cout<<"Testing getStats"<<endl;

    PerformanceStats p(3000,4,0.4);
    PerformanceStats pNew(1000,6,0.1);
    DoorKind d = Hinge;

    char const* const man = "Toyota";
    char const* const mod = "Prius";
    uint8_t nSeats = 4;
    
    Car toy(man, mod,p,nSeats,d);

    PerformanceStats info1 = toy.getStats();
    cout<<info1.horsepower<<endl;
    cout<<info1.zeroToSixtyNs<<endl;
    cout<<info1.headonDragCoeff<<endl;

    toy.reevaluateStats(pNew);

    PerformanceStats info2 = toy.getStats();
    cout<<info2.horsepower<<endl;
    cout<<info2.zeroToSixtyNs<<endl;
    cout<<info2.headonDragCoeff<<endl;
}

void testDestructor(){
    cout<<"Testing Destructor"<<endl;

    PerformanceStats p(3000,4,0.4);
    DoorKind d = Hinge;

    char const* const man = "Toyota";
    char const* const mod = "Prius";
    uint8_t nSeats = 4;
    
    Car toy(man, mod,p,nSeats,d);

}

void testCC(){
    cout<<"Testing Constructors"<<endl;
    PerformanceStats p(3000,4,0.4);
    DoorKind d = Hinge;

    char const* const man = "Beans";
    char const* const mod = "v200";
    uint8_t nSeats = 4;
    
    Car moon(man, mod,p,nSeats,d);

    Car BEAEN(moon);

    Car other(moon);

    cout<<"New object's manu"<<endl;
    cout<<other.getManufacturer()<<endl;

    cout<<"Finished Constructor Testing"<<endl;
}

int main(){
    cout<<"Running Tests"<<endl;
    // ptrTesting();
    // testCharPtr();

    // testConstructor();
    // testGetMan();
    // testGetPerf();
    // testManuChange();
    // testModChange();
    // testNewStats();
    // testDestructor();
    
    testCC();

    cout<<"end of main"<<endl;
    return 0;
} 

/* ALL FUNCTIONS TO TEST
    + Constructors (3 types)
        > Null/Empty            - done!
        > Given Values          - done!
        > Copy given object 'o' - done!
    + operator= overload        - done!
    + Destructor                
    + getManufacturer           - done!
    + getModel                  - done!
    + getStats                  - done!
    + getSeatCount              - done!
    + getBackseatDoors          - done!
    + manufacturerChange        - done!
    + modelNameChange           - done!
    + reevaluateStats           - done!
    + recountSeats              - done!
    + reexamineDoors            - done!
*/

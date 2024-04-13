#ifndef CAR_HPP
#define CAR_HPP

#include "perf.hpp"
#include "doors.hpp"

class Car{
    private:
        char* manufacturer;
        char* model;
        uint32_t zeroToSixtyNs;
        float headonDragCoeff;
        uint16_t horsepower;
        DoorKind backseatDoors;
        uint8_t seatCount;
    public:
        Car();
        Car(char const* const manufacturerName, char const* const modelName, PerformanceStats perf, uint8_t numSeats, DoorKind backseatDoorDesign);
        Car(Car const& o);
        Car& operator=(Car const& o);
        ~Car();
        char const* getManufacturer() const;
        char const* getModel() const;
        PerformanceStats getStats() const;
        uint8_t getSeatCount() const;
        DoorKind getBackseatDoors() const;
        void manufacturerChange(char const* const newManufacturer);
        void modelNameChange(char const* const newModelName);
        void reevaluateStats(PerformanceStats newStats);
        void recountSeats(uint8_t newSeatCount);
        void reexamineDoors(DoorKind newDoorKind);
};

#endif //CAR_HPP
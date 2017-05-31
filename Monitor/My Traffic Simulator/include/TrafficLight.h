#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <string>
#include <deque>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>

#include "../include/Vehicle.h"

using namespace std;

struct MapCoord
{
    int x, y;
};

class Vehicle;
class TrafficLight
{
    #ifdef GTest
    public:
    #else
    private:
    #endif
    size_t node;
    size_t direction;
    size_t countdown;
    int recalcCountdown=0;
    size_t maxVQueue;
    bool green;
    size_t timerGreen;
    size_t timerRed;
    MapCoord coord;
    vector<shared_ptr<Vehicle>> vehicles;

    public:
        TrafficLight(size_t direction, size_t countdown, size_t maxVQueue, size_t node, bool light );
        size_t GetDirection() const;
        bool GetLight() const;
        MapCoord GetCoord() const;
        void SetCoord(int x, int y);
        size_t CountVehicles() const;
        size_t GetMaxVQueue()const;
        void SwitchLight();
        bool EnQueue(const shared_ptr<Vehicle>& v);
        bool EnQueue(const shared_ptr<Vehicle>& v,size_t id);
        void Clean(size_t at);
        shared_ptr<Vehicle> FirstVehicle() const;
        void Update();
        void Modify(int quantity);
        size_t GetVehiculoLocation(const shared_ptr<Vehicle>& v) const;
        size_t GetNode()const;
        size_t GetTimer() const;
};

#endif // TRAFFICLIGHT_H

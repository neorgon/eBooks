#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <string>
#include <deque>
#include <memory>
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
    size_t ID=1;
    size_t direction;
    size_t countdown;
    size_t maxVQueue;
    bool green;
    size_t timer;
    MapCoord coord;
    deque<shared_ptr<Vehicle>> vehicles;

    public:
        TrafficLight(size_t direction, size_t countdown, size_t maxVQueue, bool light = true) :
             direction{direction}, countdown{countdown}, maxVQueue{maxVQueue}, green{light}
        {
            vehicles.resize(maxVQueue);
            for(auto& i: vehicles)
            {
                i = nullptr;
            }
            timer = countdown;
        };
        size_t GetTLID() const;
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
        bool DeQueue();
        void Update();
        size_t GetVehiculoLocation(const shared_ptr<Vehicle>& v) const;
};

#endif // TRAFFICLIGHT_H

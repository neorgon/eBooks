#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H
#include <string>
#include <deque>
#include <memory>
#include "Vehicle.h"

using namespace std;

class Vehicle;
class TrafficLight
{
    size_t ID;
    size_t direction;
    size_t countdown;
    size_t maxVQueue;
    bool green;
    size_t timer;
    deque<shared_ptr<Vehicle>> vehicles;

    public:
        TrafficLight(size_t id, size_t d, size_t c, size_t m, bool l = true) :
            ID{id}, direction{d}, countdown{c}, maxVQueue{m}, green{l}
        {
            for (size_t i = 0; i < maxVQueue; i++)
                vehicles[i] = nullptr;
            timer = countdown;
        };
        size_t GetTLID() const;
        size_t GetDirection() const;
        bool GetLight() const;
        size_t CountVehicles() const;
        bool SwitchLight();
        bool EnQueue(const Vehicle &v);
        shared_ptr<Vehicle> FirstVehicle() const;
        bool DeQueue();
        void Update();
};

#endif // TRAFFICLIGHT_H

#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H
#include <string>
#include <queue>
#include <memory>
#include "Vehicle.h"

using namespace std;

//class Vehicle;
class TrafficLight
{
    string ID;
    size_t countdown;
    size_t maxVQueue;
    bool light;
    queue<shared_ptr<Vehicle>> vehicles;

    public:
        TrafficLight(const string &id, size_t c, size_t m, bool l = true) : ID{id}, countdown{c}, maxVQueue{m}, light{l} {};
        string GetTLID() const;
        bool GetLight() const;
        size_t CountFreeSpaces() const;
        bool SwitchLight();
        bool EnQueue(const Vehicle &v);
        shared_ptr<Vehicle> FirstVehicle();
        bool DeQueue();
};

#endif // TRAFFICLIGHT_H

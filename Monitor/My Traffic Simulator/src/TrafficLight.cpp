#include "../include/TrafficLight.h"

string TrafficLight::GetTLID() const
{
    return ID;
}

bool TrafficLight::GetLight() const
{
    return green;
}

size_t TrafficLight::CountFreeSpaces() const
{
    return maxVQueue - vehicles.size();
}

bool TrafficLight::SwitchLight()
{
    return !green;
}

bool TrafficLight::EnQueue(const Vehicle &v)
{
    if (maxVQueue < vehicles.size())
    {
        vehicles.push(make_shared<Vehicle>(v));
        return true;
    }

    return false;
}

shared_ptr<Vehicle> TrafficLight::FirstVehicle()
{
    if (vehicles.empty())
        return nullptr;

    return vehicles.front();
}

bool TrafficLight::DeQueue()
{
    if (vehicles.empty())
        return false;
    if (!light)
        return false;
    vehicles.pop();

    return true;
}

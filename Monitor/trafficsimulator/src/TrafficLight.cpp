#include "../include/TrafficLight.h"

string TrafficLight::GetTLID() const
{
    return ID;
}

bool TrafficLight::GetLight() const
{
    return light;
}

size_t TrafficLight::CountFreeSpaces() const
{
    return maxLTQueue - vehicles.size();
}

bool TrafficLight::SwitchLight()
{
    return !light;
}

bool TrafficLight::EnQueue(const Vehicle &v)
{
    if (maxLTQueue < vehicles.size())
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

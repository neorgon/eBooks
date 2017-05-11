#include "../include/TrafficLight.h"

size_t TrafficLight::GetTLID() const
{
    return ID;
}

size_t TrafficLight::GetDirection() const
{
    return direction;
}

bool TrafficLight::GetLight() const
{
    return green;
}

size_t TrafficLight::CountVehicles() const
{
    size_t p = 0;
    size_t v = 0;

    while (p < maxVQueue)
    {
        if (vehicles[p])
            v++;
        p++;
    }

    return v;
}

bool TrafficLight::SwitchLight()
{
    return !green;
}

bool TrafficLight::EnQueue(const Vehicle &v)
{
    size_t i = maxVQueue;
    while (vehicles[i - 1] == nullptr && i >= 0) i--;
    if(i < maxVQueue && i >= 0 && vehicles[i] == nullptr)
    {
        vehicles[i] = make_shared<Vehicle>(v);
        return true;
    }

    return false;
}

shared_ptr<Vehicle> TrafficLight::FirstVehicle() const
{
    return vehicles.front();
}

bool TrafficLight::DeQueue()
{
    /*
    Tal vez este método tendría que devolver una lista de todos los vehículos que pueden pasar luz verde.
    */

    return true;
}

void TrafficLight::Update()
{
    if (timer > 0)
    {
        timer --;
    }
    else
    {
        SwitchLight();
        timer = countdown;
    }

    if (green)
    {
        DeQueue(); //?
    }
}

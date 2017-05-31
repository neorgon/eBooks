#include "../include/TrafficLight.h"

TrafficLight::TrafficLight(size_t direction, size_t countdown, size_t maxVQueue, size_t node, bool light = true) 
: direction{direction}, countdown{countdown}, maxVQueue{maxVQueue}, node{node}, green{light}
{
    vehicles.resize(maxVQueue);
    timerGreen = countdown+recalcCountdown;
    timerRed = countdown-recalcCountdown;
};

size_t TrafficLight::GetDirection() const
{
    return direction;
}

bool TrafficLight::GetLight() const
{
    return green;
}

MapCoord TrafficLight::GetCoord() const
{
    return coord;
}

void TrafficLight::SetCoord(int x, int y)
{
    coord.x = x;
    coord.y = y;
}

size_t TrafficLight::CountVehicles() const
{
    size_t p = 0;
    size_t v = 0;

    while (p < maxVQueue)
    {
        if (vehicles[p] != nullptr)
            v++;
        p++;
    }

    return v;
}

size_t TrafficLight::GetMaxVQueue()const
{
    return maxVQueue;
}

void TrafficLight::SwitchLight()
{
    green = !green;
}

bool TrafficLight::EnQueue(const shared_ptr<Vehicle>& v)
{
    size_t i = 0;
    while (i < maxVQueue)
    {
    	if( vehicles[i].get() == nullptr)
    	{
        	vehicles[i] = v;
       		return true;
    	}
    	i++;
    }
    return false;
}

bool TrafficLight::EnQueue(const shared_ptr<Vehicle>& v,size_t id)
{
	size_t i=vehicles.size()-(id+1);
    while (i < vehicles.size())
    {
    	if( vehicles[i] == nullptr)
    	{
        	vehicles[i] = v;
       		return true;
    	}
   		i++;
    }

    return false;
}

void TrafficLight::Clean(size_t at)
{
	vehicles.at(at-1)=nullptr;
}

shared_ptr<Vehicle> TrafficLight::FirstVehicle() const
{
    return vehicles.front();
}

void TrafficLight::Update()
{
    if (green)
    {
        if (timerGreen > 0)
        {
            timerGreen --;
        }
        else
        {
            SwitchLight();
            timerGreen = countdown+recalcCountdown;
        }
    }
    else
    {
        if (timerRed > 0)
        {
            timerRed --;
        }
        else
        {
            SwitchLight();
            timerRed = countdown-recalcCountdown;
        }   
    }
}

void TrafficLight::Modify(int quantity)
{
    if ((quantity+recalcCountdown)<=countdown || (quantity+recalcCountdown)>=(countdown*-1))
      recalcCountdown+=quantity;
    
        
}

size_t TrafficLight::GetVehiculoLocation(const shared_ptr<Vehicle>& v) const
{
	int i=0;
	auto thisVehicle = find_if(vehicles.begin(), vehicles.end(),
				 		[&v,&i](const shared_ptr<Vehicle>& it)
         				{
         					i++;
         					if(it!=nullptr)
         					return v->GetLicencePlate()==it->GetLicencePlate();

				        });

	if (thisVehicle==vehicles.end())
    {
        cout<<"auto no encontrado"<<endl;
		return 0;
    }
	return i;
}

size_t TrafficLight::GetNode()const
{
    return node;
}

size_t TrafficLight::GetTimer() const
{
    if (green)
        return timerGreen;
    else
        return timerRed;
}
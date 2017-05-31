#include "../include/Vehicle.h"
#include "../include/TrafficLight.h"

Vehicle::Vehicle(size_t licencePlate, size_t speed, vector <shared_ptr<TrafficLight>> route)
:licencePlate{licencePlate},speed{speed},route{route} 
{
	location=route[0];
	if (!location->EnQueue(make_shared<Vehicle>(*this)))
		throw ("No Push");
}

void Vehicle::Move(function<void(shared_ptr<Vehicle>)> func)
{
	if(state)
	{
		double bufferspeed = speed;
		arrivalTime++;
		auto at= location->GetVehiculoLocation(make_shared<Vehicle>(*this));
		if (at<=speed)
		{
			if (location->GetLight())
			{
				indice++;
				if (route.at(indice)->EnQueue(make_shared<Vehicle>(*this),(speed-at))==1)
					{
					 location->Clean(at);
					 location=route.at(indice);
					 speed-=at;
					}
				else
					{
						indice--;
						speed=at-1;
						if(location->EnQueue(make_shared<Vehicle>(*this), location->GetMaxVQueue()-at+speed))
					 		location->Clean(at);
					 	//else
					 		//cout<<"no se movio en nuestro semaforo en verde"<<endl;
					}
			}
			else
			{
				speed=at-1;
				if(location->EnQueue(make_shared<Vehicle>(*this), location->GetMaxVQueue()-at+speed))
			 		location->Clean(at);
			 	//else
			 		//cout<<"no se movio en nuestro semaforo en rojo"<<endl;
			 
			}

		}

		else
		{
		 	if(location->EnQueue(make_shared<Vehicle>(*this), location->GetMaxVQueue()-at+speed))
		 		location->Clean(at);
		}
	speed=bufferspeed;
		if  (location==route.back())
		{
			state=false;
		}
	}
	else
	{
		func(make_shared<Vehicle>(*this));
		// location->Clean(at)
	}
}

size_t Vehicle::GetLicencePlate() const
{
	return licencePlate;
}

shared_ptr<TrafficLight> Vehicle::GetLocation() const
{
	return location;
}

size_t Vehicle::GetArrivalTime()const
{
	return arrivalTime;
}
double Vehicle::getspeed()
{
	return speed;
}

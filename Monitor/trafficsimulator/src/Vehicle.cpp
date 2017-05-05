#include "../include/Vehicle.h"

Vehicle::Vehicle(double speed,
			vector <pair<shared_ptr<TrafficLight>, bool>> route,
			size_t startTime)
:speed{speed}, route{route}, startTime{startTime}, ubication{route[0].first}
{
	lincencePlate++;
}

void Vehicle::Move()
{
	arrivalTime++;
	/*size_t ligthPosition=ubication->MoveVehicle(this);
	if (!ligthPosition)
		{
			auto it = find_if( route.begin(), route.end(),
             [](const pair<shared_ptr<TrafficLight>, bool>& element)
             {
             	return element.first == ubication;
             });
			if (it==ruote.end())
				throw "Route not found";
			it->second=true;
			it++;
			ubication=it->firsr;
		}*/
}

shared_ptr<TrafficLight> Vehicle::GetLocation() const
{
	return ubication;
}

size_t Vehicle::GetArrivalTime()const
{
	return arrivalTime;
}

/*
Vehicle::~Vehicle()
{

}
*/

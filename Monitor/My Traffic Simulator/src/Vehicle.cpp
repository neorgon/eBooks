#include "../include/Vehicle.h"

Vehicle::Vehicle(double speed,
			vector <pair<shared_ptr<TrafficLight>, bool>> route,
			size_t startTime)
:speed{speed}, route{route}, startTime{startTime}, ubication{route[0].first}
{
	lincencePlate++;
	if (!ubication->EnQueue(*this))
		throw "TrafficLight Full";
}

void Vehicle::Move()
{
	arrivalTime++;
	if(ubication->FirstVehicle().get()==this)
		if (route.at(indice++).first->EnQueue(*this))
		{
			ubication=route.at(indice).first;
		}


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

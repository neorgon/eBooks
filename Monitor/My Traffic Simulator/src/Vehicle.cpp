#include "../include/Vehicle.h"

#include "../include/TrafficLight.h"
#include "../include/Map.h"

size_t Vehicle::licencePlate=100;

Vehicle::Vehicle(double speed, pair<size_t,shared_ptr<TrafficLight>> origen,
			pair<size_t,shared_ptr<TrafficLight>> destino, shared_ptr<Map> map/*,
			size_t startTime*/)
:speed{speed}, /*startTime{startTime},*/ ubication{origen.second}
{
	licencePlate++;
	//if (!ubication->EnQueue(*this))
	//	return;
	//pedir cambio de vector;
	vector<int> v = map->createRoute((int)origen.first,(int)destino.first);
	//hardcore
	shared_ptr<TrafficLight> t=make_shared<TrafficLight>(1,1,2,2,true);
	for (auto& i: v)
	{
		route.push_back(make_pair((size_t)i,t));

	}
	

}

void Vehicle::Move()
{
	arrivalTime++;
		if(ubication->FirstVehicle().get()==this) 
			if (route.at(indice++).second->EnQueue(*this))
			{
				ubication=route.at(indice).second;
			}
		//if(ubication==route.back().first);
			//boos->RegisterVehicle(this); 	
	for (auto& i: route)
	{
		cout<<i.first<<i.second->GetTLID()<<licencePlate<<endl;
	}
	

}

size_t Vehicle::GetLicencePlate() const
{
	return licencePlate;
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

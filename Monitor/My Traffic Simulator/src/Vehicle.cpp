#include "../include/Vehicle.h"

#include "../include/TrafficLight.h"
#include "../include/Map.h"

Vehicle::Vehicle(size_t licencePlate, double speed,const pair<size_t,shared_ptr<TrafficLight>>& origin,
			const pair<size_t,shared_ptr<TrafficLight>>& destiny,const shared_ptr<Map>& map/*,
			size_t startTime*/)
:licencePlate{licencePlate},speed{speed} /*startTime{startTime},*/ 
{ 	
	if (origin.second==nullptr)
		throw;
	ubication=origin.second;
	if (!ubication->EnQueue(make_shared<Vehicle>(*this)))
		cout<<"error no push"<<endl;
	cout<<"AN: "<<ubication->GetVehiculoLocation(make_shared<Vehicle>(*this))<<endl;
	//cout<<" Auto indice n: "<<ubication->GetVehiculoLocation(make_shared<Vehicle>(*this))<<endl;
	//pedir cambio de vector;
	vector<int> v = map->createRoute((int)origin.first,(int)destiny.first);
	//hardcore
	//auto mymapa=map->get_mapTLight();
		for (auto& i: v)
	{
		route.push_back(make_pair((size_t)i,map->get_mapTLight()[i][0]));

	}
	
	

}

void Vehicle::Move()
{
	if(state)
	{
		double bufferspped = speed;
	arrivalTime++;
	auto at=ubication->GetVehiculoLocation(make_shared<Vehicle>(*this));
	//verificar luz verde con velocidad mayor

	if (at<=speed)
	{   
		if(ubication->GetLight())
		{
			indice++;
			if (route.at(indice).second->EnQueue(make_shared<Vehicle>(*this),(speed-at))==1)
				{
					ubication->Clean(at);
					ubication=route.at(indice).second;
					cout<<"ubicacion nueva: "<<ubication->GetVehiculoLocation(make_shared<Vehicle>(*this))<<endl;
				}
			else
				{
					indice--;
					speed=at-1;
					ubication->Clean(at);
					ubication->EnQueue(make_shared<Vehicle>(*this),(ubication->GetMaxVQueue()-at+speed));
				}
		}
		else
			{
				speed=at-1;
				ubication->Clean(at);
				ubication->EnQueue(make_shared<Vehicle>(*this),(ubication->GetMaxVQueue()-at+speed));
				}

	}
	else if(at>speed)
	{
		ubication->Clean(at);
		ubication->EnQueue(make_shared<Vehicle>(*this),(ubication->GetMaxVQueue()-at+speed));
		cout<<ubication->GetVehiculoLocation(make_shared<Vehicle>(*this))<<endl;
		
	}

	//	if(ubication->FirstVehicle().get()->GetLicencePlate()==this->GetLicencePlate()
	//		&& ubication->GetLight()) 
	//		if (route.at(indice++).second->EnQueue(make_shared<Vehicle>(*this)),5)
	//		{
	//			ubication=route.at(indice++).second;
	//		}
		//if(ubication==route.back().first);
			//boos->RegisterVehicle(this); 	
			//cout<<"auno numero: "<<ubication->GetVehiculoLocation(make_shared<Vehicle>(*this))<<endl;
		cout<<endl;
		cout<<"nodo inicio id semaforo :"<<ubication->GetTLID()
		<<" auto n: "<<ubication->CountVehicles()<<endl;
		for (auto& i: route)
		{
			cout<<"nodo: "<<i.first<<" id semaforo :"<<i.second->GetTLID()
			<<" auto n: "<<i.second->CountVehicles()<<endl;
		
		}
	
		

	speed=bufferspped;
	if (ubication==route.back().second)
		{
			state=false;
		}
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
double Vehicle::getspeed()
{return speed;}
/*
Vehicle::~Vehicle()
{

}
*/

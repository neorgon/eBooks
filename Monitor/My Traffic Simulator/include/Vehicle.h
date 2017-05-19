#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <functional>

#include "../include/TrafficLight.h"
#include "../include/Map.h"

using namespace std;

class TrafficLight;
class Map;


class Vehicle
{

	size_t licencePlate;
	double speed;
	vector <pair<size_t,shared_ptr<TrafficLight>>> route;
	//size_t startTime;
	shared_ptr<TrafficLight> ubication;
	size_t arrivalTime=0;
	size_t indice=0;
	bool state=true;
public:
	Vehicle(size_t licencePlate,double speed,const pair<size_t,shared_ptr<TrafficLight>>& origin,
			const pair<size_t,shared_ptr<TrafficLight>>& destiny,const shared_ptr<Map>& map/*,
			size_t startTime*/);
	void Move(function<void(shared_ptr<Vehicle>)> func);
	size_t GetLicencePlate() const;
	double getspeed();
	shared_ptr<TrafficLight> GetLocation() const;
	size_t GetArrivalTime()  const;
	//~Vehicle();
};

#endif // VEHICLE_H

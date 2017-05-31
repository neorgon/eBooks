#ifndef VEHICLE_H
#define VEHICLE_H

#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <functional>

using namespace std;

class TrafficLight;

class Vehicle
{

	size_t licencePlate;
	size_t speed;
	vector <shared_ptr<TrafficLight>> route;
	shared_ptr<TrafficLight> location ;
	size_t arrivalTime=0;
	size_t indice=0;
	bool state=true;
public:
	Vehicle(size_t licencePlate, size_t speed,vector <shared_ptr<TrafficLight>> route);
	void Move(function<void(shared_ptr<Vehicle>)> func);
	size_t GetLicencePlate() const;
	double getspeed();
	shared_ptr<TrafficLight> GetLocation() const;
	size_t GetArrivalTime()  const;
};

#endif // VEHICLE_H

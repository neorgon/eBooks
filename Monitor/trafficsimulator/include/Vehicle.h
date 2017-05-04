#ifndef VEHICLE_H
#define VEHICLE_H
#include <vector>
#include <memory>
#include <utility>

#include "TrafficLight.h"

using namespace std;

class Vehicle
{
	size_t lincencePlate;
	double speed=1;
	vector <pair<shared_ptr<TrafficLight>, bool>> route;
	size_t startTime;
	shared_ptr<TrafficLight> ubication;
	size_t arrivalTime=0;
public:
	Vehicle(double speed,
			vector <pair<shared_ptr<TrafficLight>, bool>> route,
			size_t startTime);
	void Move();
	shared_ptr<TrafficLight> GetLocation() const;
	size_t GetArrivalTime()  const;
	~Vehicle();
};

#endif // VEHICLE_H
#ifndef VEHICLE_H
#define VEHICLE_H


#include <vector>
#include <memory>
#include <utility>
#include <iostream>



using namespace std;

class TrafficLight;
class Map;


class Vehicle
{
	
	static size_t licencePlate;
	double speed;
	vector <pair<size_t,shared_ptr<TrafficLight>>> route;
	//size_t startTime;
	shared_ptr<TrafficLight> ubication;
	size_t arrivalTime=0;
	size_t indice=0;
	bool state=true;
public:
	Vehicle(double speed, pair<size_t,shared_ptr<TrafficLight>> origen,
			pair<size_t,shared_ptr<TrafficLight>> destino, shared_ptr<Map> map/*,
			size_t startTime*/);
	void Move();
	size_t GetLicencePlate() const;
	shared_ptr<TrafficLight> GetLocation() const;
	size_t GetArrivalTime()  const;
	//~Vehicle();
};

#endif // VEHICLE_H

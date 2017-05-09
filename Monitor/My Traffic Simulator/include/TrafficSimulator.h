#ifndef TRAFFICSIMULATOR_H
#define TRAFFICSIMULATOR_H

#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <iostream>
#include <ctime>
#include <math.h>
#include <Map.h>

using namespace std;

class TrafficSimulator
{
	int trafficLightsQuantity;
	int vehicleQuantity;
	int vehicleStartPoint;
	int vehicleEndPoint;
	Map* mapSimulator;
	map<shared_ptr<TrafficLight>,vector<shared_ptr<TrafficLight>>> mapTraffictLight;
	//vector<Vehicle*> vehicles;

	public:
	TrafficSimulator();
	TrafficSimulator(int trafficLightsQuantity);
	~TrafficSimulator();
	void BuildMap(int trafficLightsQuantity);
	void StartSimulation();
	void InitializeVehicles();
	//Vehicle* CreateVehicles(int vehicleQuantity, int vehicleStartPointX, int vehicleStartPointY);
	int RandomInteger(int lowest, int highest);

};

#endif // TRAFFICSIMULATOR_H

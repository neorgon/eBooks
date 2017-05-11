#ifndef TRAFFICSIMULATOR_H
#define TRAFFICSIMULATOR_H

#include "Map.h"
#include "Vehicle.h"
//#include "../include/Vehicle.h"
//#include "../include/Map.h"
#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <iostream>
#include <ctime>
#include <math.h>
#include <exception>

//using namespace std;

class TrafficSimulator
{
	int trafficLightsQuantity;
	int vehicleQuantity;
	int vehicleStartPoint;
	int vehicleEndPoint;
	Map* mapSimulator;
	map<int,vector<int>> mapTraffictLight;
	//vector<Vehicle*> vehicles;

	public:
	TrafficSimulator();
	TrafficSimulator(int trafficLightsQuantity);
	~TrafficSimulator();
	void BuildMap(int trafficLightsQuantity);
	void StartSimulation();
	void InitializeVehicles();
	//Vehicle* CreateVehicles(vector <pair<shared_ptr<TrafficLight>, bool>> route, int vehicleStartPointX, int vehicleStartPointY);
	int RandomInteger(int lowest, int highest);

};

#endif // TRAFFICSIMULATOR_H


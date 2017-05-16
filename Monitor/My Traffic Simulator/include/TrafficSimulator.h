#ifndef TRAFFICSIMULATOR_H
#define TRAFFICSIMULATOR_H

#include "Simulation.h"
#include "Vehicle.h"
#include "TrafficLight.h"
#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <iostream>
#include <ctime>
#include <math.h>
#include <exception>
#include <conio.h>
//#include <stdio.h>
#include <iomanip>
#include <windows.h>
#include <map>

#define WINDOWS 1
#define TRAFFICLIGHTSFROMSTATISTICS 2227
#define VEHICLESFROMSTATISTICS 540063

using namespace std;
class Map;
class TrafficSimulator
{
	int trafficLightsQuantity;

	size_t vehicleStartPoint;
	size_t vehicleEndPoint;
	map<int,vector<shared_ptr<TrafficLight>>> mapAux;
	vector<shared_ptr<Vehicle>> vehicles;
	shared_ptr<Vehicle> vehicle;

	public:
	TrafficSimulator();
	~TrafficSimulator();
	int RandomInteger(int lowest, int highest);
	Simulation* BuildSimulation(shared_ptr<Map> map,string name,size_t vehicleQuantity,
		size_t speedMin,size_t speedMax);
    void StartSimulation(Simulation *simulation, int cycles = 0);
    void StartSimulation(string simulationName, int cycles = 0);
    void ClearScreen();

};

#endif // TRAFFICSIMULATOR_H


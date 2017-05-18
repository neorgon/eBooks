#ifndef TRAFFICSIMULATOR_H
#define TRAFFICSIMULATOR_H

#include "Simulation.h"
#include "Map.h"
#include "Vehicle.h"
#include "TrafficLight.h"
#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <iostream>
#include <math.h>
#include <exception>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <map>
#include <typeinfo>
#include <stdlib.h>
#include <time.h>

#define WINDOWS 1

using namespace std;
class Map;
class TrafficSimulator
{
	int trafficLightsQuantity;
	size_t vehicleStartPoint;
	size_t vehicleEndPoint;
	map<int,vector<shared_ptr<TrafficLight>>> trafficLightsSim;
	vector<shared_ptr<Vehicle>> vehicles;
	shared_ptr<Vehicle> vehicle;
	shared_ptr<Map> mapSim;
	Simulation* simulationTraffic;
	vector<shared_ptr<Simulation>> simulations;

	public:
	TrafficSimulator();
	~TrafficSimulator();
	int RandomInteger(int lowest, int highest);
	Simulation* BuildSimulation(shared_ptr<Map> map,string name,size_t vehicleQuantity,
	size_t speedMin,size_t speedMax);
    bool ValidateSimulation(string name);
    bool ValidateSimulation(Simulation *simulation);
    void StartLoopSim(int cycles = 0);
    void StartSimulation(Simulation *simulation, int cycles = 0);
    void StartSimulation(string simulationName, int cycles = 0);
    void ClearScreen();
    vector<int> convertCoordinates(int x);

};

#endif // TRAFFICSIMULATOR_H


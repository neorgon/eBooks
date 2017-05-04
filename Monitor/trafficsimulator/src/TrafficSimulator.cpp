/*
 * Source Singapore Statistics
 * https://www.lta.gov.sg/content/dam/ltaweb/corp/PublicationsResearch/files/FactsandFigures/Statistics%20in%20Brief%202014.pdf
 * according to the statistics in 2013
 * there are 2227 traffic lights in the city
 * and 540063 cars
 * this will be used to the simulation and create the quantity of cars according to the traffic lights
 * annual mileage 17800
 * this will be for the frecuency of the cars
 * */

#include "../include/TrafficSimulator.h"

TrafficSimulator::TrafficSimulator():TrafficSimulator{2}
{
}

TrafficSimulator::TrafficSimulator(int trafficLightsQuantity)
	:trafficLightsQuantity(trafficLightsQuantity)
{
	srand((unsigned)time(0));
	BuildMap(trafficLightsQuantity);
}

TrafficSimulator::~TrafficSimulator()
{
}

void TrafficSimulator::BuildMap(int trafficLightsQuantity)
{
    mapSimulator = new Map();
    mapTraffictLight = mapSimulator->createMap(trafficLightsQuantity);
    mapSimulator->show();

}

void TrafficSimulator::StartSimulation()
{

}

void TrafficSimulator::InitializeVehicles()
{
    vehicleQuantity = (int)(trafficLightsQuantity * 540063 / 2227 + 0.5);

    vector <pair<shared_ptr<TrafficLight>, bool>> route {};

	for ( int i = 0; i < vehicleQuantity ; i++)
	{
		vehicleStartPoint = RandomInteger(1,trafficLightsQuantity);
		vehicleEndPoint = RandomInteger(1,trafficLightsQuantity);

		//vehicles.push_back(CreateVehicles( route, vehicleStartPoint, vehicleEndPoint));

	}
}
/*
Vehicle* TrafficSimulator::CreateVehicles( vector <pair<shared_ptr<TrafficLight>, bool>> route, int vehicleStartPoint, int vehicleEndPoint)
{
	Vehicle* v = nullptr;

	//v = new Vehicle(vehicleStartPoint,vehicleEndPoint);
	v = new Vehicle((double)RandomInteger(1,10), route, (size_t)RandomInteger(1,24));
	return v;
}
*/
int TrafficSimulator::RandomInteger(int lowest, int highest)
{

    int random_integer;
    int range=(highest-lowest)+1;
    random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0));
	return random_integer;
}


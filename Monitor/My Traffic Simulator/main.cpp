#include "../include/TrafficSimulator.h"
#include "../include/WindowsConsole.h"

using namespace std;

int main()
{
    size_t vehicleQuantity=3;
	size_t speedMin=1;
	size_t speedMax=2;
	size_t timeTrafficLight=2;
	size_t Vehicles=10;
	TrafficSimulator* a = new TrafficSimulator();
	shared_ptr<Map> mapa=make_shared<Map>(5, timeTrafficLight, Vehicles);
	a->BuildSimulation(mapa, "primeraSImulacion", vehicleQuantity, speedMin, speedMax);
    a->StartSimulation("primeraSImulacion", 50);

    return 0;
}

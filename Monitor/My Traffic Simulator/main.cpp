#include "../include/TrafficSimulator.h"
#include "../include/WindowsConsole.h"

using namespace std;

int main()
{
<<<<<<< Updated upstream
    size_t vehicleQuantity=100;
	size_t speedMin=1;
	size_t speedMax=2;
	size_t timeTrafficLight=2;
	size_t Vehicles=10;
	TrafficSimulator* a = new TrafficSimulator();
	shared_ptr<Map> mapa=make_shared<Map>(4,timeTrafficLight,Vehicles);
	a->BuildSimulation(mapa,"primeraSImulacion", vehicleQuantity, speedMin, speedMax);
    a->StartSimulation("primeraSImulacion",20);
=======
	Map mapa = Map(6, 2, 10);

	WindowsConsole wc(600, 800, "Traffic Simulator", 7, 4);
	//wc.PrintCity();
	//wc.ClearScreen();
	auto TLs = mapa.GetMapTrafficLight();
	wc.PrintMap(TLs, mapa.getSizeMap());

    /*wc.SetColor(15);
    wc.GotoXY(11, 4);
    cout << "15";*/

    getchar();

    for (auto t : TLs)
    {
        t.second[0]->SwitchLight();
        t.second[1]->SwitchLight();
    }

    wc.UpdateMap(TLs);
    getchar();
>>>>>>> Stashed changes

    return 0;
}

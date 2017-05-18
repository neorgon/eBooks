
#include "include/TrafficSimulator.h"
//#include "TrafficSimulator.h"
#include <iostream>
#include <memory>
#include <utility>


#include "include/Vehicle.h"
#include "include/Map.h"
#include "include/TrafficSimulator.h"
#include "include/TrafficLight.h"

using namespace std;

using namespace std;
int main()
{

	/*Map* m = new Map(4,10,20);
	//m.InitializeTrafficLight(10,20);
	auto route=m->createRoute(1,10);



	m->showMap();
	m->show();*/
	size_t vehicleQuantity=100;
	size_t speedMin=1;
	size_t speedMax=2;
	size_t timeTrafficLight=2;
	size_t Vehicles=10;
	TrafficSimulator* a = new TrafficSimulator();
	shared_ptr<Map> mapa=make_shared<Map>(6,timeTrafficLight,Vehicles);
	//mapa->show();
	shared_ptr<Simulation> s=a->BuildSimulation(mapa,"primera", vehicleQuantity, speedMin, speedMax);
	//mapa->show();
	//a->StartSimulation("hola",4);
	//mapa->show();
    //cout<<s->getName()<<"NOMBRE SI\n";

    //a->StartSimulation(s,20);


    //TrafficSimulator* b = new TrafficSimulator();
	//shared_ptr<Map> mapa2=make_shared<Map>(4,timeTrafficLight,Vehicles);
	//mapa->show();
	//Simulation* s2=b->BuildSimulation(mapa2,"segunda", vehicleQuantity, speedMin, speedMax);
	//mapa->show();
	//a->StartSimulation("hola",4);
	//mapa->show();
    //cout<<s->getName()<<"NOMBRE SI\n";

    //a->StartSimulation(s2,20);




}
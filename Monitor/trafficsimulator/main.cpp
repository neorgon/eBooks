
//#include "include/TrafficSimulator.h"
//#include "TrafficSimulator.h"
#include <iostream>
#include <memory>
#include <utility>


//#include "include/Vehicle.h"
#include "include/Map.h"
//#include "include/TrafficSimulator.h"
#include "include/TrafficLight.h"

using namespace std;

using namespace std;
int main()
{

	Map* m = new Map(3, 10, 20);
	auto mapa = m->GetMapTrafficLight();

	/*
	auto aux = mapa.find(26);
	auto ini = aux->second[0]; 
	auto aux2 = mapa.find(2);
	auto fin = aux2->second[0];
	auto route=m->CreateRoute(ini,fin);

	aux = mapa.find(26);
	ini = aux->second[0]; 
	aux2 = mapa.find(8);
	fin = aux2->second[1];
	auto route1=m->CreateRoute(ini,fin);

	aux = mapa.find(32);
	ini = aux->second[0]; 
	aux2 = mapa.find(8);
	fin = aux2->second[1];
	auto route2=m->CreateRoute(ini,fin);


	aux = mapa.find(20);
	ini = aux->second[0]; 
	aux2 = mapa.find(14);
	fin = aux2->second[1];
	auto route3=m->CreateRoute(ini,fin);
	*/

	//m->showMap();
	m->show();

}

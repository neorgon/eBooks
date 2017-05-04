#ifndef MAP_H
#define MAP_H
#include "TrafficLight.h"
#include <map>
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

class Map
{

    map<shared_ptr<TrafficLight>,vector<shared_ptr<TrafficLight>>> mapTraffictLigth;
    //map<Vehicle,vector<int>> routes;
    vector<string> places;
    vector<size_t> adyacent;

    public:

 		Map();
        map<shared_ptr<TrafficLight>,vector<shared_ptr<TrafficLight>>> createMap(int sizeMap);
        void show();
        virtual ~Map();

};

#endif // MAP_H

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

    map<int,vector<int>> mapTraffictLigth;
    vector<int> adyacent;

    public:

 		Map();
        map<int,vector<int>> createMap(int sizeMap);
        void show();
        virtual ~Map();

};

#endif // MAP_H

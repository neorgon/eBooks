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
    int sizeMap;
    map<int,vector<int>> mapTraffictLigth;
    vector<int> adyacent;

    public:
        map<int,vector<int>> createMap(int sm);
        void show();
};

#endif // MAP_H

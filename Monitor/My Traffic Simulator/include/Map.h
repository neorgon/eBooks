#ifndef MAP_H
#define MAP_H
#include "TrafficLight.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <deque>
#include <stack>
#include <map>
using namespace std;

class Map
{
    map<int,vector<int>> mapTrafficLight;
    vector<int> adyacent;

    vector<TrafficLight*> VectorTrafictlight;
    map<int,vector<TrafficLight*>> mapLight;

    public:

 		Map();
        map<int,vector<TrafficLight*>> createMap(int sizeMap);
        vector<int> createRoute(int origin,int destination);
        map<int,vector<TrafficLight*>> get_mapTLight();        
    	bool findStack(stack<int> auxStack,int value);
    	bool findQueue(deque<int>& vertices,int value);
        void show();
        void showMap();
        virtual ~Map();

};

#endif // MAP_H

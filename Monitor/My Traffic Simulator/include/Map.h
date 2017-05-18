#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <memory>
#include <deque>
#include <stack>
#include <map>
#include <Direction.h>
#include <TrafficLight.h>

using namespace std;

class Map
{
    int sizeMap;
    map<int, vector<int>> mapRoutes;
    map<int, vector<shared_ptr<TrafficLight>>> mapTrafficLight;

    public:
 		Map(int sizeMap, size_t timeTrafficLight, size_t maxVehicle);
        vector<int> createRoute(int origin, int destination);
        map<int, vector<shared_ptr<TrafficLight>>> GetMapTrafficLight() const;
    	bool findStack(stack<int> auxStack, int value);
    	bool findQueue(deque<int>& vertices, int value);
        void show();
        void showMap();
};

#endif // MAP_H

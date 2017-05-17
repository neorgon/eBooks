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
    map<int,vector<int>> mapTrafficLight;
    vector<int> adyacent;

    vector<shared_ptr<TrafficLight>> VectorTrafictlight;
    map<int,vector<shared_ptr<TrafficLight>>> mapLight;

    public:
 		Map(int sizeMap , size_t timeTrafficLight , size_t maxVehicle);
        // void createMap(int sizeMap);
        //void InitializeTrafficLight(size_t timeTrafficLight,size_t maxVehicle);
        vector<int> createRoute(int origin,int destination);
        map<int,vector<shared_ptr<TrafficLight>>> get_mapTLight();
    	bool findStack(stack<int> auxStack,int value);
    	bool findQueue(deque<int>& vertices,int value);
         void show();
        void showMap();
        virtual ~Map();

};

#endif // MAP_H

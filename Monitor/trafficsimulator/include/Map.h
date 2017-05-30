#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <memory>
#include <deque>
#include <stack>
#include <map>
#include <algorithm>

#include "../include/Direction.h"

using namespace std;

class TrafficLight;
class Map
{
    int sizeMap;
    map<int, vector<int>> mapRoutes;
    map<int, vector<shared_ptr<TrafficLight>>> mapTrafficLight;
    map<shared_ptr<TrafficLight>,vector<shared_ptr<TrafficLight>>> adjacentTrafficLight;

    public:
        Map(int sizeMap, size_t timeTrafficLight, size_t maxVehicle);
        vector<shared_ptr<TrafficLight>> CreateRoute(const size_t &origin, const size_t &destination);
        int ReviewRoute(const int &origin, const int &destination);
        vector<shared_ptr<TrafficLight>> GenerateRoute(const int &caseRoute,const int &origin, const int &destination);
        void StoreRoute(const size_t &ini , const size_t &fin , Direction orientation, vector<shared_ptr<TrafficLight>> &route);
        map<int, vector<shared_ptr<TrafficLight>>> GetMapTrafficLight() const;
        void CreateAdjacentTrafficLight();
        map<shared_ptr<TrafficLight>,vector<shared_ptr<TrafficLight>>> GetAdjacentTrafficLight();
        vector<size_t> ConvertCoordinates(const int &x) ;
        int GetMapSize() const;
        void showMap();
        void show();
        
};

#endif // MAP_H

#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H
#include <string>
#include <vector>
using namespace std;
class TrafficLight
{    
	  size_t trafficLightld;
    bool state;
		vector<string> places;
    size_t interval;
		size_t stack;

    public:
        TrafficLight(size_t trafficLightld,bool state,vector<string> places,size_t interval,size_t stack);
        bool getState();
        size_t getId();
        void setState(bool newState);
        //void addQueue(Vehicle auxCar);
        void reduceQueue();
        virtual ~TrafficLight();

};

#endif // TRAFFICLIGHT_H

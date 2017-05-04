#include "../include/TrafficLight.h"

TrafficLight::TrafficLight(size_t trafficLightld,bool state,vector<string> places,size_t interval,size_t stack):trafficLightld{trafficLightld},state{state},places{places},interval{interval},stack{stack}
{

}
bool TrafficLight::getState()
{
    return state;
}
size_t TrafficLight::getId()
{
    return trafficLightld;
}
void TrafficLight::setState(bool newState)
{
    state=newState;
}
/*void TrafficLight::addQueue(Vehicle aux)
{

}*/
void TrafficLight::reduceQueue()
{

}

TrafficLight::~TrafficLight()
{
    //dtor
}

#ifndef SIMULATIONRESULT_H
#define SIMULATIONRESULT_H

#include <map>
#include <vector>

using namespace std;

class SimulationResult
{
    map<int,vector<int>> resultTrafficLight;
    map<int,int> resutlVehicle;

    public:
    SimulationResult();
    void AddTrafficCylce(int node, int vehiclesQuantity, int state, int timerState);
    ~SimulationResult();

};

#endif // SIMULATIONRESULT_H

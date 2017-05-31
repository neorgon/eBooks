#include "../include/SimulationResult.h"

SimulationResult::SimulationResult()
{
}

void SimulationResult::AddTrafficCylce(int node, int vehiclesQuantity, int state, int timerState)
{
	resultTrafficLight[node] = vector<int> {vehiclesQuantity, state, timerState};
}

void SimulationResult::AddValuesForANN(vector<int> values)
{
    valuesANN.push_back(values);
}

void SimulationResult::SerializeJSon(int node, int vehiclesQuantity, int state, int timerState)
{

}

SimulationResult::~SimulationResult()
{
}

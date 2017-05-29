#include "../include/SimulationResult.h"

SimulationResult::SimulationResult()
{
}

void SimulationResult::AddTrafficCylce(int node, int vehiclesQuantity, int state, int timerState)
{
	resultTrafficLight[node] = vector<int> {vehiclesQuantity, state, timerState};
}

SimulationResult::~SimulationResult()
{
}

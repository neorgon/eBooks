#include "../include/TrafficSimulator.h"
#include <exception>

using my_point = pair<size_t,shared_ptr<TrafficLight>>;

TrafficSimulator::TrafficSimulator()
{
    srand((unsigned)time(0));
}

TrafficSimulator::~TrafficSimulator()
{
}

int TrafficSimulator::RandomInteger(int lowest, int highest)
{

    int random_integer;
    int range=(highest-lowest)+1;
    random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0));
    return random_integer;
}

void TrafficSimulator::BuildSimulation(shared_ptr<Map>& mapSimulation,string name,size_t vehicleQuantity,size_t speedMin,size_t speedMax)
{
    vector<shared_ptr<Vehicle>> vehicles;
    int mapSize=mapSimulation->GetMapSize();

    for ( size_t i = 1,loops=0; i <= vehicleQuantity ; i++, loops++)
    {
        vector<size_t> points ;
        if(mapSize%2 == 0)
        {
            points= GetStartEndPoints ( mapSimulation, vehicleQuantity ,i);
        }
        else
        {
            do
            {
                points = GetStartEndPoints ( mapSimulation, vehicleQuantity ,i);
            }
            while( points[0] == mapSize || points[1] == mapSize*(mapSize-1) + 1  );
        }

        cout<<points[0]<<"---"<<i<<"----"<<points[1]<<"RUTA\n";
        vector<shared_ptr<TrafficLight>> routes=mapSimulation->CreateRoute(points[0],points[1]);
        for(auto& j: routes)
        {
            if(j==nullptr)
            {
                cerr<<"error ruta"<<endl;
            }
        }
        try
        {
            vehicles.push_back(make_shared<Vehicle>(i,(double)RandomInteger(speedMin,speedMax),routes));
        }
        catch (const char* e)
        {
            i--;
        }
        if (loops>(vehicleQuantity*3))
            throw ("Number of vehicles exceeded");
    }
    simulations[name]=make_shared<Simulation>(mapSimulation,name,vehicles);
}

void TrafficSimulator::StartLoopSim(map<string,shared_ptr<Simulation>>::iterator simulationIterator, int cycles)
{
    SimulationResult results;

    auto vehicles = simulationIterator->second->getVehicles();
    auto mapSim = simulationIterator->second->getMap();
    auto trafficLightsSim = mapSim->GetMapTrafficLight();
    string msg;
    bool loop=false;
    bool cyclesFlag = false;
    if(cycles!=0)
        cyclesFlag = true;

    WindowsConsole wc(500, 960, "Traffic Simulator", 7, 4);
    wc.ClearScreen();
    if(optionVisualization)
        wc.PrintMap(trafficLightsSim, mapSim->GetMapSize());

    while(loop==false)
    {
        if (vehicles.size() == 0)
        {
            loop = true;
            msg = "all cars arrived, simulation ended";
            break;
        }

        for(auto i=0U;i<vehicles.size();i++)
        {
            vehicles[i]->Move(
                [&](shared_ptr<Vehicle> me)
                {
                    shared_ptr<TrafficLight> semaforo = me->GetLocation();
                    size_t posSemaforo=semaforo->GetVehiculoLocation(me);
                    vehicles.erase(vehicles.begin()+i);
                    semaforo->Clean(posSemaforo);
                    i--;
                    return;
                });
        }

        for(auto it=trafficLightsSim.begin(); it!=trafficLightsSim.end(); ++it)
        {
			map<
                shared_ptr<TrafficLight>,
                vector<shared_ptr<TrafficLight>>
            > adjacentTrafficLight = mapSim->GetAdjacentTrafficLight();
			auto firstAdjacentTrafficLightIterator = find_if(
                adjacentTrafficLight.begin(),
                adjacentTrafficLight.end(),
                [&](pair<shared_ptr<TrafficLight>,vector<shared_ptr<TrafficLight>>> me)
                {
                    return (me.first.get() == it->second[0].get());
                });
            auto secondAdjacentTrafficLightIterator = find_if(
                adjacentTrafficLight.begin(),
                adjacentTrafficLight.end(),
                [&](pair<shared_ptr<TrafficLight>,vector<shared_ptr<TrafficLight>>> me)
                {
                    return (me.first.get()==it->second[1].get());
                });
            vector<shared_ptr<TrafficLight>> firstPairAdyacentTF = firstAdjacentTrafficLightIterator->second;
            vector<shared_ptr<TrafficLight>> secondPairAdyacentTF = secondAdjacentTrafficLightIterator->second;
            int adyacentTFCountVehicles1 = FindAdjacentEqualDirectionTrafficLight(firstPairAdyacentTF,it->second[0]);
            int adyacentTFCountVehicles2 = FindAdjacentEqualDirectionTrafficLight(secondPairAdyacentTF,it->second[1]);

            vector<int> aux = {
                (int)(it->second[0]->CountVehicles()),
                adyacentTFCountVehicles1,
                (int)(it->second[1]->CountVehicles()),
                adyacentTFCountVehicles2,
            };
            results.AddValuesForANN(aux);

            it->second[0]->Update();
            it->second[1]->Update();
        }

        if (cyclesFlag)
        {
			if(cycles==0)
            {
				loop = true;
                msg = "number of cycles reached, simulation ended";
                break;
            }
            cycles--;
         }

         if(optionVisualization)
         {
            wc.UpdateMap(trafficLightsSim);
            wc.GotoXY(1, 35);
            Sleep(1500);
         }
    }
    wc.GotoXY(1, 35);
    resultsMap.insert(make_pair(simulationIterator->second->getName(), make_shared<SimulationResult>(results)));
    cout<<msg<<endl;
}

void TrafficSimulator::StartSimulation(string simulationName, int cycles)
{
    char option;
    map<string,shared_ptr<Simulation>>::iterator it;
    it = simulations.find(simulationName);
    if (it == simulations.end())
    {
        cout<<"not a valid simulation, please give the right simulation for this traffic simulator";
    }
    else
    {
        StartLoopSim(it, cycles);
	}
}

vector<size_t> TrafficSimulator::GetStartEndPoints(shared_ptr<Map>& mapSimulation,size_t vehicleQuantity,size_t id)
{
    vector<size_t> XYStartPoint;
    vector<size_t> XYEndPoint;
    int resStartPointX;
    int resEndPointY;
    size_t vehicleStartPoint;
    size_t vehicleEndPoint;

    vector<size_t> startEndPoints;
    do
    {
        if(id<=vehicleQuantity/2)
        {
            vehicleStartPoint = (size_t) RandomInteger(1,mapSimulation->GetMapTrafficLight().size()/2);
            vehicleEndPoint = (size_t)RandomInteger((mapSimulation->GetMapTrafficLight().size()/2)+1,mapSimulation->GetMapTrafficLight().size());
        }
        else
        {
            vehicleStartPoint = (size_t)RandomInteger((mapSimulation->GetMapTrafficLight().size()/2)+1,mapSimulation->GetMapTrafficLight().size());
            vehicleEndPoint = (size_t)RandomInteger(1,mapSimulation->GetMapTrafficLight().size()/2);
        }

        XYStartPoint = mapSimulation->ConvertCoordinates((int)vehicleStartPoint/*, mapSimulation->getSizeMap()*/);
        XYEndPoint = mapSimulation->ConvertCoordinates((int)vehicleEndPoint/*, mapSimulation->getSizeMap()*/);
        resStartPointX = XYEndPoint[0]-XYStartPoint[0];
        resEndPointY = XYEndPoint[1]-XYStartPoint[1];
    }

    while( (abs(resStartPointX)== 1 && abs(resEndPointY)== 0) || (abs(resStartPointX)== 0 && abs(resEndPointY)== 1));

    startEndPoints.push_back(vehicleStartPoint);
    startEndPoints.push_back(vehicleEndPoint);
    return startEndPoints;

}

int TrafficSimulator::FindAdjacentEqualDirectionTrafficLight(vector<shared_ptr<TrafficLight>>& trafficLightVector, shared_ptr<TrafficLight>& trafficLight)
{
    if(trafficLightVector.size()==2)
    {
        if(trafficLightVector[0]->GetDirection()==trafficLight->GetDirection())
        {
            return trafficLightVector[0]->GetDirection();
        }
        else
        {
            if(trafficLightVector[1]->GetDirection()==trafficLight->GetDirection())
            {
                return trafficLightVector[1]->CountVehicles();
            }

        }
    }
    else
    {
        if(trafficLightVector.size()==1)
        {
            if(trafficLightVector[0]->GetDirection()==trafficLight->GetDirection())
                return trafficLightVector[0]->GetDirection();
        }
    }


}

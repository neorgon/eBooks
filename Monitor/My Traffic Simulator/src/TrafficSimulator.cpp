#include "../include/TrafficSimulator.h"

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



Simulation* TrafficSimulator::BuildSimulation(shared_ptr<Map> map,string name,size_t vehicleQuantity,size_t speedMin,size_t speedMax)
{
    mapSim = map;
    trafficLightsSim = map->GetMapTrafficLight();

    size_t tam = trafficLightsSim.size();

    for ( size_t i = 1; i <= vehicleQuantity ; i++)
    {
        if(i<=vehicleQuantity/2)
        {
            vehicleStartPoint =(size_t) RandomInteger(1,tam/2);
            vehicleEndPoint = (size_t)RandomInteger((tam/2)+1,tam);
        }
        else
        {
            vehicleStartPoint =(size_t)RandomInteger((tam/2)+1,tam);
            vehicleEndPoint = (size_t)RandomInteger(1,tam/2);
        }


        cout<<vehicleStartPoint<<"---"<<i<<"----"<<vehicleEndPoint<<"\n";
        pair<size_t,shared_ptr<TrafficLight>> origin = make_pair((size_t)vehicleStartPoint, trafficLightsSim[vehicleStartPoint][RandomInteger(0,1)]);
        pair<size_t,shared_ptr<TrafficLight>> destination = make_pair((size_t)vehicleEndPoint,trafficLightsSim[vehicleEndPoint][RandomInteger(0,1)]);
        vehicle = make_shared<Vehicle>(i,(double)RandomInteger(speedMin,speedMax),origin, destination, map);
        vehicles.push_back(vehicle);

    }


    simulationTraffic=new Simulation(map,name,vehicles);

    return simulationTraffic;

}

bool TrafficSimulator::ValidateSimulation(Simulation *simulation)
{
    auto name = simulation->getName();
    if (name == simulationTraffic->getName())
        return true;
    return false;
}

bool TrafficSimulator::ValidateSimulation(string name)
{
    if (name == simulationTraffic->getName())
        return true;
    return false;
}

void TrafficSimulator::StartLoopSim(int cycles)
{
    string msg;
    char ch;
    bool loop=false;
    bool cyclesFlag = false;
    if(cycles!=0)
        cyclesFlag = true;

    while(loop==false)
    {
        getch();
        ClearScreen();
        cout<<"press escape to end simulation"<<endl;
        cout<<"press space to continue"<<endl;
        ch=getch();
        if(ch=='\033')
            loop = true;
        else
        {
            if(ch==' ')
            {
                for(auto& i:vehicles)
                {
                    if (vehicles.size() == 0)
                    {
                        loop = true;
                        msg = "all cars arrived, simulation ended";
                        break;
                    }

                    try
                    {
                        i->Move();
                    }
                    catch (...)
                    {
                        cout<<"Simulation ended due to a car arrived";
                    }
                    ClearScreen();
                    cout<<"Simulation: "<<simulationTraffic->getName();
                    mapSim->show();
                    //cout << "\r%"<<i;
                    //mapSimulator->show();
                    //auto vehicleArrived = i->Move();
                    /*if(vehicleArrived)
                    {
                        if (i != auxVehicles.end())
                        auxVehicles.erase(i);
                    }*/
                }

                for(auto it=trafficLightsSim.begin(); it!=trafficLightsSim.end(); ++it)
                {

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
                cout<<cycles;

                    //llamar al visualizador
            }
        }

    }
    cout<<msg<<endl;
}
void TrafficSimulator::StartSimulation(Simulation *simulation, int cycles)
{
    auto forValidation = simulation;
    if(!ValidateSimulation(forValidation))
        cout<<"not a valid simulation, please give the right simulation for this traffic simulator";
    else
        StartLoopSim(cycles);
}

void TrafficSimulator::StartSimulation(string simulationName, int cycles)
{
    auto forValidation = simulationName;
    if(!ValidateSimulation(forValidation))
        cout<<"not a valid simulation, please give the right simulation for this traffic simulator";
    else
        StartLoopSim(cycles);
}

void TrafficSimulator::ClearScreen()
{
  #ifdef WINDOWS
  system("cls");
  #endif
  #ifdef LINUX
  system("clear");
  #endif
}

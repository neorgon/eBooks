#include "../include/TrafficSimulator.h"

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
    map <int, vector<shared_ptr<TrafficLight>>> trafficLightsSim= mapSimulation->GetMapTrafficLight();
    int sizeMap = mapSimulation->getSizeMap();
    size_t tam = trafficLightsSim.size();
    vector<shared_ptr<Vehicle>> vehicles;
    vector<int> XYStartPoint;
    vector<int> XYEndPoint;
    int resStartPointX;
    int resEndPointY;
    size_t vehicleStartPoint;
    size_t vehicleEndPoint;

    for ( size_t i = 1; i <= vehicleQuantity ; i++)
    {
        do
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

            XYStartPoint=ConvertCoordinates((int)vehicleStartPoint, sizeMap);
            XYEndPoint=ConvertCoordinates((int)vehicleEndPoint, sizeMap);
            resStartPointX=XYEndPoint[0]-XYStartPoint[0];
            resEndPointY=XYEndPoint[1]-XYStartPoint[1];
        }

        while( (abs(resStartPointX)== 1 && abs(resEndPointY)== 0) || (abs(resStartPointX)== 0 && abs(resEndPointY)== 1));


        //cout<<vehicleStartPoint<<"---"<<i<<"----"<<vehicleEndPoint<<"RUTA\n";
        my_point origin = make_pair((size_t)vehicleStartPoint, trafficLightsSim[vehicleStartPoint][RandomInteger(0,1)]);
        my_point destination = make_pair((size_t)vehicleEndPoint,trafficLightsSim[vehicleEndPoint][RandomInteger(0,1)]);
        vehicles.push_back(make_shared<Vehicle>(i,(double)RandomInteger(speedMin,speedMax),origin, destination, mapSimulation));

    }


    simulations[name]=make_shared<Simulation>(mapSimulation,name,vehicles);

}

void TrafficSimulator::StartLoopSim(map<string,shared_ptr<Simulation>>::iterator simulationIterator, int cycles)
{
    //cout<<simulationIterator->second->getName();
    auto vehicles = simulationIterator->second->getVehicles();
    auto mapSim = simulationIterator->second->getMap();
    auto trafficLightsSim = mapSim->GetMapTrafficLight();
    string msg;
    char ch;
    bool loop=false;
    bool cyclesFlag = false;
    if(cycles!=0)
        cyclesFlag = true;

    while(loop==false)
    {
        getch();
        WindowsConsole wc(600, 800, "Traffic Simulator", 7, 4);
        wc.ClearScreen();
        //cout<<"press escape to end simulation"<<endl;
        //cout<<"press space to continue"<<endl;

        wc.PrintMap(trafficLightsSim, mapSim->getSizeMap());
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
                        i->Move([&](shared_ptr<Vehicle> me){
                        Data.push_back("auto :"+to_string( me->GetLicencePlate())+"Time : "+to_string( me->GetArrivalTime()));
                        //cout<<me->GetArrivalTime()<<endl;
                        return;
                        });
                    }
                    catch(...)
                    {
                        cout<<"a car arrvied";
                    }

                    //cout<<"Simulation: "<<simulationIterator->second->getName();
                    //mapSim->show();
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
                //cout<<cycles;
                wc.UpdateMap(trafficLightsSim);

            }
        }

    }
    cout<<msg<<endl;
}

void TrafficSimulator::StartSimulation(string simulationName, int cycles)
{
    map<string,shared_ptr<Simulation>>::iterator it;
    it = simulations.find(simulationName);
    if (it == simulations.end())
        cout<<"not a valid simulation, please give the right simulation for this traffic simulator";
    else
        StartLoopSim(it, cycles);
}

vector<int> TrafficSimulator::ConvertCoordinates(int x,int sizeMap)
{
    vector<int> aux;

    aux={0,0};

    aux[0]=(int)ceil((double)x/sizeMap);
    aux[1]= sizeMap-((sizeMap*aux[0])-x);

    return aux;
}

#include "../include/TrafficSimulator.h"
#include "../include/Map.h"
#include <typeinfo>
#include <utility>

TrafficSimulator::TrafficSimulator()
{
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

    mapAux=map->get_mapTLight();

    size_t tam=mapAux.size();

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
        pair<size_t,shared_ptr<TrafficLight>> origin = make_pair((size_t)vehicleStartPoint, mapAux[vehicleStartPoint][RandomInteger(0,1)]);
        pair<size_t,shared_ptr<TrafficLight>> destination = make_pair((size_t)vehicleEndPoint,mapAux[vehicleEndPoint][RandomInteger(0,1)]);
        vehicle = make_shared<Vehicle>(i,(double)RandomInteger(speedMin,speedMax),origin, destination, map);
        vehicles.push_back(vehicle);

    }


    Simulation* simulationTraffic=new Simulation(map,name,vehicles);
    ///move vehicles//
    /*
    for (auto & i: vehicles)
    {
        i->Move();
    }
    */
    return simulationTraffic;

}

void TrafficSimulator::StartSimulation(Simulation *simulation, int cycles)
{
	auto mapSim = simulation->getMap();
	auto trafficLightsSim = mapSim->get_mapTLight();
	auto vehiclesSim = simulation->getVehicles();

	char ch;
    bool loop=false;
    if(cycles==0)
    {
        while(loop==false)
        {
            getchar();
            ClearScreen();
            cout<<"press escape to end simulation"<<endl;
            cout<<"press space to continue"<<endl;
            ch=getch();
            if(ch=='\0')
                loop = true;
            else
            {
                if(ch==' ')
                {
                    for(auto& i:vehiclesSim)
                    {

                        if (vehiclesSim.size() == 0)
                        {
                            loop = true;
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
                        cout<<"Simulation: "<<simulation->getName();
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
                    //llamar al visualizador
                }
            }

        }
        cout<<"simulation terminated"<<endl;
    }
    else
    {
        for(auto i = 0; i<cycles; i++)
        {
            getchar();
            ClearScreen();
            cout<<"press escape to end simulation"<<endl;
            cout<<"press space to continue"<<endl;
            ch=getch();
            if(ch=='\0')
                loop = true;
            else
            {
                if(ch==' ')
                {
                    for(auto& i:vehiclesSim)
                    {
                        if (vehiclesSim.size() == 0)
                        {
                            loop = true;
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
                        cout<<"Simulation: "<<simulation->getName();
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
                        //i[0]->Update();
                        //i[1]->Update();
                        //mapAux[i][0]->Update();
                        it->second[0]->Update();
                        it->second[1]->Update();

                    }
                    //llamar al visualizador
                }
            }
        }
    }
}

void TrafficSimulator::StartSimulation(string simulationName, int cycles)
{
	char ch;
	auto auxVehicles = vehicles;
    bool loop=false;
    if(cycles==0)
    {
        while(loop==false)
        {
            getchar();
            ClearScreen();
            cout<<"press escape to end simulation"<<endl;
            cout<<"press space to continue"<<endl;
            ch=getch();
            if(ch=='\0')
                loop = true;
            else
            {
                if(ch==' ')
                {
                    for(auto& i:auxVehicles)
                    {

                        if (auxVehicles.size() == 0)
                        {
                            loop = true;
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
                        cout<<"Simulation: "<<simulationName;
                        //cout << "\r%"<<i;
                        //mapSimulator->show();
                        //auto vehicleArrived = i->Move();
                        /*if(vehicleArrived)
                        {
                            if (i != auxVehicles.end())
                            auxVehicles.erase(i);
                        }*/
                    }
                    for(auto it=mapAux.begin(); it!=mapAux.end(); ++it)
                    {

                        it->second[0]->Update();
                        it->second[1]->Update();

                    }
                    //llamar al visualizador
                }
            }

        }
        cout<<"simulation terminated"<<endl;
    }
    else
    {
        for(auto i = 0; i<cycles; i++)
        {
            getchar();
            ClearScreen();
            cout<<"press escape to end simulation"<<endl;
            cout<<"press space to continue"<<endl;
            ch=getch();
            if(ch=='\0')
                loop = true;
            else
            {
                if(ch==' ')
                {
                    for(auto& i:auxVehicles)
                    {
                        if (auxVehicles.size() == 0)
                        {
                            loop = true;
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
                        cout<<"Simulation: "<<simulationName;
                        //cout << "\r%"<<i;
                        //mapSimulator->show();
                        //auto vehicleArrived = i->Move();
                        /*if(vehicleArrived)
                        {
                            if (i != auxVehicles.end())
                            auxVehicles.erase(i);
                        }*/
                    }
                    for(auto it=mapAux.begin(); it!=mapAux.end(); ++it)
                    {
                        //i[0]->Update();
                        //i[1]->Update();
                        //mapAux[i][0]->Update();
                        it->second[0]->Update();
                        it->second[1]->Update();

                    }
                    //llamar al visualizador
                }
            }
        }
    }
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

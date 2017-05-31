#include "../parser/include/IOptionType.h"
#include "../parser/include/OptionParser.h"
#include "../include/TrafficSimulator.h"
#include "../include/WindowsConsole.h"

using namespace std;

string name;
int blocks;
int vehicles_by_blocs;
int vehicles;
int time_traffic_light;
int speed_min;
int speed_max;
int cycles;
bool verbose;

void GetValues(const vector<IOptionType*> &options)
{
    for (auto &o:options)
    {
        if (o->GetName() == "name")
        {
            name = static_cast<Text*>(o)->GetValue();
        }
        if (o->GetName() == "blocks")
        {
            blocks = static_cast<Integer*>(o)->GetValue();
        }
        if (o->GetName() == "vehicles_by_blocs")
        {
            vehicles_by_blocs = static_cast<Integer*>(o)->GetValue();
        }
        if (o->GetName() == "vehicles")
        {
            vehicles = static_cast<Integer*>(o)->GetValue();
        }
        if (o->GetName() == "time_traffic_light")
        {
            time_traffic_light = static_cast<Integer*>(o)->GetValue();
        }
        if (o->GetName() == "speed_min")
        {
            speed_min = static_cast<Integer*>(o)->GetValue();
        }
        if (o->GetName() == "speed_max")
        {
            speed_max = static_cast<Integer*>(o)->GetValue();
        }
        if (o->GetName() == "cycles")
        {
            cycles = static_cast<Integer*>(o)->GetValue();
        }
        if (o->GetName() == "verbose")
        {
            verbose = static_cast<Boolean*>(o)->GetValue();
        }
    }
}

int main(int argc, char* args[])
{
    try
    {
        OptionParser op(argc, (const char **)args);
        op.AddText("name", 'n'); //, true
        op.AddInteger("blocks", 'b');
        op.AddInteger("vehicles_by_blocs", 'y');
        op.AddInteger("vehicles", 'h');
        op.AddInteger("time_traffic_light", 't');
        op.AddInteger("speed_min", 'm');
        op.AddInteger("speed_max", 'x');
        op.AddInteger("cycles", 'c');
        op.AddBoolean("verbose", 'v', false);

        op.Validate();

        map<string, vector<IOptionType*>> options = op.GetOptions();
        for (auto &o : options)
        {
            GetValues(o.second);
        }
    }
    catch (exception& e)
    {
        cerr<<e.what()<<endl;
    }

	TrafficSimulator* a = new TrafficSimulator();
	shared_ptr<Map> mapa=make_shared<Map>(blocks, time_traffic_light, vehicles_by_blocs);
	a->BuildSimulation(mapa, name, vehicles, speed_min, speed_max);
	a->SetVisualization(verbose);
    a->StartSimulation(name, cycles);

    return 0;
}

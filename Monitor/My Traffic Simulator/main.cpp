#include "../parser/include/IOptionType.h"
#include "../parser/include/OptionParser.h"
#include "../include/TrafficSimulator.h"
#include "../include/WindowsConsole.h"

using namespace std;

int main(int argc, char* args[])
{
    try
    {
        int oArgc = 1;
        const char* oArgs[] = { "TS" };
        OptionParser op(oArgc, oArgs);
        op.AddText("name", 'n'); //, true
        op.AddInteger("blocks", 'b');
        op.AddInteger("vehicles_by_blocs", 'y');
        op.AddInteger("vehicles", 'h');
        op.AddInteger("time_traffic_light", 't');
        op.AddInteger("cycles", 'c');
        op.AddBoolean("verbose", 'v');

        op.Validate();

        map<string, vector<IOptionType*>> options = op.GetOptions();
        /*for (auto &o : options)
        {
            printOptions(o.first, o.second);
        }*/
    }
    catch (exception& e)
    {
        cerr<<e.what()<<endl;
    }

    size_t vehicleQuantity=3;
	size_t speedMin=1;
	size_t speedMax=2;
	size_t timeTrafficLight=2;
	size_t Vehicles=10;
	TrafficSimulator* a = new TrafficSimulator();
	shared_ptr<Map> mapa=make_shared<Map>(5, timeTrafficLight, Vehicles);
	a->BuildSimulation(mapa, "primeraSImulacion", vehicleQuantity, speedMin, speedMax);
    a->StartSimulation("primeraSImulacion", 50);

    return 0;
}

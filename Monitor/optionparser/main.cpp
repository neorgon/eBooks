#include "./include/OptionParser.h"

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>

using namespace std;

void printOptions(string optionname, vector<IOptionType*> Op)
{
    for(auto i:Op)
        switch(i->GetType())
        {
            case OptionType::Boolean:
            {
                cout << i->GetName() << ": " << static_cast<Boolean*>(i)->GetValue() << endl;
                break;
            }
            case OptionType::Integer:
            {
                cout << i->GetName() << ": " << static_cast<Integer*>(i)->GetValue() << endl;
                break;
            }
            case OptionType::Real:
            {
                cout << i->GetName() << ": " << static_cast<Real*>(i)->GetValue() << endl;
                break;
            }
            case OptionType::Text:
            {
                cout << i->GetName() << ": " << static_cast<Text*>(i)->GetValue() << endl;
                break;
            }
        }
}


int main(/*int argc, char* args[]*/)
{
    try
    {
        int argc = 14;
        //const char* args[] = { "Scanner", "--calorias", "250", "-g", "-10.0"};
        const char* args[] =
        {
            "Main",
            "--name", "\"Test TS\"",
            "--blocks" , "3",
            "--vehicles_by_blocs", "5",
            "--vehicles", "15",
            "--time_traffic_light", "2",
            "--cycles", "50",
            "--verbose"
        };

        OptionParser op(argc, args);
        op.AddText("name", 'n'); //, true
        op.AddInteger("blocks", 'b');
        op.AddInteger("vehicles_by_blocs", 'y');
        op.AddInteger("vehicles", 'h');
        op.AddInteger("time_traffic_light", 't');
        op.AddInteger("cycles", 'c');
        op.AddBoolean("verbose", 'v');

        op.Validate();

        map<string, vector<IOptionType*>> options = op.GetOptions();
        for (auto &o : options)
        {
            printOptions(o.first, o.second);
        }

    }
    catch (exception& e)
    {
        cerr<<e.what()<<endl;
    }

    return 0;
}

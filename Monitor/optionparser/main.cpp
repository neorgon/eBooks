#include <OptionParser.h>
#include "Integer.h"
#include "Boolean.h"
#include "Real.h"
#include "Text.h"
#include "IOptionType.h"

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
        int argc = 7;
        //const char* args[] = { "Scanner", "--calorias", "250", "-p", "100", "--grasas_saturadas", "0.8", "--nombre", "cereal kellogs", "--no-incluye", "[--grasas_hidrogenadas", "2.5", "-z", "50]", "-b", "-i" };
        //const char* args[] = { "Scanner", "-p", "100", "--no-incluye", "[--grasas_hidrogenadas", "2.5", "-z", "50]", "--calorias", "250" };
        //const char* args[] = { "Scanner", "--no-incluye", "--no-config" };
        //const char* args[] = { "Scanner", "-c", "45", "-p", "60" };
        const char* args[] = { "Scanner", "-ca", "45", "-p", "[60", "45", "50]" };
        //const char* args[] = { "Scanner", "--calorias", "250", "-p", "100", "--grasas_saturadas", "1.8", "--nombre", "cereal kellogs" };

        OptionParser op(argc, args);

        size_t i = 0;
        while(op.GetToken(i).compare("") != 0)
        {
            cout << op.GetToken(i) << endl;
            i++;
        }

        op.AddInteger("calorias", 'c');
        op.AddInteger("proteinas", 'p');
        op.AddReal("grasas_saturadas", 'g');
        op.AddReal("grasas_hidrogenadas", 'h', true);
        op.AddText("nombre", 'n', false);
        op.AddInteger("azucares", 'z');
        op.AddBoolean("bBool", 'b');
        op.AddBoolean("iBool", 'i');

        op.Validate();
        map<string, vector<IOptionType*>> options = op.GetOptions();
        for (auto &o : options)
        {
            printOptions(o.first,o.second);
        }
    }
    catch (exception& e)
    {
        cerr<<e.what()<<endl;
    }

    return 0;
}

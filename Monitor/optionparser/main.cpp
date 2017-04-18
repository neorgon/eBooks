#include <OptionParser.h>

using namespace std;

int main(/*int argc, char* args[]*/)
{
    int argc = 9;
    //const char* args[] = { "Scanner", "--calorias", "250", "-p", "100", "--grasas_saturadas", "0.8", "--nombre", "cereal kellogs", "--no-incluye", "[--grasas_hidrogenadas", "2.5", "-z", "50]", "-b", "-i" };
    //const char* args[] = { "Scanner", "--no-incluye", "[--grasas_hidrogenadas", "2.5", "-z", "50]" };
    //const char* args[] = { "Scanner", "--no-incluye", "--no-config" };
    const char* args[] = { "Scanner", "--calorias", "250", "-p", "100", "--grasas_saturadas", "0.8", "--nombre", "cereal kellogs" };

    OptionParser op(argc, args);

    /*size_t i = 0;
    while(op.GetToken(i).compare("") != 0)
    {
        cout << op.GetToken(i) << endl;
        i++;
    }*/

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddReal("grasas_saturadas", 'g');
    op.AddReal("grasas_hidrogenadas", 'h', true, 0);
    op.AddText("nombre", 'n', false, 2);
    op.AddList("no-incluye", 'i');
    op.AddInteger("azucares", 'z');
    op.AddBoolean("bBool", 'b');
    op.AddBoolean("iBool", 'i');

    op.Validate();

    map<string, vector<IOptionType*>> options = op.GetOptions();
    size_t i = 0;
    for (auto &o : options)
    {
        switch(o.second.at(i)->GetType())
        {
            case OptionType::Boolean:
            {
                break;
            }
            case OptionType::Integer:
            {
                cout << o.first << ": " << static_cast<int>(o.second.at(i)->GetValue()) << endl;
                break;
            }
            case OptionType::List:
            {
                break;
            }
            case OptionType::Real:
            {
                break;
            }
            case OptionType::Text:
            {
                break;
            }
        }
        i++;
    }

    return 0;
}

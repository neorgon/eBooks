#include <OptionParser.h>

using namespace std;

int main(/*int argc, char* args[]*/)
{
    int argc = 16;
    const char* args[] = { "Scanner", "--calorias", "250", "-p", "100", "--grasas_saturadas", "0.8", "--nombre", "cereal kellogs", "--no-incluye", "[--grasas_hidrogenadas", "2.5", "-z", "50]", "-b", "-i" };
    //const char* args[] = { "Scanner", "--no-incluye", "[--grasas_hidrogenadas", "2.5", "-z", "50]" };
    //const char* args[] = { "Scanner", "--no-incluye", "--no-config" };

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
    op.AddReal("grasas_hidrogenadas", 'h', true, 0);
    //op.AddString("nombre", "n", false, 2);

    return 0;
}

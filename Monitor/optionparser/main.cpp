#include <OptionParser.h>

using namespace std;

int main(/*int argc, char* args[]*/)
{
    int argc = 7;
    const char* args[] = { "Scanner", "--calorias", "250", "-p", "100", "--grasas_saturadas", "0.8", "--nombre", "\"cereal kellogs\"" };

    OptionParser op(argc, args);

    bool assertion = op.GetToken(0).compare("calorias") == 0 &&
                     op.GetToken(2).compare("p") == 0 &&
                     op.GetToken(3).compare("100") == 0;

    if(assertion)
        cout << "Great!!" << endl;
    else
        cout << "Fail :(" << endl;

    op.AddInteger("calorias", 'c');
    op.AddInteger("proteinas", 'p');
    op.AddReal("grasas_saturadas", 'g');
    op.AddReal("grasas_hidrogenadas", 'h', true, 0);
    //op.AddString("nombre", "n", false, 2);

    return 0;
}

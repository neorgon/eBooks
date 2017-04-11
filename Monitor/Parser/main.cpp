#include <Parser.h>

int main(/*int argc, char* args[]*/)
{
    bool assertion = false;
    int argc = 7;
    const char* args[] = { "Scanner", "--calorias", "250", "-p", "100", "--grasas_saturadas", "50.8", "--nombre", "\"cereal kellogs\"" };

    Parser np;
    np.AddInteger("calorias", 'c');
    np.AddInteger("proteinas", 'p');
    np.AddReal("grasas_saturadas", 'g');
    np.AddReal("grasas_hidrogenadas", 'h', true, 0);
    //np.AddString("nombre", "n", false, 2);

    try
    {
        assertion = np.Validate(argc, args);
    }
    catch (exception& e)
    {
        cout << e.what() << endl;
    }

    map<string, vector<Options>> parametros = np.GetOptions();
    for (auto& i : parametros)
    {
        cout << "K: " << i.first << "\n";

        for (auto& j : i.second)
        {
            //j.SetValue();
            cout << "    " << *((int*)(j.Value)) << "\n";
        }

    }


	cout << *((int*)(parametros.find("calorias")->second.at(0).Value)) /*
            *((int*)(parametros.find("proteinas")->second.at(0).Value))*/ << endl;

    /*if(assertion)
        assertion = np.GetJSon().compare("{ \"calorias\" : 250, \"proteinas\" : 100, \"grasas_saturadas\" : 50.8 }")*/

    if(assertion)
        cout << "Great!!" << endl;
    else
        cout << "Falied." << endl;

    np.Print();

    return 0;
}

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
  //          case OptionType::List:
  //          {
  //              cout << i->GetName() << ": " <<endl;
  //              cout << "............................." <<endl;
  //              printOptions(optionname,static_cast<List*>(i)->GetValue());
  //              cout << "............................." <<endl;
 //               break;
 //           }
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
//    int argc = 9;
    //const char* args[] = { "Scanner", "--calorias", "250", "-p", "100", "--grasas_saturadas", "0.8", "--nombre", "cereal kellogs", "--no-incluye", "[--grasas_hidrogenadas", "2.5", "-z", "50]", "-b", "-i" };
    //const char* args[] = { "Scanner", "-p", "100", "--no-incluye", "[--grasas_hidrogenadas", "2.5", "-z", "50]","--calorias", "250" };
    //const char* args[] = { "Scanner", "--no-incluye", "--no-config" };
//    const char* args[] = { "Scanner", "--calorias", "250", "-p", "100", "--grasas_saturadas", "1.8", "--nombre", "cereal kellogs" };

//    OptionParser op(argc, args);

//    size_t i = 0;
//    while(op.GetToken(i).compare("") != 0)
//    {
//        cout << op.GetToken(i) << endl;
//        i++;
//    }

/*    op.AddInteger("calorias", 'c', false);
    op.AddInteger("proteinas", 'p', false);
    op.AddReal("grasas_saturadas", 'g', false);
    op.AddReal("grasas_hidrogenadas", 'h', false);
    op.AddText("nombre", 'n', false);
//    op.AddList("no-incluye", 'i');
//    op.AddList("incluye", 'e');
    op.AddInteger("azucares", 'z', true);
    op.AddBoolean("bBool", 'b', false);
    op.AddBoolean("iBool", 'i', false);
*/
    int argc = 5;
    const char* args[] = { "Scanner", "--calorias", "250", "-g", "10.0"};

    //Act
    //Assert
    OptionParser op(argc, args);
    op.AddInteger("calorias", 'c',true);
    op.AddReal("grasas_saturadas", 'g',true);
    op.AddBoolean("fBool", 'f',false);


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

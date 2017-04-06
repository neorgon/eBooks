#include <Parser.h>




int main(int argc, char* args[])
{

        argc=3;
    char* arg[]={" ", "--nombre","\"205\"", };
    Parser np;

    np.AddInteger("calorias", "c", false);
    np.AddInteger("proteinas", "p", false);
    np.AddReal("grasas_saturadas", "g", false);
    np.AddReal("grasas_hidrogenadas", "h", true, 0);
    np.AddString("nombre", "n", false, 2);

//np.PrintRules();

    if(argc > 1)
    {
//        if((string) args[1] == "--help")
//			np.Help();
//
//		else
		try
		{
		    //np.Scanner(argc, args);
		    np.Scanner(argc, arg);
            np.PrintTokens();
		}
        catch (exception& e)
        {
            cout<<e.what()<<endl;
        }

    }

    else
        cout << "Missing parameters." << endl;
    try
    {
        np.LexicalAnalyzer();
        np.Analysing();
    }
    catch(exception& e)
    {
        cout<<e.what()<<endl;
    }


    np.PrintOptions();

    return 0;
}

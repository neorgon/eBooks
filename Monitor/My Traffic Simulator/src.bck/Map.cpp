#include "Map.h"
#include <ViewScreen.h>

map<int, vector<int>> Map::createMap(int sm)
{
    sizeMap = sm;
	int id=0;

	for (int i = 1; i <= sizeMap; ++i)
	{
		for (int j= 1; j <= sizeMap; ++j)
		{
			id++;
			adyacent={0,0};

		 	if (i%2!=0 && j%2 != 0)         //---->>>> y ^ arriba
			{
				if (id-(sizeMap*i)!=0)
				{
					//S_adyacent[0] = to_string(id+1)+"V";
					adyacent[0]=id+1;
				}
				if (id-sizeMap>=1)
				{
					//S_adyacent[1] = to_string(id-N)+"H";
					adyacent[1]=id-sizeMap;
				}
			}
			if (i%2!=0 && j%2 == 0)         //---->>> y v abajo
			{
				if (id-(sizeMap*i)!=0)
				{
					//S_adyacent[0] = to_string(id+1)+"V";
					adyacent[0]=id+1;
				}
				if (id+sizeMap <= sizeMap*sizeMap)
				{
					//S_adyacent[1] = to_string(id+sizeMap)+"H";
					adyacent[1]=id+sizeMap;
				}

			}

			if (i%2==0 && j%2 != 0)         //<<<---- y ^ arriba
			{
				if (id-(sizeMap*(i-1)+1)!=0)
				{
					//S_adyacent[0] = to_string(id-1)+"V";
					adyacent[0]=id-1;
				}
				if (id-sizeMap>=1)
				{
					//S_adyacent[1] = to_string(id-sizeMap)+"H";
					adyacent[1]=id-sizeMap;
				}

			}

			if (i%2==0 && j%2 == 0)         //<<<---- y v abajo
			{
				if (id-(sizeMap*(i-1)+1)!=0)
				{
					//S_adyacent[0] = to_string(id-1)+"V";
					adyacent[0]=id-1;
				}
				if (id+sizeMap <= sizeMap*sizeMap)
				{
					//S_adyacent[1] = to_string(id+sizeMap)+"H";
					adyacent[1]=id+sizeMap;
				}
			}

			mapTraffictLigth.insert(pair<int, vector<int>> (id, adyacent));

			//TrafficLight tl(to_string(id)+"V", 10, 20,  true);
			//TrafficLight tl(to_string(id)+"H", 10, 20, false);
		}
	}

 	return mapTraffictLigth;
}

void Map::show()
{
	map<int, vector<int>>::iterator it = mapTraffictLigth.begin();
	int counter = 0;

	ViewScreen vs(600, 800, "Traffic Simulator");
	vs.PrintTL(sizeMap);

	//for (it=mapTraffictLigth.begin(); it!=mapTraffictLigth.end(); ++it)
    //	cout <<"  "<< it->first << " : " << it->second[0] << " : "<< it->second[1] << '\n';

    /*for (it = mapTraffictLigth.begin(); it != mapTraffictLigth.end(); ++it)
    {
        counter++;
        cout << " " << it->first << " ";
        if (counter == sizeMap)
        {
            counter = 0;
            cout << "\n";
        }
    }*/

    //vs.GotoXY(0, 1);
    //cout << "Go!!\n";

    /*vs.GotoXY(1,1);
    cout << "*";
    vs.GotoXY(4,1);
    cout << "*";
    vs.GotoXY(8,1);
    cout << "*";
    vs.GotoXY(12,1);
    cout << "*";
    vs.GotoXY(1,4);
    cout << "*";
    vs.GotoXY(4,4);
    cout << "*";
    vs.GotoXY(8,4);
    cout << "*";
    vs.GotoXY(12,4);
    cout << "*";*/
    cout.flush();
    vs.GotoXY(1,1);
    cout << "#";
    getchar();
}
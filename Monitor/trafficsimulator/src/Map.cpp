#include "../include/Map.h"

Map::Map()
{
    //ctor
}

map<shared_ptr<TrafficLight>,vector<shared_ptr<TrafficLight>>> Map::createMap(int sizeMap)
{
	places={"Farmacia San Elias","Cayena"};
	adyacent={0,0};
	size_t id=0;
	for (int i = 1; i <= sizeMap; ++i)
	{
		for (int j= 1; j <= sizeMap; ++j)
		{
			id++;
			if (i%2 == 0)
			{
				if (id-(sizeMap*(i-1)+1)==0)
				{
					adyacent[0]=0;
				}
				else
				{
					adyacent[0]=id-1;
				}
			}
			else
			{
				if (id-(sizeMap*i)==0)
				{
					adyacent[0]=0;
				}
				else
				{
					adyacent[0]=id+1;
				}
			}

			if (j%2 == 0)
			{
				if (id-sizeMap<1)
				{
					adyacent[1]=0;
				}
			    else
			    {
				   adyacent[1]=id-sizeMap;
				}
			}
			else
			{
				if (id+sizeMap > sizeMap*sizeMap)
				{
					adyacent[1]=0;
				}
				else
				{
					adyacent[1]=id+sizeMap;
				}
			}
			auto trafficLight=make_shared<TrafficLight>(id,true,places,rand()%5,10);
		  auto trafficLightOne=make_shared<TrafficLight>(adyacent[0],true,places,rand()%5,10);
			shared_ptr<TrafficLight> trafficLightTwo=make_shared<TrafficLight>(adyacent[1],false,places,rand()%5,10);

			mapTraffictLigth[trafficLight].push_back(trafficLightOne);
			mapTraffictLigth[trafficLight].push_back(trafficLightTwo);

		}
	}
 return mapTraffictLigth;

}
  void Map::show()
{
	map<shared_ptr<TrafficLight>,vector<shared_ptr<TrafficLight>>>::iterator p = mapTraffictLigth.begin();
    while (p != mapTraffictLigth.end() )
  	{
  		int estado=p->first->getId();
  		cout << estado<<":  ";
		auto& vec = p->second;
		for (auto tl : vec)
		{
    		int estado2= tl->getId();
    		cout <<estado2<<"----";
		}
		cout << ":--------------"<<"\n";
    	p ++;
  	}
		//return mapTraffictLigth;
}
Map::~Map()
{
    //dtor
}

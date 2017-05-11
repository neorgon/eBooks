#include "../include/Map.h"
//#include "../include/TrafficLight.h"
Map::Map()
{
    //ctor
}

map<int,vector<TrafficLight*>> Map::createMap(int sizeMap)
{

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
					adyacent[0]=id+1;
				}
				if (id-sizeMap>=1)
				{
					adyacent[1]=id-sizeMap;
				}
			}

			if (i%2!=0 && j%2 == 0)         //---->>> y v abajo
			{
				if (id-(sizeMap*i)!=0)
				{
					adyacent[0]=id+1;
				}
				if (id+sizeMap <= sizeMap*sizeMap)
				{
					adyacent[1]=id+sizeMap;
				}
			}

			if (i%2==0 && j%2 != 0)         //<<<---- y ^ arriba
			{
				if (id-(sizeMap*(i-1)+1)!=0)
				{
					adyacent[0]=id-1;
				}
				if (id-sizeMap>=1)
				{
					adyacent[1]=id-sizeMap;
				}
			}

			if (i%2==0 && j%2 == 0)         //<<<---- y v abajo
			{
				if (id-(sizeMap*(i-1)+1)!=0)
				{
					adyacent[0]=id-1;
				}
				if (id+sizeMap <= sizeMap*sizeMap)
				{
					adyacent[1]=id+sizeMap;
				}
			}
			mapTrafficLight.insert(pair<int,vector<int>> (id,adyacent));

			TrafficLight* TL_Horizontal  = new TrafficLight(id, 0, 10, 20,  false);
			TrafficLight* TL_Vertical  = new TrafficLight(id, 1, 10, 20,  true);

			VectorTrafictlight.push_back(TL_Horizontal);
			VectorTrafictlight.push_back(TL_Vertical);


			mapLight.insert(pair<int,vector<TrafficLight*>> (id,VectorTrafictlight));
			VectorTrafictlight.clear();

		}
	}
 	return mapLight;

}
  void Map::show()
{
	map<int,vector<TrafficLight*>>::iterator it =  mapLight.begin();
		cout<<"\nNODO  TL  TL\n-------------------\n";
	for (it=mapLight.begin(); it != mapLight.end();++it )
	{
		cout<< "  " << it->first <<"  " << it->second.at(0)->GetTLID() <<"  " << it->second.at(1)->GetTLID() <<"\n";
	}
}

void Map::showMap()
{
	map<int,vector<int>>::iterator it = mapTrafficLight.begin();
		cout<<"\n ID  AdH  AdV\n-------------------\n";
	for (it=mapTrafficLight.begin(); it!=mapTrafficLight.end(); ++it)
    	cout <<"  "<< it->first << " : " << it->second[0] << " : "<< it->second[1] << '\n';
}

vector<int> Map::createRoute(int origin,int destination)
{
	vector<int> route;
    stack<int> routes;
    deque<int> vertices;
    vertices.push_back(origin);

    while(!vertices.empty())
    {
      	int vertex = vertices.front();
      	vertices.pop_front();
      	routes.push(vertex);

        if(vertex == destination)break;
        else
        {
          	map<int,vector<int>>::iterator itMap;
          	itMap = mapTrafficLight.find(vertex);
          	vector<int> adjacentVertex;
          	if (itMap != mapTrafficLight.end())
          	{
            	adjacentVertex = itMap->second;
          	}

          	for(auto k = 0U ; k < adjacentVertex.size(); k++)
          	{
              	int adjacent = adjacentVertex[k];
              	if(adjacent != 0)
              	{
			  		bool findRes = findStack(routes,adjacent);
              		bool findQueue1 = findQueue(vertices,adjacent);

              		if( findQueue1 == false && findRes == false)
              		{
                		vertices.push_back(adjacent);
					}
            	}
          	}
        }
    }

    int path = destination;
    routes.pop();
    route.push_back(path);
    while(!routes.empty())
    {
		int anotherPath;
		anotherPath = routes.top();
		routes.pop();
		auto trafficLight = mapTrafficLight.find(anotherPath);
		auto adjacents = trafficLight->second;
		for(auto& i : adjacents)
        {
            if( i == path)
            {
                path = trafficLight->first;
                route.push_back(trafficLight->first);
            }


        }

	}


 	reverse(route.begin(), route.end());
  	for(auto u = 0U ; u < route.size();u++)
  	{
    	cout<<route[u]<<"--->";

 	}
 	cout<<"\n";
 	return route;

}

bool Map::findStack(stack<int> auxStack,int value)
{
	stack<int> aux=auxStack;
  	while(!aux.empty())
  	{
    	int auxValue=aux.top();
    	aux.pop();
    	if(value==auxValue)
    	{
      		return true;
    	}
  	}
 	return false;
}

bool Map::findQueue(deque<int>& vertices,int value)
{
  	for(auto& it:vertices)
  	{
    	if(it==value)
    	{
    		return true;
    	}
  	}
  	return false;
}
Map::~Map()
{
    //dtor
}

 map<int,vector<TrafficLight*>> Map::get_mapTLight()
{
	return mapLight;
}

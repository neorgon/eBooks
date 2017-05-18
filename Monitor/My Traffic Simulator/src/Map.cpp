#include "../include/Map.h"
#include "../include/TrafficLight.h"

#include <algorithm>

Map::Map(int sizeMap, size_t timeTrafficLight, size_t maxVehicle) : sizeMap{sizeMap}
{
	int id = 0;
	size_t direction;
    vector<int> adyacents;
    vector<shared_ptr<TrafficLight>> VectorTrafictlight;

	for (int i = 1; i <= sizeMap; ++i)
	{
		for (int j = 1; j <= sizeMap; ++j)
		{
			id++;
			adyacents = {0, 0};

		 	if ((i % 2 != 0) && (j % 2 != 0))
			{
				if (id - (sizeMap * i) != 0)
				{
					adyacents[0] = id + 1;
				}
				if (id-sizeMap>=1)
				{
					adyacents[1] = id - sizeMap;
				}
				direction = static_cast<int>(Direction::goRight);
				direction = static_cast<int>(Direction::goUp);
			}

			if ((i % 2 != 0) && (j % 2 == 0))
			{
				if (id - (sizeMap * i) !=0 )
				{
					adyacents[0] = id + 1;
				}
				if (id + sizeMap <= sizeMap * sizeMap)
				{
					adyacents[1] = id + sizeMap;
				}
				direction = static_cast<int>(Direction::goRight);
				direction = static_cast<int>(Direction::goDown);
			}

			if ((i % 2 == 0) && (j % 2 != 0))
			{
				if (id - (sizeMap * (i - 1) + 1) != 0)
				{
					adyacents[0] = id - 1;
				}
				if (id - sizeMap >= 1)
				{
					adyacents[1] = id - sizeMap;
				}
				direction = static_cast<int>(Direction::goLeft);
				direction = static_cast<int>(Direction::goUp);
			}

			if ((i % 2 == 0) && (j % 2 == 0))
			{
				if (id - (sizeMap * (i - 1) + 1) !=0 )
				{
					adyacents[0] = id - 1;
				}
				if (id + sizeMap <= sizeMap * sizeMap)
				{
					adyacents[1] = id + sizeMap;
				}
                direction = static_cast<int>(Direction::goLeft);
                direction = static_cast<int>(Direction::goDown);
			}

			VectorTrafictlight.push_back
			(
                make_shared<TrafficLight>(direction, timeTrafficLight, maxVehicle,  true)
            );
            VectorTrafictlight.push_back
            (
                make_shared<TrafficLight>(direction, timeTrafficLight, maxVehicle,  false)
            );

			mapRoutes.insert(pair<int, vector<int>> (id, adyacents));
			mapTrafficLight.insert(pair<int, vector<shared_ptr<TrafficLight>>> (id, VectorTrafictlight));
			VectorTrafictlight.clear();
		}
	}
}

void Map::showMap()
{
	//map<int,vector<int>>::iterator it = mapTrafficLight.begin();
		cout<<"\n ID  AdH  AdV\n-------------------\n";
	for (auto it = mapRoutes.begin(); it != mapRoutes.end(); ++it)
    	cout <<"  "<< it->first << " : " << it->second[0] << " : "<< it->second[1] << '\n';
}


void Map::show()
{

	cout<<"\nNODO  TL  TL\n-------------------\n";
	for(auto it = mapTrafficLight.begin(); it != mapTrafficLight.end(); ++it)
	{
		cout<< "  " << it->first <<"  " << it->second[0]->GetTLID() <<"  "<< it->second[0]->GetDirection() <<"  " << it->second[1]->GetTLID() <<" "<< it->second[1]->GetDirection() <<"\n";
	}
}


vector<int> Map::createRoute(int origin,int destination)
{
	vector<int> route;  //respues     DFS
    stack<int> routes; // res aux
    deque<int> vertices;// cola
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
          	itMap = mapRoutes.find(vertex);
          	vector<int> adjacentVertex;
          	if (itMap != mapRoutes.end())
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
		auto trafficLight = mapRoutes.find(anotherPath);
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
  	/*for(auto u = 0U ; u < route.size();u++)
  	{
    	cout<<route[u]<<"--->";

 	}
 	cout<<"\n";*/
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

map<int, vector<shared_ptr<TrafficLight>>> Map::GetMapTrafficLight() const
{
	return mapTrafficLight;
}

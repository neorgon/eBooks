#include "../include/TrafficLight.h"
#include "../include/Map.h"
#include <math.h>


Map::Map(int sizeBlock, size_t timeTrafficLight, size_t maxVehicle) : sizeMap{sizeBlock + 1}
{
	int id=0;
	size_t dir1, dir2;
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
				dir1 = static_cast<int>(Direction::goRight);
				dir2 = static_cast<int>(Direction::goUp);
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
				dir1 = static_cast<int>(Direction::goRight);
				dir2 = static_cast<int>(Direction::goDown);
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
				dir1 = static_cast<int>(Direction::goLeft);
				dir2 = static_cast<int>(Direction::goUp);
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
                dir1 = static_cast<int>(Direction::goLeft);
                dir2 = static_cast<int>(Direction::goDown);
			}

			VectorTrafictlight.push_back
			(
                make_shared<TrafficLight>(dir1, timeTrafficLight, maxVehicle,id,  true)
            );
            VectorTrafictlight.push_back
            (
                make_shared<TrafficLight>(dir2, timeTrafficLight, maxVehicle, id, false)
            );

			mapRoutes.insert(pair<int, vector<int>> (id, adyacents));
			mapTrafficLight.insert(pair<int, vector<shared_ptr<TrafficLight>>> (id, VectorTrafictlight));
			VectorTrafictlight.clear();
		}
	}
}

vector<shared_ptr<TrafficLight>> Map::CreateRoute(const size_t &origin, const size_t &destination)
{
	int caseRoute = ReviewRoute(origin, destination);
	vector<shared_ptr<TrafficLight>> route = GenerateRoute(caseRoute, origin, destination);

	for(auto i : route)
	{
		cout<<i->GetNode() <<":"<< i->GetDirection() <<"  ";
	}
	cout<<"\n";

 	return route;
}


int Map::ReviewRoute(const int &origin, const int &destination)
{


	auto XYorigin = ConvertCoordinates(origin);
	auto XYdestination = ConvertCoordinates(destination);

 	if(XYorigin[1]<=XYdestination[1] && XYorigin[0]<=XYdestination[0])
	{
		if(XYorigin[0]%2!=0 && XYorigin[1]!=XYdestination[1] )
		{
			if(XYdestination[1]%2==0 )
			{
				return 1;
			}
			else
			{
				if(XYdestination[0]%2!=0  )
				{
					return 2;
				}
				else
				{
					if(XYdestination[0]<sizeMap)
					{
						return 3;
					}
					else
					{
						if(XYdestination[1]<sizeMap)
						{
							return 4;
						}
					}
			    }
			}
		}

		else
		{
			if(XYorigin[1]%2==0 && XYorigin[0] != XYdestination[0])
			{
				if(XYdestination[0]%2!=0)
				{
					return 5;
				}
				else
				{
					if(XYdestination[1]%2==0)
					{
						return 6;
					}
					else
					{
						if(XYdestination[0]<sizeMap)
						{
                            return 7;
						}
						else
						{
							if(XYdestination[1]<sizeMap)
							{
								return 8;
							}
						}
					}
			    }
			}
			else
			{
				if(XYorigin[1]>1 && XYorigin[0]%2==0 && XYorigin[0] != XYdestination[0] ) // recorrer -1 <-- y bajar
				{
					if(XYdestination[0]%2!=0)
					{
						return 9;
					}
					else
					{
						if(XYdestination[1]%2==0)
						{
							return 10;
						}
						else
						{
							if(XYdestination[0]<sizeMap)
							{
								return 11;
							}
							else
							{
								if(XYdestination[1]<sizeMap)
								{
									return 12;
								}
							}
						}
					}
				}
				else
				{
					if(XYorigin[1]!=XYdestination[1] && XYorigin[1]%2!=0)
					{
						if(XYdestination[1]%2==0 && XYorigin[0]>1  )
						{
							return 13;
						}
						else
						{
							if(XYdestination[1]%2==0)
							{
								return 14;
							}
							else
							{
								if(XYdestination[0]<sizeMap)
								{
									return 15;
								}
								else
								{
									if(XYdestination[1]<sizeMap)
									{
										return 16;
									}
								}
							}
						}
				    }
				}
			}
		}
	}

	if(XYorigin[1]>=XYdestination[1] && XYorigin[0]<=XYdestination[0])
	{
		if(XYorigin[0]%2==0 && XYorigin[1] != XYdestination[1])
		{
			if(XYdestination[1]%2==0)
			{
				return 17;
			}
			else
			{
				if(XYdestination[0]%2==0)
				{
					return 18;
				}
				else
				{
					if(XYdestination[0]<sizeMap )
					{
						return 19;
					}
					else
					{
						if(XYdestination[1]>1 )
						{
							return 20;
						}
						else
						{
							throw;
						}
					}
				}
			}
		}
		else
		{
			if(XYorigin[1]%2==0 && XYorigin[0] != XYdestination[0])
			{
				if(XYdestination[0]%2==0)
				{
					return 21;
				}
				else
				{
					if(XYdestination[1]%2==0)
					{
						return 22;
					}
					else
					{
						if(XYdestination[0]<sizeMap)
						{
							return 23;
						}
						else
						{
							if(XYdestination[1]>1)
							{
								return 24;
							}
							else
							{
								throw;
							}
						}
					}
				}
			}
			else
			{
				if(XYorigin[1]<sizeMap && XYorigin[0]%2!=0 && XYorigin[0]!=XYdestination[0])
				{
					if(XYdestination[0]%2==0)
					{
						return 25;
					}
					else
					{
						if(XYdestination[1]%2==0 && XYorigin[0] != XYdestination[0])
						{
							return 26;
						}
						else
						{
							if(XYdestination[0]<sizeMap )
							{
								return 27;
							}
							else
							{
								if(XYdestination[1]>1)
								{
									return 28;
								}
								else
								{
									throw 2;
								}
							}

						}
					}

				}
				else
				{
					if(XYorigin[0]>1 && XYorigin[1]!=XYdestination[1] && XYorigin[1]%2!=0 )
					{
					cout<<" : 4 \n";
						if(XYdestination[1]%2==0 ) // subir por 1 arriba y <----- CORRECTO
						{
							return 29;
						}
						else
						{
							if(XYdestination[0]%2==0) //destino puede bajar y <-- CORRECTO
							{
								return 30;
							}
							else
							{
								if(XYdestination[0]<sizeMap) ///  girar por abajo CORRECTO
								{
									return 31;
								}

								else
								{
									if(XYdestination[1]>1)// girar por ---> CORRECTO
									{
										return 32;
									}
									else
									{
										cout<<"No se puede llegar 3";
									}
								}
							}
						}
					}
					else
					{
						cout<<"de este nodo no se puede ir a ningun lado esta en la ezquina superior derecha \n";
					}
				}
			}
		}
	}
//////////////////////////////////////////derecha y arriba//////////////////////////////////////////////////

	if(XYorigin[1]<=XYdestination[1] && XYorigin[0]>=XYdestination[0])
	{
		cout<<"CASO: 3";
			if(XYorigin[0]%2!=0 && XYorigin[1] != XYdestination[1]) //orientacion --->
			{
				cout<<" : 1 \n";
				if(XYdestination[1]%2!=0) // destino puedo ir arriba  OK
				{
					return 33;
				}
				else
				{
					if(XYdestination[0]%2!=0 ) // destino puede ir --->  OK
					{
						return 34;
					}
					else
					{
						if(XYdestination[0]>1) // dar giro por arriba   OK
						{
							return 35;
						}
						else
						{
							if(XYdestination[1]<sizeMap) //giro por --> Ok
							{
								return 36;
							}
							else
							{
								cout<<"No se puede llegar";
							}
						}
					}
				}
			}

			else
			{
				if(XYorigin[1]%2!=0 && XYorigin[0] != XYdestination[0]) // orientacion arriba
				{
					cout<<" : 2 \n";
					if(XYdestination[0]%2!=0) // destino puedo ir --> OK
					{
						return 37;
					}
					else
					{
						if(XYdestination[1]%2!=0) //destono puedo subir  OK
						{
							return 38;
						}
						else
						{
							if(XYdestination[0]>1)  // girar por arriba OK
							{
								return 39;
							}
							else
							{
								if(XYdestination[1]<sizeMap) // girar por ---> OK
								{
									return 40;
								}
								else
								{
									cout<<"No se puede llegar 1";
								}
							}
						}
					}
				}
				else
				{
					if(XYorigin[1] > 1 && XYorigin[0]%2==0 && XYorigin[1]%2==0) // recorrer -1 <-- y subir
					{
						cout<<" : 3 \n";
						if(XYdestination[0]%2!=0 ) //destino puede ir -->  OK
						{
							return 41;
						}
						else
						{
							if(XYdestination[1]%2!=0 && XYorigin[0] != XYdestination[0]) // destino puede subir OK
							{
								return 42;
							}
							else
							{
								if(XYdestination[1]>1 && XYdestination[1]%2==0) // girar por arriba OK
								{
									return 43;
								}
								else
								{
									if(XYdestination[1]<sizeMap)// girar por ---->  OK
									{
										return 44;
									}
									else
									{
										cout<<"No se puede llegar 2";
									}
								}
							}
						}
					}
					else
					{
						if(XYorigin[1]!=XYdestination[1] && XYorigin[1]%2==0)
						{
							cout<<" : 4 \n";
							if(XYdestination[1]%2!=0) // bajar por 1 abajo y ----->  OK
							{
								return 45;
							}
							else
							{
								if(XYdestination[0]%2!=0) //destino puede bajar y --> OK
								{
									return 46;
								}
								else
								{
									if(XYdestination[0]>1) ///  girar por arriba
									{
										return 47;
									}
									else
									{
										if(XYdestination[1]<sizeMap)// girar por --->
										{
											return 48;
										}
										else
										{
											cout<<"No se puede llegar 3";
										}
									}
								}
							}
						}
					}
				}
	 		}

	}
///////////////////////////////////izquierda y arri/////////////////////////////////////////////////////////

	if(XYorigin[1]>=XYdestination[1] && XYorigin[0]>=XYdestination[0])
	{
		cout<<"CASO: 4 ";
			if(XYorigin[0]%2==0 && XYorigin[0]>1  && XYorigin[1] != XYdestination[1] && XYorigin[0] != XYdestination[0]) //orientacion <---
			{
			cout<<" : 1 \n";
				if(XYdestination[1]%2!=0 ) // destino puedo ir arriba OK
				{
					return 49;
				}
				else
				{
						if(XYdestination[0]%2==0) // destino puede ir <--- OK
						{
							return 50;
						}
						else
						{
							if(XYdestination[0]>1 ) // dar giro por arriba   OK
							{
								return 51;
							}
							else
							{
								if(XYdestination[1]>1) //giro por <---  OK
								{
									return 52;
								}
								else
								{
									cout<<"No se puede llegar";
								}
							}
						}

				}
			}

			else
			{
				if(XYorigin[1]%2!=0 && XYorigin[0]!=XYdestination[0]) // orientacion arriba
				{
				cout<<" : 2 \n";
					if(XYdestination[0]%2==0) // destino puedo ir <--- CORRECTO
					{
						return 53;
					}
					else
					{
						if(XYdestination[1]%2!=0) //destono puedo subir    OK
						{
							return 54;
						}
						else
						{
							if(XYdestination[0]>1)  // girar por arriba OK
							{
								return 55;
							}
							else
							{
								if(XYdestination[1]>1) // girar por <---  OK
								{
									return 56;
								}
								else
								{
									cout<<"No se puede llegar 1";
								}
							}
						}
					}
				}
				else
				{
					if(XYorigin[1]<sizeMap  && XYorigin[0]%2!=0 && XYorigin[0]!=XYdestination[0]) // recorrer +1 --> y subir
					{
					cout<<" : 3 \n";
						if(XYdestination[0]%2==0) //destino puede ir <--   OK
						{
							return 57;
						}
						else
						{
							if(XYdestination[1]%2!=0) // destino puede baja  CORRECTO
							{
								return 58;
							}
							else
							{
								if(XYdestination[0]>1) // girar por arriba  OK
								{
									return 59;
								}
								else
								{
									if(XYdestination[1]>1)// girar por <---- OK
									{
										return 60;
									}
									else
									{
										cout<<"No se puede llegar 2";
									}
								}
							}
						}
					}
					else
					{
						if(XYorigin[0] < sizeMap && XYorigin[1]!= XYdestination[1] && XYorigin[1]%2==0 && XYorigin[0]%2!=0 ) //  bajar por 1 abajo y <----- OK
						{
						cout<<" : 4\n";
							if(XYdestination[1]%2!=0) // DESTINO TIENE CAMINO ASIA ARRIBA
							{
								return 61;
							}
							else
							{
								if(XYdestination[0]%2==0) //destino puede bajar y <-- OK
								{
									return 62;
								}
								else
								{
									if(XYdestination[0]>1) ///  girar por arriba OK
									{
										return 63;
									}

									else
									{
										if(XYdestination[1]>1)// girar por ---> CORRECTO
										{
											return 64;
										}
										else
										{
											cout<<"No se puede llegar 3";
										}
									}
								}
							}
						}
					}
				}
			}

	}
//////////////////////////CASO BORDE IZQUIERDO /////////////////////////////////////////////////////////////

	if(XYorigin[1]==XYdestination[1] && XYorigin[1]==1 && XYorigin[0]%2 ==0)
	{
		if(XYdestination[0]%2==0)
		{
			return 65;
		}
		else

			if(XYdestination[0]<sizeMap)
			{
				return 66;
			}
			else
			{
				cout<<"no se puede LLegar \n";
			}

	}
//////////////////////////CASO BORDE DERECHO ///////////////////////////////////////////////////////////////

	if(XYorigin[1]==XYdestination[1] && XYorigin[1]==sizeMap && XYorigin[0]%2 !=0)
	{
		if(XYdestination[0]%2!=0)
		{
			return 67;
		}
		else
			if(XYdestination[0]<sizeMap)
			{
				return 68;
			}
			else
			{
				cout<<"no se puede LLegar \n";
			}
	}

	return 0;
}


vector<shared_ptr<TrafficLight>> Map::GenerateRoute(const int &caseRoute,const int &origin, const int &destination)
{

	auto XYorigin = ConvertCoordinates(origin);
	auto XYdestination = ConvertCoordinates(destination);

	vector<shared_ptr<TrafficLight>> route;
	auto TL = mapTrafficLight.find(origin);
	route.push_back(TL->second[1]);
	int nodoAux;
	shared_ptr<TrafficLight> aux;
	switch(caseRoute)
	{
		case 0 :
				cout<<"no se encontro un camino para este caso; "<< origin <<" : " << destination <<"\n";
				break;
		case 1 :
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
				break;
		case 2 :

					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );

				break;
		case 3 :

					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					nodoAux += -sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back(TL->second[1]);

				break;
		case 4 :


					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					nodoAux += 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					nodoAux += -1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);

				break;
		case 5 :

					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
				break;
		case 6 :

					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );

				break;
		case 7 :

					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );

				break;
		case 8 :

					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );
					nodoAux += -1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );

				break;
		case 9 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);

				break;
		case 10 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);

				break;
		case 11 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
				break;
		case 12 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1]+2,Direction::goRight,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					nodoAux += -1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
				break;
		case 13 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
				break;
		case 14 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
				break;
		case 15 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0]+2,Direction::goDown,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += -sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);

				break;
		case 16 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					nodoAux += -1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);

				break;
		case 17 :

					StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);

				break;
		case 18 :

					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
				break;
		case 19:

					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					nodoAux += -sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );

				break;
		case 20 :

					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					nodoAux += -1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					nodoAux += sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );
					nodoAux += 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );

				break;
		case 21 :

					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);

				break;
		case 22 :

					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );

				break;
		case 23 :

					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );
					nodoAux +=  sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );
					nodoAux +=  -1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					nodoAux += -sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );
				break;
		case 24 :

					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goLeft,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );
					nodoAux += 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );

				break;
		case 25 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goLeft,route);

				break;
		case 26 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goLeft,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );

				break;
		case 27 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );
					nodoAux += sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );
					nodoAux += -1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					nodoAux += -sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );
				break;
		case 28 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goDown,route);
					StoreRoute(XYorigin[1],XYdestination[1]-2,Direction::goLeft,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()+sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );
					nodoAux += 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );

				break;
		case 29 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);
					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);

				break;
		case 30 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );

				break;
		case 31 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
					StoreRoute(XYorigin[0],XYdestination[0]+2,Direction::goDown,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					nodoAux += -sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );
				break;
		case 32 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goDown,route);
				    aux = route.at(route.size()-1);
					nodoAux = aux->GetNode()-1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					nodoAux += -1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );
					nodoAux += +sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1] );
					nodoAux += 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0] );

				break;
		case 33 :

					StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);

				break;
		case 34 :

					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() + 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);

				break;
		case 35 :

					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() + 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back(TL->second[1]);

				break;
		case 36 :

					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() + 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += -sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back(TL->second[1]);
					nodoAux += -1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);

				break;
		case 37 :

					StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);

				break;
		case 38 :

					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp,route);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);

				break;
		case 39 :

					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() + sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);

				break;
		case 40 :

					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp,route);
					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					nodoAux += - 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);

				break;
		case 41 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);
					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);

				break;
		case 42 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp,route);
					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
				break;
		case 43 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);
					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goRight,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() + sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
				break;
		case 44 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);
					StoreRoute(XYorigin[1],XYdestination[1]+2,Direction::goRight,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() + sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					nodoAux += -1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);

				break;
		case 45 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() + sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);

				break;
		case 46 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() + sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() + 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);

				break;
		case 47 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() + sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0]-2,Direction::goUp,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() + 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);

				break;
		case 48 :

					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() + sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goRight,route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() + 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += -sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					nodoAux += -1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);

				break;
		case 49 :

					StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft, route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);

				break;
		case 50 :

					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft, route);
					StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);

				break;
		case 51 :

					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft, route);
					StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);

				break;
		case 52 :

					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft, route);
					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += -1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += -sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					nodoAux += 1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);

				break;
		case 53 :

					StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp, route);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);

				break;
		case 54 :

					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp, route);
					StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
				break;
		case 55 :

					StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp, route);
					StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft,route);
					aux = route.at(route.size()-1);
					nodoAux = aux->GetNode() - sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					nodoAux += -sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);
					nodoAux += -1;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[0]);
					nodoAux += sizeMap;
					TL = mapTrafficLight.find(nodoAux);
					route.push_back( TL->second[1]);

				break;
		case 56 :

				StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp, route);
				StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goLeft,route);
				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() - sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				nodoAux += 1;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);

				break;
		case 57 :

				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() + 1;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp, route);
				StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goLeft,route);

				break;
		case 58 :

				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() + 1;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp, route);
				StoreRoute(XYorigin[1],XYdestination[1]-1,Direction::goLeft,route);
				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() - sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);

				break;
		case 59 :

				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() + 1;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp, route);
				StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft,route);
				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() - sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				nodoAux += -sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				nodoAux += -1;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				nodoAux += sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);

				break;
		case 60 :

				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() + 1;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp, route);
				StoreRoute(XYorigin[1],XYdestination[1]-2,Direction::goLeft,route);
				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() - sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				nodoAux += 1;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);

				break;
		case 61 :

				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() + sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				StoreRoute(XYorigin[1],XYdestination[1],Direction::goLeft, route);
				StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);

				break;
		case 62 :

				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() + sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft, route);
				StoreRoute(XYorigin[0],XYdestination[0]-1,Direction::goUp,route);
				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() -1;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);

				break;
		case 63 :

				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() + sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft, route);
				StoreRoute(XYorigin[0],XYdestination[0]-2,Direction::goUp,route);
				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() -1;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				nodoAux += sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);

				break;
		case 64 :

				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() + sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				StoreRoute(XYorigin[1],XYdestination[1]+1,Direction::goLeft, route);
				StoreRoute(XYorigin[0],XYdestination[0],Direction::goUp,route);
				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() -1;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				nodoAux += -1;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				nodoAux += -sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				nodoAux += 1;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);

				break;
		case 65 :

				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() - sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				nodoAux += 1 ;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goDown,route);
				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode()  -1 ;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				break;
		case 66 :

				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() - sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				nodoAux += 1 ;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				StoreRoute(XYorigin[0],XYdestination[0]+2,Direction::goDown,route);
				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode()  -1 ;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				nodoAux += -sizeMap ;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				break;
		case 67 :

				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() + sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				nodoAux += -1 ;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				StoreRoute(XYorigin[0],XYdestination[0]+1,Direction::goUp,route);
				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode()  +1 ;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				break;
		case 68 :

				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode() + sizeMap;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				nodoAux += -1 ;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				StoreRoute(XYorigin[0],XYdestination[0]-2,Direction::goUp,route);
				aux = route.at(route.size()-1);
				nodoAux = aux->GetNode()  +1 ;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[0]);
				nodoAux += +sizeMap ;
				TL = mapTrafficLight.find(nodoAux);
				route.push_back( TL->second[1]);
				break;

	}
	return route;
}



void Map::StoreRoute(const size_t &ini , const size_t &fin , Direction orientation, vector<shared_ptr<TrafficLight>> &route)
{
	auto ultimatePosision = route.at(route.size()-1);
	int ultimateNodo = ultimatePosision->GetNode() ;
	size_t initial;
	size_t final;
	size_t incremento;
	int uxTL;
	switch(orientation)
	{
		case Direction::goUp:
				uxTL=1;
				initial= fin;
				final= ini;
				incremento= -sizeMap;
			break;
		case Direction::goDown:
				uxTL=1;
				initial= ini ;
				final= fin;
				incremento = sizeMap;
			break;
		case Direction::goRight:
				uxTL=0;
				initial= ini;
				final= fin;
				incremento = 1;
			break;
		case Direction::goLeft:
				uxTL=0;
				initial= fin;
				final= ini;
				incremento = -1;
			break;
	}
	for(auto i = initial ; i<final; ++i )
	{
		ultimateNodo+=incremento;
		auto findNodo =  mapTrafficLight.find(ultimateNodo);
		route.push_back(findNodo->second[uxTL]);
	}
}

map<int, vector<shared_ptr<TrafficLight>>> Map::GetMapTrafficLight() const
{
	return mapTrafficLight;
}

void Map::CreateAdjacentTrafficLight()
{
	vector<shared_ptr<TrafficLight>> vectorTrafictlight;
	for (auto it = mapRoutes.begin(); it != mapRoutes.end(); ++it)
	{
		auto adjacentNode=it->second;
		auto node=mapTrafficLight.find(it->first);
		auto trafficLightNode=node->second;
		vector<shared_ptr<TrafficLight>> auxTrafficLight;

		if(adjacentNode[0] != 0)
		{
			auto adjacentH=mapTrafficLight.find(adjacentNode[0]);
			auxTrafficLight=adjacentH->second;
			vectorTrafictlight.push_back(auxTrafficLight[0]);
		}

		if(adjacentNode[1] != 0)
		{
			auto adjacentV=mapTrafficLight.find(adjacentNode[1]);
			auto auxTrafficLightV=adjacentV->second;
			vectorTrafictlight.push_back(auxTrafficLightV[1]);
		}

		adjacentTrafficLight.insert(pair<shared_ptr<TrafficLight>,vector<shared_ptr<TrafficLight>>>
			(trafficLightNode[0],vectorTrafictlight));
		adjacentTrafficLight.insert(pair<shared_ptr<TrafficLight>,vector<shared_ptr<TrafficLight>>>
			(trafficLightNode[1],vectorTrafictlight));
		vectorTrafictlight.clear();
	}
		/*adjacentTrafficLight[trafficLightNode[0]]=vectorTrafictlight;
		adjacentTrafficLight[trafficLightNode[1]]=vectorTrafictlight;
		vectorTrafictlight.clear();
		auxTrafficLight.clear();

	}*/

	cout<<"\nNODO  TL  TL\n-------------------\n";
	for(auto it = adjacentTrafficLight.begin(); it != adjacentTrafficLight.end(); ++it)
	{
		auto ad=it->second;
		if(ad.size()==2)
		{
		cout
            << "  " << it->first->GetNode() <<"--"<<it->first->GetDirection()<< " ** " << it->second[0]->GetNode() << "--"
            << it->second[0]->GetDirection() << "***  " << it->second[1]->GetNode() << "--" << it->second[1]->GetDirection() <<"\n";
		}
		else
		{
			cout
            << "  " << it->first->GetNode() << "--"<<it->first->GetDirection()<<" ** " << it->second[0]->GetNode() << "--"
            << it->second[0]->GetDirection() << "\n";
		}
	}
}

map<shared_ptr<TrafficLight>,vector<shared_ptr<TrafficLight>>> Map::GetAdjacentTrafficLight()
{
	return adjacentTrafficLight;
}

vector<size_t> Map::ConvertCoordinates(const int &x)
{
	vector<size_t> coordinates;
	coordinates={0,0};

	coordinates[0]=(int)ceil((double)x/sizeMap);
	coordinates[1]= sizeMap-((sizeMap*coordinates[0])-x);

	return coordinates;

}

int Map::GetMapSize() const
{
	return sizeMap;
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
		cout
            << "  " << it->first << "  " << it->second[0]->GetNode() << "  "
            << it->second[0]->GetDirection() << "  " << it->second[1]->GetNode() << " " << it->second[1]->GetDirection() <<"\n";
	}
}

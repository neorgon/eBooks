#include <set>
#include <string>
#include <iostream>
#include <unordered_set>
using namespace std;

struct car
{
	string id;
	string brand;
	bool operator< (const car& c) const
	{
		return id <c.id;
	}
	void show() const
	{
		cout << id <<" ; "<< brand <<"\n";
	}
	bool operator()(const car& a, const car& b ) const
	{
		/*if(a.brand < b.brand)
			return true;
		if(a.brand > b.brand)
			return false;
		return a.id < b.id;*/
		return tie(a.brand, a.id) <	tie(b.brand, b.id);// devuelve un objeto del tipo tuple
	}
	bool operator==(const car& c)const
	{
		return id == c.id;
	}
};
struct car_comp
{
	bool operator()(const car& a, const car& b ) const
	{
		/*if(a.brand < b.brand)
			return true;
		if(a.brand > b.brand)
			return false;
		return a.id < b.id;*/
		return tie(a.brand, a.id) <	tie(b.brand, b.id);// devuelve un objeto del tipo tuple
	}
};
struct car_hash
{
	size_t operator()(const car& c)const
	{
		/*size_t h = 0;
		for(auto& i: c.id)
		{
			h+= i*31;
		}
		return h;*/
		hash<string> hs;
		return hs(c.id);
	}
};
int main(int argc, char const *argv[])
{
	/*unordered_set<string> pp = {"venezuela","bolivia","chile","peru","ecuador","argentina","brasil","paraguay","uruaguay"};
	//set<string> pp = {"venezuela","bolivia","chile","peru","ecuador","argentina","brasil","paraguay","uruaguay"}; ordena por criterio de hash
	pp.insert("colombia");
	for(auto& i: pp)
	{
		cout << i <<"\n";
	}
	auto it = pp.find("paraguaya");// find devuelve un iterador
	if(it == pp.end())
	{
		cerr << "not found\n";
		//no se encontro el elemento
	}
	else
	{
		cout << *it <<"\n";
	}*/

	//set<car, car_comp> cars;
	unordered_set<car,car_hash> cars;
	cars.insert(car{"001ABC", "Ford"});
	cars.insert(car{"4971XYZ", "VW"});
	cars.insert(car{"2560XXA", "Susuki"});
	cars.insert(car{"1234MMO", "VW"});
	for(auto& i: cars)
	{
		i.show();
	}
	auto x = cars.find(car{"4971XYZ"});
	if(x == cars.end())
		cerr<< "NOT FOUND\n";
	else
		x->show();
	return 0;
}

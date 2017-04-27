#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Street
{
    string name;

    public:
        Street(const string &n) : name{n} {}
        string GetName() const;
};

string Street::GetName() const
{
    return name;
}

class Block
{
    string name;
    int number;
    set<Street*> streets;

    public:
        Block(const string &n, int i) : name{n}, number{i} {}
        string GetName() const;
        int GetNumber() const;
        void AddStreet(const string &name);
};

string Block::GetName() const
{
    return name;
}

int Block::GetNumber() const
{
    return number;
}

void Block::AddStreet(const string &name)
{
    streets.insert(new Street(name));
}

class Vehicle
{

};

class Semaphore
{

};

class City
{
    vector<Block*> blocks;

    public:
        void AddBlock(const string &name, int number);
        void Show() const;
};

void City::AddBlock(const string &name, int number)
{
    blocks.push_back(new Block(name, number));
}

void City::Show() const
{
    cout << ".:LEGO CITY:.\n";
    for (auto &b : blocks)
        cout << b->GetName() << ":" << b->GetNumber() << endl;
}

int main()
{
    City legocity;

    legocity.AddBlock("A", 1);
    legocity.AddBlock("A", 2);
    legocity.AddBlock("A", 3);
    legocity.AddBlock("B", 1);
    legocity.AddBlock("B", 2);
    legocity.AddBlock("B", 3);
    legocity.AddBlock("C", 1);
    legocity.AddBlock("C", 2);
    legocity.AddBlock("C", 3);
    legocity.Show();

    return 0;
}

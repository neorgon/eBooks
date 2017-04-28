#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

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

    public:
        Block(const string &n) : name{n} {}
        string GetName() const;
        int GetNumber() const;

        struct Finder {
            string name;
            Finder(const string &n) : name{n} {};
            bool operator()(const Block &b) const
            {
                return b.name.compare(name) == 0;
            }
        };
};

string Block::GetName() const
{
    return name;
}

class Vehicle
{

};

class Semaphore
{

};

class City
{
    vector<Block> blocks;
    vector<Street> streets;
    map<string, vector<Block*>> address;

    public:
        void AddBlock(const string &name);
        void AddStreet(const string &name);
        Block GetBlock(const string &name) const;
        void Show() const;
};

void City::AddBlock(const string &name)
{
    blocks.push_back(Block(name));
}

void City::AddStreet(const string &name)
{
    streets.push_back(Street(name));
}

Block City::GetBlock(const string &name) const
{
    auto it = find_if(blocks.begin(), blocks.end(), Block::Finder(name));
    if (it != blocks.end())
        return *it;
}

void City::Show() const
{
    cout << ".:LEGO CITY:.\n";
    for (auto &b : blocks)
        cout << b.GetName() << endl;
    for (auto &s : streets)
        cout << "Street: " << s.GetName() << endl;
}

int main()
{
    City legocity;

    legocity.AddBlock("A1");
    legocity.AddBlock("A2");
    legocity.AddBlock("A3");
    legocity.AddBlock("B4");
    legocity.AddBlock("B5");
    legocity.AddBlock("B6");
    legocity.AddBlock("C7");
    legocity.AddBlock("C8");
    legocity.AddBlock("C9");
    legocity.AddStreet("SH1");
    legocity.AddStreet("SH2");
    legocity.AddStreet("SH3");
    legocity.AddStreet("SH4");
    legocity.AddStreet("SV1");
    legocity.AddStreet("SV2");
    legocity.AddStreet("SV3");
    legocity.AddStreet("SV4");
    legocity.Show();

    return 0;
}

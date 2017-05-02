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
        friend bool operator==(const Block &b1, const Block &b2);
};

string Block::GetName() const
{
    return name;
}

bool operator==(const Block &b1, const Block &b2)
{
    return b1.name == b2.name;
}

class Semaphore
{
    bool CanGo;
    pair<string, string> location;

    public:
        bool GetStatus();
};

bool Semaphore::GetStatus()
{
    return CanGo;
}

class Vehicle
{

};

class City
{
    vector<Block> blocks;
    vector<Street> streets;
    map<string, vector<Block>> address;

    public:
        void AddBlock(const string &name);
        void AddStreet(const string &name);
        Block GetBlock(const string &name) const;
        void InsertAddress(const string &street, const string &block);
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
    auto it = find(blocks.begin(), blocks.end(), Block(name));
    if (it != blocks.end())
        return *it;
    return Block("");
}

void City::InsertAddress(const string &street, const string &block)
{
    address.insert(pair<string, vector<Block>> (street, vector<Block>()));
    address[street].push_back(GetBlock(block));
}

void City::Show() const
{
    cout << ".:LEGO CITY:.\n";
    for (auto &a: address)
    {
        cout << a.first << endl;
        for (auto &b : a.second)
        {
            cout << b.GetName() << " ";
        }
        cout << endl;
    }
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
    /*
    legocity.AddStreet("SH1");
    legocity.AddStreet("SH2");
    legocity.AddStreet("SH3");
    legocity.AddStreet("SH4");
    legocity.AddStreet("SV1");
    legocity.AddStreet("SV2");
    legocity.AddStreet("SV3");
    legocity.AddStreet("SV4");
    */
    legocity.InsertAddress("SH1", "A1");
    legocity.InsertAddress("SH1", "A2");
    legocity.InsertAddress("SH1", "A3");
    legocity.InsertAddress("SH2", "A1");
    legocity.InsertAddress("SH2", "A2");
    legocity.InsertAddress("SH2", "A3");
    legocity.InsertAddress("SH2", "B4");
    legocity.InsertAddress("SH2", "B5");
    legocity.InsertAddress("SH2", "B6");
    legocity.InsertAddress("SH3", "B4");
    legocity.InsertAddress("SH3", "B5");
    legocity.InsertAddress("SH3", "B6");
    legocity.InsertAddress("SH3", "A1");
    legocity.InsertAddress("SH3", "A2");
    legocity.InsertAddress("SH3", "A3");
    legocity.InsertAddress("SH4", "C7");
    legocity.InsertAddress("SH4", "C8");
    legocity.InsertAddress("SH4", "C9");
    legocity.Show();

    return 0;
}

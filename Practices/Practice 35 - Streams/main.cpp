#include <iostream>
#include <sstream>
#include <map>

using namespace std;

map<string, int> get_occurrences(const string &s)
{
    map<string, int> r;

    stringstream occ{s};

    while(occ.good())
    {
        string aux;
        occ >> aux;
        r[aux]++;
    }

    return r;
}

int main()
{
    /*
    string p = "5 15";
    stringstream iss{p};
    int a, b;
    iss >> a;
    iss >> b;
    */
    //ss << "La suma de " << x << " y " << y << " es " << (x + y) << endl;
    //cout << (a * b) << endl;
    string song = "we are the world we are the children";
    auto oc = get_occurrences(song);
    for (auto &i : oc)
    {
        cout << i.first << ": " << i.second << endl;
    }

    return 0;
}

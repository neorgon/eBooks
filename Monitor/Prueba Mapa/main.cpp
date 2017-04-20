#include <iostream>
#include <map>

using namespace std;

map<int, string> pruebas;

int main()
{
    pruebas.insert(pair<int, string>(1, "hola"));
    pruebas.insert(pair<int, string>(2, "mundo"));
    pruebas.insert(pair<int, string>(2, "camarada"));

    for (auto &p : pruebas)
        cout << p.first << ": " << p.second << endl;

    return 0;
}

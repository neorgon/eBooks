#include <iostream>

using namespace std;

//const char** get_months()
//void get_months(const char** &ms)
void get_months(const char*** q) // a la manera de C
{
    //const char** ms = new const char* [12];
    /*ms = new const char* [12];
    ms[0] = "Enero"; //const char*
    ms[1] = "Febrero";
    ms[2] = "Marzo";
    ms[3] = "Abril";
    ms[4] = "Mayo";
    ms[5] = "Junio";
    ms[6] = "Julio";
    ms[7] = "Agosto";
    ms[8] = "Septiembre";
    ms[9] = "Octubre";
    ms[10] = "Noviembre";
    ms[11] = "Diciembre";*/

    auto ms = new const char* [12];
    ms[0] = "Enero"; //const char*
    ms[1] = "Febrero";
    ms[2] = "Marzo";
    ms[3] = "Abril";
    ms[4] = "Mayo";
    ms[5] = "Junio";
    ms[6] = "Julio";
    ms[7] = "Agosto";
    ms[8] = "Septiembre";
    ms[9] = "Octubre";
    ms[10] = "Noviembre";
    ms[11] = "Diciembre";

    *q = ms;

//    return ms;
}

void print(const char** x, size_t n)
{
    for (auto i=0U; i<n; i++)
    {
        cout << x[i] << endl;
    }
}

int main()
{
    /*int z = 8;
    int* pz = &z;
    int** ppz = &pz;
    int*** pppz = &ppz;
    int**** ppppz = &pppz;*/

    /*auto ms = get_months();
    print(ms, 12);
    delete []ms;*/

    const char** p;
    get_months(&p);
    print(p, 12);

    return 0;
}

#include <iostream>

using namespace std;

int main()
{
    int* p; //dangling pointer
    int s = 25;
    int* r = &s;
    /*int* m = nullptr; Cuidado!!
    *m = 4;*/

    int* n = &s;


    cout << *r << endl;
    (*r)++;
    cout << *r << endl;
    cout << s << endl;
    //cout << *m << endl;

    cout << n << endl;
    n++;
    cout << n << endl;
    cout << *n << endl;
    /* n += 1500000;     Se sale del rango de memoria asignado
    cout << *n << endl; */

    int x1 = 8, x2 = 10, x3 = 20;
    int* pp = &x1;

    cout << *pp++ << endl;
    cout << *pp++ << endl;
    cout << *pp++ << endl;

    return 0;
}

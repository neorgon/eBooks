#include <iostream>

using namespace std;

void print(int* x, size_t n)
{
    for (int i = 0; i < n; i++)
    {
        //cout << x[i] << endl; igual que *(x+i)
        cout << *(x+i) << endl; // igual que i[x]
    }
}

void populate(int* x, size_t n)
{
    for (int i=0; i<n; i++)
    {
        x[i] = (i+1)*5;
    }
}

void populate2(int*& x, size_t &n)
{
    x = new int[2];
    x[0] = 1000;    //*x = 1000;
    x[1] = 2000;    //*++x = 2000;
    n=2;
}

int main()
{
    double ns[3];
    ns[0] = 8;
    ns[1] = 10;
    ns[2] = 12;

    int m[] = {2, 8, 9, 15};
    int m2[] = {1, 3, 5, 7, 8, 11, 13};

    print(m, 4);
    print(m2, sizeof(m2) / sizeof(int));

    int* b1 = new int {155};
    print(b1, 1);

    int* b2 = new int[10];
    populate(b2, 10);
    cout << "****************" << endl;
    print(b2, 10);

    int* b3;
    size_t tb3;
    populate2(b3, tb3);
    print(b3, tb3);

    cout << "****************" << endl;
    int b8 = 8;
    print(&b8, 1);

    delete b1;
    delete []b2;
    delete []b3;

    return 0;
}

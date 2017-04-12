#include <iostream>

using namespace std;

struct Exception
{
    int n;
    Exception(int n) : n(n) {}
    ~Exception()
    {
        cout << "Adios" << endl;
    }
    Exception(const Exception &e)
    {
        n = e.n;
        cout << "copy" << endl;
    }
};

struct Int
{
    int n;

    void show() const
    {
        cout << n << endl;
    }

    ~Int()
    {
        cout << "Die" << endl;
    }
};

void r()
{
    cout << ":P" << endl;
    //throw 3.1415;
    /* int* x = nullptr;
    *x = 25;*/
    /*Int* z = nullptr;
    z->show();*/
    int a = 1;
    int b = a - 1;
    cout << (a / b) << endl; //SEH exceptions
}

void q()
{
    cout << "Hi" << endl;
    r();
    cout << "Bye" << endl;
}

void p()
{
    q();
}

void m()
{
    /*auto p = new Int{25};
    try
    {
        throw 10;
        p->show();
        delete p;
    }
    catch(...)
    {
        delete p;
        throw;
    }*/
    Int p {25};
    throw 10;
    p.show();
}

void X2()
{
    cout << "Hello Thuesday" << endl;
    throw Exception {48};
}

int main()
{
    /*try
    {
        p();
    }
    catch(int x) // (...) <--- Para cualquier valor lanzado por el throw
    {
        cerr << "Error: " << x << endl;
    }
    catch(const char* s)
    {
        cerr << s << endl;
    }
    catch(double d)
    {
        cerr << d << endl;
    }
    catch(...)
    {
        cerr << "OUCH" << endl;
    }

    cout << "END" << endl;*/

    try
    {
        m();
    }
    catch(...)
    {
        cerr << "Error" << endl;
    }

    try
    {
        X2();
    }
    catch(const Exception &e)
    {
        cerr << "Error: " << e.n << endl;
    }
    catch(...)
    {
        cerr << "Oops" << endl;
    }

    return 0;
}

#include <iostream>

using namespace std;

struct point
{
    private:
        int y;
        int x;

    public:
point(int x, int y) : y(y), x(x)//Initialization list
    {
        cout << "Point: " << endl;
    }

    ~point()
    {
        cout << "Goodbye cruel world!!" << endl;
    }

    point(const point &src) : y {src.y}, x {src.x}
    {
        cout << "Copy" << endl;
    }

    /*point(int x, int y) //Hidding
    {
        cout << "Point: " << endl;
        this->x = x; // (*this).
        this->y = y; // (*this).
    }*/

    /*point()
    {
        cout << "Ini Point" << endl;
        x = y = 0;
    }*/

    point():point(0 ,0) {}

    void show() const //constant method, tip declare all method constant
    {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};

/*void show(const point &x)
{
    cout << "(" << x.x << ", " << x.y << ")" << endl;
}*/

int main()
{
    /*point p;
    p.x = 8;
    p.y = 5;
    show(p);*/

    point q {15, 23}; // from c++ 11, no construct, pttas. publics
    q.show();

    point r = q; //copy
    r.show();

    r = q; //assignment
    r.show();

    return 0;
}

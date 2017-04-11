#include <iostream>

using namespace std;

class point
{
    int x, y;
    public:
        point(int x, int y)
            : x(x), y(y)
            {

            }
        friend void show(const point &);
        friend ostream &operator<<(ostream &os, const point &p);
};

class Barbie
{
    void sayHi() { cout << "Hi" << endl; }
    void sayBye() { cout << "Bye" << endl; }
    friend class BarbieFriend;
};

class BarbieFriend
{
    public:
    void greet()
    {
        Barbie b;
        b.sayHi();
        b.sayBye();
    }
};

void show(const point &p)
{
    cout << "(" << p.x << ", " << p.y << ")" << endl;
}

ostream &operator<<(ostream &os, const point &p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

int main()
{
    cout << "Hello world!" << endl;

    point p {6, 8};
    //show(p);
    cout << p << endl;

    BarbieFriend bff;
    bff.greet();

    return 0;
}

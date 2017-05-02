#include <iostream>
#include <memory>

using namespace std;

struct A
{
    int* a;
    int* b;

    A(int* a, int* b) : a(a), b(b) {}
};

struct ADelete
{
    void operator()(A* x) const
    {
        cout << "Bye A\n";
        delete x->a;
        delete x->b;
    }
};

struct point3D
{
    int x, y, z;

    point3D(int x, int y, int z) : x(x), y(y), z(z) {}

    void show() const
    {
        cout << x <<  "; " << y << "; " << z << endl;
    }

    ~point3D()
    {
        cout << "Bye ";
        show();
    }
};

int main()
{
    //auto x = make_unique<A>(new int(10), new int(10));
    unique_ptr<A, ADelete> x{ new A(new int(20), new int(40)) };

    cout << *(x->b) << endl;

    /*auto a = new point3D(3, 4, 5);
    auto b = new point3D(6, 7, 8);
    auto c = new point3D(9, 0, 1);
    auto d = c;
    auto e = new point3D(1, 1, 1);
    b = a;
    d = c;
    e = nullptr;
    a = new point3D(2, 2, 2);

    delete a;
    delete b;
    delete c;
    delete d;
    delete e;*/

    shared_ptr<point3D> a{ new point3D(3, 4, 5) };
    auto b = make_shared<point3D>(6, 7, 8);
    auto c = make_shared<point3D>(9, 0, 1);
    b = a;
    auto d = c;
    auto e = nullptr;
    a = make_shared<point3D>(1, 2, 1);

    return 0;
}

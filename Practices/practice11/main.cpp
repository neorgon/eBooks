#include <iostream>

using namespace std;

struct Animal
{
    virtual ~Animal() {};
    virtual void Say_something() const = 0;
};

struct Dog : Animal
{
    void Say_something() const override
    {
        cout << "Woff, Woff" << endl;
    }
};

struct Cat : Animal
{
    void Say_something() const override
    {
        cout << "Meow, Meow" << endl;
    }
    void Scratch() const
    {
        cout << "Scratching" << endl;
    }
};

void work(const Animal* a)
{
    a->Say_something();
    const Cat* c = dynamic_cast<const Cat*>(a);
    if (c != nullptr)
        c->Scratch();
}

int main()
{
    Dog d;
    Cat c;

    work(&d);
    work(&c);

    return 0;
}

/*
class Shape
{
    protected:
        Shape() {}

    public:
        virtual double Get_area() const = 0;
};

class Circle: public Shape
{
    double r;

    public:
        Circle(double r) : r(r)
        {

        }
        double Get_area() const override
        {
            return r * r *3.14159;
        }
};

int main()
{
    Circle c{5};
    auto d = new Circle{8};
    Shape* e = new Circle {10};
    Shape &g = *e;

    int* i;
    int in = 5;

    i = &in;

    cout << e->Get_area() << endl;
    cout << g.Get_area() << endl;

    cout << *i << endl;

    delete d;
    delete g;

    return 0;
}
*/

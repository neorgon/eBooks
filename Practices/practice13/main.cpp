#include <iostream>

using namespace std;

struct dormir
{
    void duerme()
    {
        cout << "ZZZ\n";
    }
};

struct comer
{
    void come()
    {
        cout << "Crunch Crunch\n";
    }
};

struct perro: dormir, comer
{

};

class vehicle
{
    size_t max_speed;

    public:
        vehicle(size_t ms) : max_speed(ms) {};

        void move()
        {
            cout << "I'm moving\n";
        }
};

class animal
{
    public:
        void eat()
        {
            cout << "I'm eating\n";
        }
};

class flier
{
    public:
        void fly()
        {
            cout << "I'm flying\n";
        }
};

class swimmer
{
    public:
        void swim()
        {
            cout << "I'm swimming\n";
        }
};

class airplane: public vehicle, public flier
{
    public:
        airplane(size_t ms) : vehicle {ms} {};
};

class hawk: public animal, public flier
{

};

class duck: public animal, public swimmer
{

};

void test(flier &r)
{
    cout << "****\n";
    r.fly();
}

struct A
{
    void p()
    {
        cout << "hello\n";
    }

    void q()
    {
        cout << "Cucuruchu\n";
    }
};

struct B
{
    void p()
    {
        cout << "hola\n";
    }
};

struct C:A, B
{
    void p()
    {
        //cout << "Good by cruel world!\n";
        B::p(); //funciona por que está explícito
    }
};


//Dredd Diamond Problem
struct X
{
    int x;
    void s()
    {
        cout << ":P\n";
    }
    int get()
    {
        return x;
    }
};

struct Y:X
{

};

struct Z:X
{

};

struct XX:Y, Z
{
    int get()
    {
        return Y::get();
    }
};

int main()
{
    /*perro p;
    p.come();
    p.duerme();
    duck d;
    d.eat();
    d.swim();
    airplane r {1000};
    r.fly();
    r.move();
    hawk h;
    h.eat();
    h.fly();
    test(h);
    test(r);*/
    //C c;
    //c.q();
    //c.p()  // funciona por ocultamiento
    //c.A::p();
    XX m;
    /*m.Y::x = 18;
    m.Z::x = 35;

    cout << m.Y::x << endl;
    cout << m.Z::x << endl;

    m.Y::s();
    m.Z::s();

    cout << m.Y::get() << endl;
    cout << m.Z::get() << endl;*/

    m.Y::x = 60;
    cout << m.get() << endl;
    //cout << m.Z::get() << endl;

    return 0;
}

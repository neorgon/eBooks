#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct IShape
{
    ~IShape() { cout << "bye\n"; }
    virtual void p() = 0;
};

struct Rectangle: IShape
{
    void p() override
    {
        cout << "Rect\n";
    }
};

struct Circle: IShape
{
    void p() override
    {
        cout << "Circ\n";
    }
};

IShape* get(int n)
{
    if (n % 2)
        return new Circle();
    else
        return new Rectangle();
}

int main()
{
    vector<unique_ptr<IShape>> ss;
    for (int i = 0; i < 10; i++)
    {
        ss.push_back(unique_ptr<IShape>(get(i)));
    }

    ss[3]->p();
    ss[6]->p();
    auto &m = ss[5];
    m->p();

    return 0;
}

/*struct N
{
    int n;
    N(int n) : n{n} { cout << "Hi: " << n << endl; }
    ~N() { cout << "Bye " << n << endl; }
};

struct Pair
{
    unique_ptr<N> a;
    unique_ptr<N> b;
    /*
    N* a;
    N* b;
    */
/*    Pair(int x, int y) : a(new N {x}), b(new N {y}) { throw 666; }
    void Show() const
    {
        cout << a->n << ", " << b->n << endl;
    }
    ~Pair()
    {
        cout << "Bye pair\n";
        /*delete a;
        delete b;*/
/*    }
};

int main()
{
    /*auto n = new N { 10 };
    cout << n->n << endl;
    delete n;*/

    //unique_ptr <N> n { new N {15}};
/*    auto n = make_unique<N>(15);
    cout << n->n << endl;
    cout << (*n).n << endl;
    cout << n.get() << endl;

    /*auto p = move(n);

    cout << n.get() << endl;*/
/*    try
    {
        auto p = make_unique<Pair>(2, 5);
        p->Show();
        Pair q {6,9};
        q.Show();
    }
    catch(...)
    {
        cerr << "ERROR\n";
    }

    return 0;
}
*/

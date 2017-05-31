#include <iostream>
#include <memory>

using namespace std;

struct son;

struct father
{
    shared_ptr<son> s;
    void say() { cout << "I'm your father Luck\n"; }
    ~father() { cout << "Bye father\n"; }
};

struct son
{
    weak_ptr<father> f;
    ~son() { cout << "Bye son\n"; }
};

int main()
{
    /*auto ff = make_shared<father>();
    auto ss = make_shared<son>();

    ff->s = ss;
    ss->f = ff;
    ss->f.lock()->say();*/

    auto ss = make_shared<son>();
    {
        auto ff = make_shared<father>();
        ss->f = ff;
        ff->s = ss;
        ss->f.lock()->say();
    }
    cout << "*****\n";
    cout << ss->f.expired() << endl;

    return 0;
}

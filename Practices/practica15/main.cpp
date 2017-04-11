#include <iostream>
#include <typeinfo>
#include <string>

using namespace std;

class Father
{
    public:
        virtual ~Father(){};
};

class Son:public Father
{

};

struct A
{
    int a;
    explicit A(int a): a(a){}
    A(const A &) = delete;
    A &operator=(const A &) = delete;
};

int main()
{
    cout << "Hello world!" << endl;
    Father f1, f2;
    Son s;

    if (typeid(f1) == typeid(f2))
    {
        cout << "Iguales" << endl;
    }

    if (typeid(f1) != typeid(s))
    {
        cout << "Son diferentes" << endl;
    }

    cout << typeid(f2).name() << endl;
    cout << typeid(s).name() << endl;

    Father* f4 = new Son();

    cout << typeid(f4).name() << endl;
    cout << typeid(*f4).name() << endl;

    const type_info &str = typeid(string);

    cout << str.name() << endl;

    A a {10};
    A b {27};
    A c {8};
    //c = b;

    cout << c.a << endl;

    return 0;
}

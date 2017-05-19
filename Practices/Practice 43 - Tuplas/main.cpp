#include <iostream>
#include <tuple>

using namespace std;
using namespace std::string_literals;

template<size_t N, typename X>
struct tuple_show
{
    const X& x;
    void show() const
    {
        cout << get<N>(x) << "\n";
        tuple_show<N - 1, X> ts {x};
        ts.show();
    }
};

template <class X>
struct tuple_show<0, X>
{
    const X& x;
    void show() const
    {
        cout << get<0>(x) << "\n";
    }
};

template <typename ... T>
void show(const tuple<T ...> &t)
{
    using my_tuple = tuple<T ...>;
    constexpr auto sz = tuple_size<my_tuple>::value;

    cout << get<sz - sz>(t) << "\n";
    //tuple_show <sz - 1, my_tuple> ts {t};
    //ts.show();
}

class Person
{
    string name;
    int ci;

    public:
        Person(int ci, const string &name) : name{name}, ci{ci} {}
        void show() const
        {
            cout << name << ", " << ci << "\n";
        }
};

int main()
{
    tuple<int, int, int> ps {6, 8, 14}; //c++11

    cout << get<0>(ps) << "\n";
    cout << get<1>(ps) << "\n";
    cout << get<2>(ps) << "\n";

    tuple<char, int, string> q {'a', 2, "hello"};

    cout << get<string>(q) << "\n"; //c++14

    auto r = make_tuple(10, "abejas"s);
    auto s = make_tuple(10, "cabras"s);

    if(r < s)
        cout << "r es menor" << "\n";

    auto u = make_tuple(1, 2, 3, 8, 5, 14);
    auto sz = tuple_size<decltype(u)>::value;

    cout << sz << "\n";

    auto f = make_tuple(2, 8, "hello"s);
    auto g = make_tuple("hola", "mundo", 1, 2, 3);

    show(f);
    show(g);

    auto z1 = make_tuple(123458, "Bon Jovi");
    auto p = make_from_tuple<Person>(z1);
    p.show();

    return 0;
}

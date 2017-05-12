#include <iostream>
#include <string>
#include <set>

using namespace std;

void p(int n)
{
    cout << n << "\n";
}

void s(int x, int y, int& z)
{
    z = x + y;
}

template <typename Proc, typename ... ARGS>
auto invoke(Proc x, /*const*/ ARGS&& ... args)
{
    x(forward<ARGS>(args) ...);
}

int main()
{
    invoke(p, 6);
    int r;
    invoke(s, 6, 15, r);
    cout << r << "\n";
}

/*
template <typename T>
void populate(T&)
{

}

template<class T, class V, class ... Z>
void populate(T& x, const V& a, const Z& ... z)
{
    x.insert(a);
    populate(x, z ...);
}

template <typename T, typename ... ARGS>
void my_sort(const ARGS& ... args)
{
    set<T> s;

    populate(s, args ...);

    for (auto &i : s)
        cout << i << "\n";
}

int main()
{
    my_sort<int>(6, 8, 4, 1, 5, 9);
    my_sort<string>("hello"s, "today"s, "is"s, "friday"s);
}
*/
/*
template <typename T>
T sum(const T& a, const T&b)
{
    return a + b;
}

template <typename T, typename ... ARGS> // ARGS parameter pack
T sum(const T &a, const ARGS& ... args)
{
    return a + sum(args ...);
}

int main()
{
    int x = sum(2, 4);
    auto y = sum(3.6, 8.9);
    int z = sum(6, 8, 9, 14);
    int a = sum(1, 2, 3);

    cout << x << "\n";
    cout << y << "\n";
    cout << z << "\n";
    cout << a << "\n";

    return 0;
}

*/

#include <iostream>
#include <string>

using namespace std;
using namespace std::string_literals;

/*int sum(int a, int b)
{
    return a + b;
}

double sum(double a, double b)
{
    return a + b;
}*/

template <typename T, class U>
//template <class T>
auto sum(T a, U b)->decltype(a + b)
{
    return a + b;
}

struct Int
{
    int n;
};

Int operator+(Int a, Int b)
{
    return Int{a.n + b.n};
}

template <int N>
int factorial()
{
    /*if(N == 1)
        return 1;
    return N * factorial<N - 1>();*/
    int r = 1;
    for (int i = N; i > 1; i--)
        r *= i;
}

int main()
{
    /*auto p = sum(4, 8);
    cout << p << endl;
    auto q = sum(8.2, 3.1);
    cout << q << endl;
    auto c = sum('a', 'b');
    cout << c << endl;
    auto r = sum(8.2, 3);
    cout << r << endl;
    auto s = sum("hello "s, "world");
    cout << s << endl;
    auto v = sum<string, string>("hello ", "world");
    cout << v << endl;
    auto z = sum(Int{2}, Int{5});
    cout << z.n << endl;*/

    cout << factorial<5>() << endl;
    cout << factorial<6>() << endl;

    return 0;
}

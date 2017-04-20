#include <iostream>
#include <vector>

using namespace std;

template <class T, class P>
void process(vector<T> &x, P p)
{
    for (auto &i : x)
        p(i);
}

int main()
{
    //vector<string> x { "lunes", "martes", "miercoles", "jueves", "viernes", "sabado", "domingo" };
    vector<int> x {6, 7, 8, 9, 0};
    process(x, [](auto &s)
    {
        cout << s << endl;
    });
    bool par = false;
    int n = 0;
    process(x, [par, &n](auto &s)
    {
        if(n % 2 == !par)
            cout << s << endl;
        n++;
    });

    return 0;
}

/*
#include <iostream>

using namespace std;

auto main()->int
{
    //auto f = [](const string &s)
    //void (*f)(const string &) = [](const string &s)->void
    auto f = [](const auto &s)->void
    {
        cout << s << endl;
    };
    f("hello");
    f(12);

    return 0;
}
*/

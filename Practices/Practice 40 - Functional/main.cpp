#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;
using namespace std::placeholders;

int p(int a, int b)
{
    return a * b;
}

void q(int n)
{
    cout << n + 1 << "\n";
}

void maxx(int a, int b)
{
    if (a > b) cout << a << "\n";
    else cout << b << "\n";
}

void pr(const string &a, const string &b, const string &c)
{
    cout << a << " es mejor que " << b << " y es mejor que " << c << "\n";
}

void invertir(string &s)
{
    reverse(s.begin(), s.end());
}

int main()
{
    /*function <int(int, int)>
    f = p;
    cout << f(7, 8) << "\n";*/
    //vector <void(*)(int)> fs;
    vector <function<void(int)>> fs;
    fs.push_back(q);
    fs.push_back([](int p)
    {
        if (p % 2 == 0) cout << "PAR\n";
        else cout << "IMPAR\n";
    });
    int m = 25;
    fs.push_back([m](int n)
    {
        cout << m + n << "\n";
    });
    auto mb = bind(maxx, 10, _1);
    fs.push_back(mb);
    for (auto& i : fs)
        i(15);

    vector<function<decltype(pr)>> ff;
    ff.push_back(pr);
    ff.push_back(bind(pr, _1, _3, _2));
    ff.push_back(bind(pr, _3, _2, _1));
    ff.push_back(bind(pr, _2, _1, _3));
    for (auto& i : ff)
        i("Cocha", "Potosi", "Oruro");

    string z = "lostiempos";
    auto f = bind(invertir, ref(z));
    f();
    cout << z << "\n";

    return 0;
}

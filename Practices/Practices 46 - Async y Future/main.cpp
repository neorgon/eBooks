#include <iostream>
#include <string>
#include <algorithm>
#include <future>

using namespace std;

template <typename T>
int minifind(int posi, int len, const vector<T> &x, const T &u, atomic<bool> &f)
{
    for (int i = posi; i < posi + len; i++)
    {
        if (x[i] == u)
        {
            f = true;
            return i;
        }
        if (f) return -1;
    }

    return -1;
}

template <typename T>
int find(const vector<T> &x, const T &u, size_t nz = 10)
{
    auto slice = x.size() / nz;
    vector<future<int>> rs;
    atomic<bool> found = false;
    for (auto i = 0; i < nz; i++)
    {
        rs.push_back(async(minifind<T>, i *slice, slice, ref(x), ref(u), ref(found)));
    }

    for (auto i = 0; i < nz; i++)
    {
        auto v = rs[i].get();
        if (v != -1)
            return v;
    }

    return 1;
}

int main()
{
    vector<int> x;

    for (int i = 0; i < 10000000; i++)
        x.push_back(i);

    auto t0 = clock();
    int index = find(x, 9000000);
    cout << index << "\n";
    auto t1 = clock();
    cout << "Time: " << (t1- t0) << "\n";
}

/*
bool inc(int &a)
{
    a++;

    return true;
}

int main()
{
    auto n = 9, m = 10, y = 4;

    auto p1 = async(inc, ref(n));
    auto p2 = async(inc, ref(m));
    auto p3 = async(inc, ref(y));

    p1.get();
    p2.get();
    p3.get();

    cout << n << "\n";
    cout << m << "\n";
    cout << y << "\n";
}
*/

/*string invertir(const string &s)
{
    auto r = s;
    reverse(r.begin(), r.end());
    cout << r << " invertido\n";

    return r;
}

int main()
{
    future<string> x = async(invertir, "martes");
    auto y = async(invertir, "fundacion jala");
    auto z = async(invertir, "willstermann");

    cout << x.get() << "\n";
    cout << y.get() << "\n";
    cout << z.get() << "\n";

    return 0;
}
*/

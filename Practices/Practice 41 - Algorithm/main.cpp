#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

using namespace std;

template<typename I, typename P>
auto get_elems(I first, I last, P p)
{
    using Type = typename remove_reference<decltype(*first)>::type;
    vector<Type> r;
    for (I i = first; i != last; ++i)
    {
        if (p(*i) == true)
        {
            r.push_back(*i);
        }
    }

    return r;
}

int main()
{
    vector<int> y {6,9,2,5,4,8};
    vector<string> ms = { "juan", "jesus", "maria", "jorge", "omar", "mauricio", "eva", "jaime", "guillermo" };

    auto it = find(y.begin(), y.end(), 5);
    if (it == y.end())
        cerr << "NO FOUND\n";
    else
        cout << "FOUND\n";

    auto it2 = find_if(y.begin(), y.end(), [](auto n){ return n < 5; });

    if (it2 == y.end())
        cerr << "NOT FOUND\n";
    else
        cout << "FOUND\n";

    auto n = count_if(ms.begin(), ms.end(), [](auto &p)
    {
        return p[0] == 'j';
    });

    cout << n << "\n";

    sort(ms.begin(), ms.end());
    auto b = binary_search(ms.begin(), ms.end(), "guillermo");

    cout << b << "\n";

    auto x = get_elems(ms.begin(), ms.end(), [](auto &s)
    {
        return s[0] == 'j';
    });
    for (auto &e : x)
        cout << e << "\n";

    auto yy = get_elems(y.begin(), y.end(), [](int n){ return n % 2 == 0; });
    for (auto &e : yy)
        cout << e << "\n";

    return 0;
}

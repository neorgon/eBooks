#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> x { 10, 7, 2, 8, 9 };
    for_each(x.begin() + 1, x.end() - 2,
            [](auto &i)
            {
                if (i % 2 == 0)
                    cout << i << endl;
            });

    vector<string> y { "one", "two", "three", "four", "five" };
    bool ascending = false;
    sort(y.begin(), y.end(),
        [ascending](auto &a, auto &b)
        {
            if (ascending) return a < b;
            return b < a;
        });

    for (auto &i : y)
        cout << i << endl;

    return 0;
}

#include <iostream>

using namespace std;

struct sumador
{
    template <class T>
    T operator()(T a, T b) const
    {
        return a + b;
    }
};

int sub(int x, int y)
{
    return x - y;
}

template <typename Proc, class T, class U>
void exec(Proc p, const T &a, const U &b)
{
    cout << p(a, b) << endl;
}

int main()
{
    sumador s;

    cout << s(5 , 16) << endl;
    cout << s(3.45 , 8.19) << endl;

    exec(s, 25, 18);
    exec(sub, 20, 10);

    return 0;
}

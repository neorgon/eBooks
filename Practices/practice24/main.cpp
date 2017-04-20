#include <iostream>

using namespace std;

template<class A, class B>
struct X
{
    A a;
    B b;

    void show() const
    {
        cout << a << endl << b << endl;
    }
};
template<class T>
struct X<string, T>
{
    string x;
    T y;
    void show() const
    {
        cout << "X: " << x + to_string(y) << endl;
    }
};
template<>
struct X<int, int>
{
    int m, n;
    void show() const
    {
        cout << m + n << ":::\n";
    }
};

int main()
{
    X<int, double> x {6, 8.3};
    x.show();

    X<string, int> y {"hello", 19};
    y.show();

    X<int, int> z {1, 3};
    z.show();
}

/*
#include <iostream>

using namespace std;

template<int N>
int factorial()
{
    return N * factorial<N - 1>();
}
template<>
int factorial<1>()
{
    return 1;
}

template<int N>
struct xf
{
    static const int value = N * xf<N-1>::value;
};
template<>
struct xf<1>
{
    static const int value = 1;
};

template<class T>
struct Wrapper
{
    T elem;
    const T &get() const {return elem;}
};
template<class T>
struct Wrapper<T*>
{
    T* elem;
    const T& get() const
    {
        return *elem;
    }
    ~Wrapper()
    {
        cout << "Bye" << endl;
        delete elem;
    }
};

int main()
{
    cout << factorial<6>() << endl;
    cout << xf<7>::value << endl;

    Wrapper<int> x {2};
    Wrapper<string> y {"hello"};
    cout << x.get() << endl;
    cout << y.get() << endl;
    Wrapper<int *> z {new int {16}};
    Wrapper<string *> m {new string("abril")};
    cout << z.get() << endl;
    cout << m.get() << endl;
}
*/
/*
#include <iostream>
#include <vector>

using namespace std;

template<class T>
ostream &operator<<(ostream &os, const vector<T> &x)
{
    for (auto &i : x)
        os << i << "\n";
    return os;
}

template<class E>
void sum(E e1, E e2)
{
    cout << e1 + e2 << endl;
}
template<>
void sum<vector<string>>(vector<string> a, vector<string> b)
{
    vector<string> r = a;
    for (auto &i : b)
        r.push_back(i);
    cout << r << endl;
}
template<>
void sum<double>(double a, double b)
{
    cout << "DOUBLE: " << a + b << endl;
}

int main()
{
    sum(6, 8);
    sum(3.4, 6.5);
    sum<string>("hello", " world");
    sum(vector<string>{"monday", "tuesday"}, vector<string>{"thursday", "friday"});
    return 0;
}
*/

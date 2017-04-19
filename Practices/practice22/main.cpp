#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

struct msg
{
    string s;
    void operator()(size_t a, size_t b)
    {
        cout << s << ": " << a << " " << b << endl;
    }
};

void mul(int a, int b)
{
    cout << a * b << endl;
}

void sub(int a, int b)
{
    cout << a - b << endl;
}

void add(int a, int b)
{
    cout << a + b << endl;
}

void show_progres(size_t n, size_t m)
{
    cout << n << " of " << m << "finished" << endl;
}

/*void do_something(size_t n, void(*p)(size_t, size_t))
{
    for (auto i = 0U; i < n; i++)
    {
        if (i % 10000 == 0)
        {
            p(i, n);
        }
    }
}*/

template <class P>
void do_something(size_t n, P p)
{
    for (auto i = 0U; i < n; i++)
    {
        if (i % 10 == 0)
        {
            p(i, n);
        }
    }
}

int cpint(const void* a, const void* b)
{
    auto aa = (int*)a;
    auto bb = (int*)b;

    return *aa - *bb;
}

int main()
{
    //auto m = mul;
    /*void(*m)(int, int) = mul;
    m(10, 20);

    vector<void(*)(int, int)> fs;
    fs.push_back(mul);
    fs.push_back(sub);
    fs.push_back(add);

    for (auto &i : fs)
    {
        i(50, 25);
    }*/

    msg m { "Hello" };
    do_something(100, m);
    //do_something(10000000, show_progres);

    int arr[] = {6, 8, 9, 21, 3, 9, 1, 0};
    qsort(arr, 8, sizeof(int), cpint);

    for (auto &i : arr)
    {
        cout << i << endl;
    }

    string* ns[] = { new string {"juan prado"}, new string {"pedro blanco"}, new string {"eva longoria"} };

    qsort(ns, 3, sizeof(string*), [](const void* a, const void* b)
          {
              auto aa = (string**) a;
              auto bb = (string**) b;

              return (*aa)->compare(**bb);
          }
    );

    for (auto &i : ns)
    {
        cout << *i << endl;
    }


    return 0;
}

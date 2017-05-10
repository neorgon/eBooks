#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

struct data
{
    char* s;
    size_t n;

    data(char k, size_t n) : s { new char[n] }, n {n}
    {
        memset(s, k , n);
    }

    data(const data &src) : s { new char[src.n] }, n {src.n}
    {
        memcpy(s, src.s, n);
    }

    data &operator=(const data &src)
    {
        delete[] s;
        s = new char[src.n];
        n = src.n;
        memcpy(s, src.s, n);

        return *this;
    }

    //MOVE CONSTRUCTOR
    data(data &&src) : s {src.s}, n {src.n}
    {
        //cout << "Hi \n";
        src.s = nullptr;
    }

    data &operator=(data && src)
    {
        //cout << "Hi\n";
        delete[] s;
        s = src.s;
        n = src.n;
        src.s = nullptr;

        return *this;
    }

    ~data() { delete [] s; }
};

data get_data(char k)
{
    return data {k, 1'000'000};
}

template <typename T>
//void process {data x}
void process(T&& x)
{
    cout << x.s[0] << "\n";
}

void sw(data &a, data &b)
{
    data c = move(a);
    a = move(b);
    b = move(c);
}

int main()
{
    /*clock_t t0 = clock();
    data d{'a',2};
    for (auto i = 0U; i < 1000; i++)
    {
        d = get_data('b');
    }
    auto tz = clock();
    cout << "TIME: " << (tz - t0) << "\n";*/

    data d1 {'b', 1'000'000};
    process(d1);
    process(data{'m',10});

    auto t0 = clock();
    data x{'x', 1'000'000};
    data y{'y', 10'000'000};
    for (auto i = 0; i < 1001; i++)
        sw(x,y);
    auto ta = clock();

    cout << "TIME: " << (ta - t0) << "\n";

    return 0;
}

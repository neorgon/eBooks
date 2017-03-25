#include <iostream>

using namespace std;

class binary
{
    uint16_t n;

    public:
        binary(const string &s) : n{0}
        {
            if(s.length() > 16) return;
            int p = 1;
            for(auto i = s.rbegin(); i != s.rend(); ++i, p *= 2)
            {
                char b = *i;
                if(b == '0') continue;
                if(b == '1') n += p;
                else
                {
                    n = 0;
                    return;
                }
            }
        }

        binary(uint16_t n) : n{n} {}

        uint16_t to_decimal() const
        {
            return n;
        }

        bool operator==(const binary &b) const
        {
            return n == b.n;
        }

        bool operator==(uint16_t x) const
        {
            return n==x;
        }

        binary operator+(const binary &b) const
        {
            return binary{(uint16_t)(n + b.n)};
        }

        binary &operator+=(const binary &b)
        {
            n += b.n;

            return *this;
        }

        binary &operator++()
        {
            n++;

            return *this;
        }

        binary operator++(int)
        {
            binary b{n};
            n++;

            return b;
        }

        void show() const
        {
            cout << n << endl;
        }

};

bool operator==(uint16_t x, const binary &b)
{
    return x == b.to_decimal();
}

int main()
{
    binary b {"101101"};
    binary d = b;
    binary c {"100110"};
    auto e = b + c;

    cout << b.to_decimal() << endl;
    cout << c.to_decimal() << endl;
    if(d == b)
        cout << "Iguales" << endl;
    else
        cout << "Diferentes" << endl;

    cout << e.to_decimal() << endl;

    binary e1 {"101"};
    binary e2 {"110"};

    auto e3 = e1 + e2;

    cout << e3.to_decimal() << endl;

    cout << (e3 += binary {"1000"}).to_decimal() << endl;

    (++e3).show();

    (e3++).show();

    e3.show();

    /*
    auto d = b + c;
    b = ~b;

    binary e {"110"};

    */
    return 0;
}

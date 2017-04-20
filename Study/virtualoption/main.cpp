#include <iostream>

using namespace std;

class IOption
{
    public:
        virtual void Value() const
        {
            cout << "IOption: Type?" << endl;
        }
};

class OInteger : public IOption
{
    public:
        void Value() const
        {
            cout << "OInteger: Integer?" << endl;
        }
};

class OReal : public IOption
{
    public:
        void Value() const
        {
            cout << "OReal: Real?" << endl;
        }
};

void get(IOption &o)
{
    o.Value();
}

int main()
{
    OInteger integer;
    integer.Value();
    OReal real;
    real.Value();

    return 0;
}

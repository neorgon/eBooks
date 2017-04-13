#include <iostream>

using namespace std;

enum otype { Integer, Real };

class IOption
{
    public:
        virtual void Value(otype) const
        {
            cout << "IOption: Type?" << endl;
        }
};

class OInteger : public IOption
{
    public:
        void Value(otype) const
        {
            cout << "OInteger: Integer?" << endl;
        }
};

void get(IOption &o)
{
    o.Value(Integer);
}

int main()
{
    OInteger option;
    get(option);

    return 0;
}

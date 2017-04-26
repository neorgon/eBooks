#include <iostream>

using namespace std;

template <class T>
class Value
{
    public:
        //Value();
        virtual T getValue() = 0;
        virtual void setValue(T val) = 0;
};


class IntValue : public Value<int>
{
    public:
        //IntValue();

        int getValue() {return _val;}
        void setValue(int val) {_val = val;}
    private:
        int _val;
};

int main()
{
    IntValue x;
    x.setValue(2);
    cout << x.getValue() << endl;

    return 0;
}

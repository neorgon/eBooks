#include <iostream>
#include <string>

using namespace std;

struct Object
{
    Object(int) {};
    virtual ~Object() {}
    virtual string to_string() const = 0;
};

struct Number : virtual Object
{
    Number() : Object(0) {}
    virtual void inc() = 0;
};

struct IComparable: virtual Object
{
    IComparable() : Object(0) {}
    virtual int compare_to(const Object &o) const = 0;
};

struct Integer final: Number, IComparable
{
    int n;
    Integer(int n) : Number(), IComparable(), Object(0), n(n) {}
    string to_string() const override
    {
        return std::to_string(n);
    }
    void inc() override { n++; }
    int compare_to(const Object &o) const override
    {
        auto &i = dynamic_cast<const Integer &>(o);
        return n - i.n;
    }
};

int main()
{
    auto p = new Integer(10);
    p->inc();
    IComparable* q = new Integer(8);
    cout << p->to_string() << endl;
    cout << q->to_string() << endl;
    cout << q->compare_to(*p) << endl;

    return 0;
}

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Person
{
    string fn;
    string ln;

    Person(const string &fn, const string &ln) : fn(fn), ln(ln)
    {
        static size_t n = 0;
        cout << "N: " << (++n) << "\n";
    };

    virtual void Show() const
    {
        cout << fn << " " << ln << endl;
    }

    virtual ~Person() {};
};

struct Employee : Person
{
    string role;

    Employee(const string &fn,
             const string &ln,
             const string &role) : Person {fn, ln}, role {role}
    {

    }

    void Show() const override
    {
        cout << fn << " " << ln << ", " << role << endl;
    }
};

int main()
{
    /*vector<Person> ps;

    ps.push_back(Person{"juan", "perez"});
    ps.push_back(Person{"eva", "morales"});
    ps.push_back(Person{"lionel", "messi"});

    Person q {"alvaro", "garcia"};
    ps.push_back(q);

    for (Person &p : ps)
        p.Show();*/

    vector<Person*> qs;

    qs.push_back(new Employee{"Omar", "Vera", "QA"});
    qs.push_back(new Person{"Oscar", "Gonzales"});
    qs.push_back(new Employee{"Romulo", "Rojas", "Bigboss"});

    for (auto &q : qs)
        q->Show();

    for (auto &q : qs)
        delete q;

    return 0;
}

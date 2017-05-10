#include <iostream>
#include <vector>

using namespace std;

struct people
{
    vector<string>* p;

    people() : p(new vector<string>())
    {
        cout << "Const\n";
    }
    ~people() { delete p; }

    void add(const string& s)
    {
        p->push_back(s);
    }
    people(const people &src) : p(new vector<string>())
    {
        cout << "CopyCons\n";
        for (auto &i : *(src.p))
            p->push_back(i);
    }
    people &operator=(const people &src)
    {
        delete p;
        p = new vector<string>();
        for (auto &i : *(src.p))
            p->push_back(i);

        return *this;
    }
    people(people&& src) : p(src.p)
    {
        cout << "Move\n";
        src.p = nullptr;

    }
    people &operator=(people&& src)
    {
        delete p;
        p = src.p;
        src.p = nullptr;

        return *this;
    }
};

class groups
{
    people men;
    people women;

    public:
        groups(const people& m, const people &w) : men(m), women(w)
        {
            cout << "GCons";
        }
        /*groups(people&& m, people&& w) : men {move(m)}, women {move(w)}
        {
            cout << "GMove\n";
        }*/
        template<typename P, typename Q>
        groups(P&& m, Q&& w) : men {forward<P>(m)}, women {forward<Q>(w)}
        {
            cout << "PFCons\n";
        }
};

int main()
{
    people men;
    men.add("mike hammer");
    men.add("alice cooper");
    people women;
    women.add("lady gaga");
    women.add("mary curie");
    groups g {men, women};
    groups h {people{}, people{}};
    groups j {people{}, women};
    groups k {men, people{}};

    return 0;
}

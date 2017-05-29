#include <iostream>
#include <list>
#include <memory>

using namespace std;

struct node
{
    int value;
    list<shared_ptr<node>> my_list;
};

class my_nodes
{
    node root;

    void to_print(const list<shared_ptr<node>> &l) const;

    public:
        my_nodes(int v) { root.value = v; }
        node create(int v) const;
        void add(node &n);
        void to_print() const;
};

node my_nodes::create(int v) const
{
    node e;

    e.value = v;

    return e;
}

void my_nodes::add(node &n)
{
    root.my_list.push_back(make_shared<node>(n));
}

void my_nodes::to_print() const
{
    cout << root.value << " ";
    if (root.my_list.size())
        to_print(root.my_list);
}

void my_nodes::to_print(const list<shared_ptr<node>> &l) const
{
    if (l.size())
        for (auto &i : l)
        {
            cout << i->value << " ";
            to_print(i->my_list);
        }
}

int main()
{
    my_nodes n { 1 };

    auto a = n.create(2);
    auto b = n.create(3);

    n.add(a);
    n.add(b);

    n.to_print();

    return 0;
}

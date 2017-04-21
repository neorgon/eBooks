#include <iostream>
#include <string>

using namespace std; //(RojoNegro)

template<class T>
struct default_less
{
    bool operator()(const T &a, const T &b) const
    {
        return a < b;
    }
};

template<class T, class Compare = default_less<T>>
class bst
{
    struct bst_node
    {
        T elem;
        bst_node* left;
        bst_node* right;
    };
    bst_node* root;
    Compare cmp;

    void add(bst_node* &node, const T &n)
    {
        if (node == nullptr)
        {
            node = new bst_node{n, nullptr, nullptr};
            return;
        }
        //bool z = n < node->elem;
        bool z = cmp(n, node->elem);
        if (z)
            add(node->left, n);
        else
            add(node->right, n);
    }
    template<class P>
    void iterate(const bst_node* node, P proc)
    {
        if (node == nullptr) return;
        iterate(node->left, proc);
        proc(node->elem);
        iterate(node->right, proc);
    }
    const T &find(const bst_node* node, const T &x) const
    {
        if (node == nullptr)
        {
            throw "Item not found.";
        }
        //bool c = x == node->elem;
        //bool c = !(x < node->elem) && !(node->elem < x);
        bool c = !cmp(x, node->elem) && !cmp(node->elem, x);
        if (c)
            return node->elem;
        //c = x < node->elem;
        c = cmp(x, node->elem);
        if (c)
            return find(node->left, x);
        return find(node->right, x);
    }

    public:
        //bst() : root(nullptr) {}
        bst(Compare cmp = Compare {}) : root(nullptr), cmp(cmp) {}
        auto &add(const T &n)
        {
            add(root, n);
            return *this;
        }

        template<class P>
        void iterate(P proc)
        {
            iterate(root, proc);
        }
        const T &find(const T &x) const
        {
            return find(root, x);
        }
};

struct ci
{
    string name;
    int num;
};

bool operator<(const ci &a, const ci &b)
{
    if (a.num < b.num) return true;
    if (b.num < a.num) return false;
    return a.name < b.name;
}

struct name_compare
{
    bool operator()(const ci &a, const ci &b) const
    {
        if (a.name < b.name) return true;
        if (b.name < a.name) return false;
        return a.num < b.num;
    }
};

auto f=[](int a, int b)
{
    return b < a;
};

int main()
{
    bst<int> b; //O(log 2 N)
    b.add(10).add(8).add(0).add(4);
    b.iterate([](auto &n)
    {
        cout << n << endl;
    });
    try
    {
        auto &q = b.find(6);
        cout << q << "\n";
    }
    catch(const char* ex)
    {
        cout << ex << "\n";
    }

    bst<string> s;
    s.add("hoy").add("es").add("miercoles").add("20");
    s.iterate([](auto &n)
    {
        cout << n << endl;
    });
    try
    {
        auto &m = s.find("hola");
        cout << m << "\n";
    }
    catch(const char* ex)
    {
        cout << ex << "\n";
    }

    bst<ci, name_compare> oops;
    oops.add(ci{"nicolas", 8234567}).add(ci{"catalina", 5234567}).add(ci{"rene", 1234567});
    oops.iterate([](auto &n)
    {
        cout << n.name << " " << n.num << endl;
    });

    bst<int, decltype(f)> jueves {f};
    jueves.add(10).add(5).add(15);
    jueves.iterate([](auto &n)
    {
        cout << n << endl;
    });
}

/*
template<class Talkable>
struct animal
{
    Talkable p;
    void talk()
    {
        p.talk();
    }
};

struct cat_talk
{
    void talk()
    {
        cout << "MEOW\n";
    }
};

struct dog_talk
{
    void talk()
    {
        cout << "GAUFF\n";
    }
};

template<typename T>
void w(animal<T> &a)
{
    a.talk();
}

using dog = animal<dog_talk>;
using cat = animal<cat_talk>;

int main()
{
    dog d;
    cat c;
    w(d);
    w(c);

    return 0;
}
*/

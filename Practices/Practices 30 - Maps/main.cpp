#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

struct id
{
    size_t n;
    virtual void show() const { cout << n << endl; }
};

struct ci : id
{
    string city;
    void show() const override { cout << n << " " << city << endl; }
};

struct ppt : id
{
    string country;
    void show()const override { cout << n << " " << country << endl; }
};

map<char, int>get_char_frecuencies(const string &s)
{
    map<char, int> m;

    for (auto c : s)
    {
        m[c]++; //No hay const []
        /*auto it = m.find(c);
        if (it == m.end())
        {
            m.insert(make_pair(c, 1));
        }
        else
        {
            counter = it->second;
            m[c] = counter + 1;
        }*/
    }

    return m;
}

struct id_comp
{
    bool operator()(const id* a, const id* b) const
    {
        return a->n < b->n;
    }
};

int main()
{
    map<id*, string, id_comp> nn;

    auto c1 = new ci();
    c1->n = 4007215;
    c1->city = "Cbba";

    nn[c1] = "Adela Zamudio";

    auto p1 = new ppt();
    p1->n = 248;
    p1->country = "Argentina";

    nn[p1] = "Lionel Messi";

    for (auto &i : nn)
    {
        cout << "*****" << endl;
        cout << i.second << endl;
        i.first->show();
    }
    cout << "--------------\n";
    ppt x;
    x.n = 248;
    auto it = nn.find(&x);
    if(it == nn.end())
        cerr << "Not found.\n";
    else
        cout << it->second << endl;

    for (auto &i : nn)
        delete i.first;
}

/*
int main()
{
    string s = "bolivianos el hado propicio corono nuestros votos y anhelo";
    auto x = get_char_frecuencies(s);

    for (auto &i : x)
    {
        cout << "CHAR: " << i.first << " = " << i.second << endl;
    }

    return 0;
}
*/
/*int main()
{
    unordered_map<int, string> x;
    x.insert(pair<int, string>{1, "one"});
    x.insert(make_pair(10, "ten"));
    x[0] = "zero";  // solo para obtener elementos que seguro están en el map
                    // insertar nuevos elementos
                    // mejor no usar para buscar elementos

    cout << x[2] << endl;
    x.insert(make_pair(10, "diez"));
    x[10] = "diez";
    for (auto &i : x)
        cout << i.first << ": " << i.second << endl;

    auto it = x.find(10);
    if (it == x.end())
    {
        cerr << "Not found.\n";
    }
    else
    {
        cout << it->second << endl;
    }

    return 0;
}*/

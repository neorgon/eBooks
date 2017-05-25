#include <iostream>
#include <unordered_map>
#include <memory>
#include <functional>
#include <vector>

using namespace std;

struct trie_node
{
    unordered_map<char, unique_ptr<trie_node>> nodes;

    void add(const char* c, int i)
    {
        nodes.insert(make_pair(c[i], make_unique<trie_node>()));
        if (c[i] != '\0')
            nodes.find(c[i])->second->add(c, i + 1);
    }

    bool contiene(const char* c, int i)
    {
        if (c[i] == '\0')
        {
            auto it = nodes.find(c[i]);
            return (it != nodes.end());
        }
        else
        {
            auto it = nodes.find(c[i]);
            if (it != nodes.end())
                return it->second->contiene(c, i + 1);
            else
                return false;
        }
    }
};

class trie
{
    trie_node root;

    public:
        void add(const char* s);
        bool contiene(const char* s);
        void iterate_all_start_with(const string& s, function<void(string)> lambda);
        void iterate_all_words(function<void(sting)> lambda);
};

void trie::add(const char* s)
{
    root.add(s, 0);
}

bool trie::contiene(const char* s)
{
    return root.contiene(s, 0);
}

void trie::iterate_all_start_with(const string &s, function<void(string)> lambda)
{

}

void trie::iterate_all_words(function<void(sting)> lambda)
{
    vector<string> ms { "hola", "mundo", "cruel" };
    for (int i = 0; i < 3; i++)
        lambda(ms[i]);
}

int main()
{
    trie x;

    x.add("perro");
    x.add("gato");
    x.add("perchero");
    x.add("silla");
    x.add("camisa");
    x.add("carro");
    x.add("ganancia");
    x.add("girar");
    x.add("gatos");

    cout << x.contiene("ganancia") << "\n";
    x.iterate_all_start_with
    (
        "ga",
        [](string s){ cout << s << "\n"; }
    );
    x.iterate_all_words
    (
        [](auto &s){ cout << s << "\n"; }
    );

    return 0;
}

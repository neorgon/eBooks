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

    vector<string> get_words(char* word, size_t x)
    {
        vector<string> words;

        if (x == nodes.size() - 1)
            return words;

        for (auto it = nodes.begin(); it != nodes.end(); it++)
        {
            word[x] = it->first;
            if (word[x] == '\0')
                words.push_back(word);

            it->second->get_words(word, x + 1);
        }

        return words;
    }
};

class trie
{
    trie_node root;

    public:
        void add(const char* s);
        bool contiene(const char* s);
        vector<string> get_words(char* word, int x);
        void iterate_all_start_with(const string& s, function<void(string)> lambda);
        void iterate_all_words(function<void(string)> lambda);
        void sizemap()
        {
            cout << root.nodes.size() << "\n";
        }
};

void trie::add(const char* s)
{
    root.add(s, 0);
}

bool trie::contiene(const char* s)
{
    return root.contiene(s, 0);
}

vector<string> trie::get_words(char* word, int x)
{
    vector<string> words = root.get_words(word, 0);

    return words;
}

void trie::iterate_all_start_with(const string &s, function<void(string)> lambda)
{

}

void trie::iterate_all_words(function<void(string)> lambda)
{
    char* word;
    vector<string> ms = get_words(word, 0);

    for (size_t i = 0; i < ms.size() - 1; i++)
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
    x.add("adios");
    x.add("mundo");
    x.add("cruel");
    x.add("cruela");

    cout << x.contiene("luigi") << "\n";
    x.iterate_all_start_with
    (
        "ga",
        [](string s){ cout << s << "\n"; }
    );
    x.iterate_all_words
    (
        [](string s){ cout << s << "\n"; }
    );
    x.sizemap();

    return 0;
}

#include <iostream>
#include <unordered_map>

using namespace std;

struct trie_node
{
    bool end_of_word;
    unordered_map<char, trie_node*> nodes;

    trie_node(char c, bool endw = false)
    {
        end_of_word = endw;
        nodes.insert(pair<char, trie_node*>(c, nullptr));
    }
};

class trie
{
    trie_node root;

    public:
        trie() { root('a'); }
        ~trie();
        void add(const char* s);
};

void trie::add(const char* s)
{

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

    /*cout << x.contiene("carro") << "\n";
    x.iterate_all_start_with
    (
        "ga",
        [](const string &s){ cout << s << "\n"; }
    );
    x.iterate_all_words
    (
        [](auto &s){ cout << s << "\n"; }
    );*/

    return 0;
}

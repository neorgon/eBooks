#include <string>
#include <iostream>
#include <unordered_map>
#include <memory>

using namespace std;

struct trie_node
{
    bool end_of_word = false;

    unordered_map<char, unique_ptr<trie_node>> nodes;
};

class trie
{
    trie_node root;

    void add(const char* s, trie_node& node)
    {
        auto k = *s;
        if (k == '\0')
        {
            node.end_of_word = true;
            return;
        }

        auto it = node.nodes.find(k);
        if (it == node.nodes.end())
        {
            node.nodes[k] = make_unique<trie_node>();
            add(s + 1, *node.nodes[k]);
            return;
        }

        add(s + 1, *it->second);
    }

    bool contains(const char* s, const trie_node& node) const
    {
        auto k = *s;

        if (node.end_of_word && k == '\0')
            return true;

        auto it = node.nodes.find(k);
        if (it == node.nodes.end())
            return false;

        return contains(s + 1, *it->second);
    }

    template <typename PROC>
    void iterate_all_words(PROC p, const trie_node& node, const string& prefix) const
    {
        if (node.end_of_word)
            p(prefix);

        for (auto& i : node.nodes)
        {
            auto word = prefix + i.first;
            iterate_all_words(p, *i.second, word);
        }
    }

    const trie_node* find_prefix_node(const string& s) const
    {
        return find_prefix_node(s.c_str(), root);
    }

    const trie_node* find_prefix_node(const char* s, const trie_node& node) const
    {
        auto k = *s;
        if (k == '\0')
            return &node;

        auto it = node.nodes.find(k);
        if (it == node.nodes.end())
            return nullptr;

        return find_prefix_node(s + 1, *it->second);
    }

public:
    void add(const string& s)
    {
        auto x = s.c_str();
        add(x, root);
    }

    template <typename PROC>
    void iterate_all_words(PROC p) const
    {
        iterate_all_words(p, root, "");
    }

    template <typename PROC>
    void iterate_all_words_that_start_with(const string& s, PROC p) const
    {
        auto node = find_prefix_node(s);
        if (node == nullptr)
            return;

        iterate_all_words(p, *node, s);
    }

    bool contains(const string& s) const
    {
        const char* x = s.c_str();
        return contains(x, root);
    }
};

int main()
{
    trie x;
    x.add("carro");
    x.add("gato");
    x.add("carreta");
    x.add("gatos");
    x.add("ganancia");
    x.add("mensual");
    x.add("menso");
    x.add("gesto");
    x.add("carroza");

    cout << x.contains("ga") << "\n****\n";

    x.iterate_all_words_that_start_with("ga", [](auto& s) { cout << s << "\n"; });

    cout << "****\n";

    x.iterate_all_words([](const string& s) { cout << s << "\n"; });

}

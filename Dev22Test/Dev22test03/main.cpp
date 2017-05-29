#include <iostream>
#include <string>
#include <time.h>
#include <list>
#include <memory>

using namespace std;

struct xml_node
{
    string name;
    list<xml_node> nodes;
};

class xml_document
{
    xml_node root;

    void append(xml_node &node, xml_node &child);
    string get_childs(list<xml_node> &node);
    public:
        xml_document(const string &txt)
        {
            root.name = txt;
        }
        string to_string();
        xml_node create_element(const string &txt);
        void append_child(xml_node &child);
};

void xml_document::append(xml_node &node, xml_node &child)
{
    node.nodes.push_back(child);
}

string xml_document::get_childs(list<xml_node> &node)
{
    for (auto n : node)
    {
        if (!n.nodes.size()) return "<" + n.name + " />";
        return "<" + n.name + ">" + get_childs(n.nodes) + "</" + n.name + ">";
    }
}

xml_node xml_document::create_element(const string &txt)
{
    xml_node tmp;

    tmp.name = txt;

    return tmp;
}

void xml_document::append_child(xml_node &child)
{
    append(root, child);
}

string xml_document::to_string()
{
    string xml;
    if (!root.nodes.size()) xml += "<" + root.name + " />";
    else
    {
        /*xml += "<" + root.name + ">";
        for (auto &n : root.nodes)
             xml += get_childs(n.nodes);
        xml += "</" + root.name + ">";*/
        cout << root.nodes.name << "\n";
    }

    return xml;
}

auto test1()
{
    xml_document doc { "test" };

    return doc.to_string() == "<test />";
}

auto test2()
{
    xml_document doc { "personas" };

    auto elem1 = doc.create_element("persona1");
    auto elem2 = doc.create_element("persona2");

    doc.append_child(elem1);
    doc.append_child(elem2);

    return doc.to_string() == "<personas><persona1 /><persona2 /></personas>";
}

template <typename Proc>
int execute_test(Proc p, const string& test_name)
{
    auto r = p();
    const char* passed = r ? " PASSED " : "FAILED";

    cout << "Executed [" << test_name << "]. Status: [" << passed << "]\n";

    return r ? 1 : 0;
}

int main()
{
    auto t0 = clock();

    auto tc = 0;

    tc += execute_test(test1, "Test1");
    tc += execute_test(test2, "Test2");
    /*tc += execute_test(test3, "Test3");
    tc += execute_test(test4, "Test4");
    tc += execute_test(test5, "Test5");
    tc += execute_test(test6, "Test6");
    tc += execute_test(test7, "Test7");
    tc += execute_test(test8, "Test8");
    tc += execute_test(test9, "Test9");*/

    auto t1 = clock();

    cout << "DURATION: " << (t1 - t0) << "\n";
    cout << "SCORE: " << tc << " / 9\n";
    return 0;
}

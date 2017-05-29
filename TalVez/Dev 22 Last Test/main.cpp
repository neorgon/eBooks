#include <iostream>
#include <sstream>
#include <time.h>
#include <string>
#include <list>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>

using namespace std;

string escape(const string &src)
{
    ostringstream dst;

    for (char ch : src)
    {
        switch (ch)
        {
            case '&': dst << "&amp;"; break;
            case '\'': dst << "&apos;"; break;
            case '"': dst << "&quot;"; break;
            case '<': dst << "&lt;"; break;
            case '>': dst << "&gt;"; break;
            default: dst << ch; break;
        }
    }

    return dst.str();
}

class xml_exception: public exception
{
    string message;

    public:
        xml_exception(string message)
        {
            this->message = message;
        }

        virtual const char* what() const throw()
        {
            return message.c_str();
        }

        ~xml_exception()
        {
        }
};

struct xml_node
{
    string value;
    string only_txt;
    list<pair<string, string>> attrs;
    list<shared_ptr<xml_node>> nodes;

    void append_child(const shared_ptr<xml_node> &n)
    {
        nodes.push_back(n);
    }

    void set_attribute(const string &key, const string &value)
    {
        pair<string, string> attr;

        attr = make_pair(key, "\"" + escape(value) + "\"");
        attrs.push_back(attr);
    }

    string get_attrs() const
    {
        string tmp_attrs = "";

        if (attrs.size())
        {
            tmp_attrs += " ";
            for (auto &a : attrs)
            {
                tmp_attrs += a.first + "=" + a.second + " ";
            }
            tmp_attrs = tmp_attrs.substr(0, tmp_attrs.size() - 1);
        }

        return tmp_attrs;
    }
};

class xml_document
{
    xml_node root;

    string to_string(const list<shared_ptr<xml_node>> &n) const;

    public:
        xml_document(const string &v) { root.value = v; }
        shared_ptr<xml_node> create_element(const string &v);
        shared_ptr<xml_node> create_text(const string &v);
        shared_ptr<xml_node> create_comment(const string &v);
        void append_child(const shared_ptr<xml_node> &n);
        xml_node &get_element_at(size_t e) const;
        string to_string() const;
};

shared_ptr<xml_node> xml_document::create_element(const string &v)
{
    xml_node tmp;

    tmp.value = v;

    return make_shared<xml_node>(tmp);
}

shared_ptr<xml_node> xml_document::create_text(const string &v)
{
    xml_node tmp;

    tmp.only_txt = escape(v);

    return make_shared<xml_node>(tmp);
}

shared_ptr<xml_node> xml_document::create_comment(const string &v)
{
    xml_node tmp;

    tmp.only_txt = "<!-- " + v + " -->";

    return make_shared<xml_node>(tmp);
}

void xml_document::append_child(const shared_ptr<xml_node> &n)
{
    if (count(n->value.begin(), n->value.end(), ' '))
        throw xml_exception("Element name must not contain spaces");
    root.nodes.push_back(n);
}

string xml_document::to_string(const list<shared_ptr<xml_node>> &n) const
{
    string xml = "";

    if (n.size())
        for (auto &i : n)
        {
            if (!i->only_txt.empty())
            {
                xml += i->only_txt;
            }
            else
            {
                if (i->nodes.size())
                {
                    xml += "<" + i->value + i->get_attrs() + ">" + to_string(i->nodes) + "</" + i->value + ">";
                }
                else
                    xml += "<" + i->value + i->get_attrs() + " />";
            }
        }

    return xml;
}

xml_node &xml_document::get_element_at(size_t e) const
{
    size_t i = 0;

    if (root.nodes.size() >= e)
        for (auto &n : root.nodes)
        {
            i++;
            if (i == e) return *n;
        }

    throw xml_exception("Position out of range. Element not found.");
}

string xml_document::to_string() const
{
    string xml = "";

    if (root.nodes.size())
    {
        xml = "<" + root.value + ">" + to_string(root.nodes) + "</" + root.value + ">";
    }
    else
        xml = "<" + root.value + " />";

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

auto test3()
{
    xml_document doc { "cars" };

    auto c1 = doc.create_element("car");
    auto p11 = doc.create_element("door");
    auto p12 = doc.create_element("engine");

    c1->append_child(p11);
    c1->append_child(p12);

    auto c2 = doc.create_element("car");

    doc.append_child(c1);
    doc.append_child(c2);

    return doc.to_string() == "<cars><car><door /><engine /></car><car /></cars>";
}

auto test4()
{
    xml_document doc { "doc" };

    auto elem = doc.create_element("content");
    doc.append_child(elem);

    auto text = doc.create_text("This is a content text");
    elem->append_child(text);

    return doc.to_string() == "<doc><content>This is a content text</content></doc>";
}

auto test5()
{
    xml_document doc { "personas" };

    auto p1 = doc.create_element("persona");
    doc.append_child(p1);

    p1->set_attribute("nombre", "juan");
    p1->set_attribute("apellido", "rios");
    p1->set_attribute("id", "1432924");

    auto p2 = doc.create_element("persona");
    doc.append_child(p2);

    p2->set_attribute("nombre", "andrea");
    p2->set_attribute("apellido", "suarez");
    p2->set_attribute("id", "14329240");

    p2->append_child(doc.create_element("cursos"));

    return doc.to_string() == "<personas><persona nombre=\"juan\" apellido=\"rios\" id=\"1432924\" />"
                               "<persona nombre=\"andrea\" apellido=\"suarez\" id=\"14329240\">"
                              "<cursos /></persona></personas>";
}

auto test6()
{
    xml_document doc { "empty"};

    auto elem = doc.create_element("data_field");
    doc.append_child(elem);

    elem->append_child(doc.create_comment("This is a comment"));

    return doc.to_string() == "<empty><data_field><!-- This is a comment --></data_field></empty>";
}

auto test7()
{
    xml_document doc { "tests" };

    auto elem = doc.create_element("test7");
    doc.append_child(elem);

    elem->set_attribute("condition", "a < b");
    elem->append_child(doc.create_text("M&M are delicious. \"Hello\""));

    return doc.to_string() == "<tests><test7 condition=\"a &lt; b\">M&amp;M are delicious. &quot;Hello&quot;</test7></tests>";
}

auto test8()
{
    try
    {
        xml_document doc { "tests" };

        auto elem = doc.create_element("test 8");
        doc.append_child(elem);
    }
    catch (const xml_exception& ex)
    {
        return "Element name must not contain spaces"s == ex.what();
    }

    return false;
}

auto test9()
{
    xml_document doc { "personas" };

    auto p1 = doc.create_element("persona");
    doc.append_child(p1);

    p1->set_attribute("nombre", "juan");
    p1->set_attribute("apellido", "rios");
    p1->set_attribute("id", "1432924");

    auto p2 = doc.create_element("persona");
    doc.append_child(p2);

    p2->set_attribute("nombre", "andrea");
    p2->set_attribute("apellido", "suarez");
    p2->set_attribute("id", "14329240");

    p2->append_child(doc.create_element("cursos"));

    auto doc2 = doc;

    doc.append_child(doc.create_element("persona1"));
    doc.append_child(doc.create_element("persona2"));
    doc.append_child(doc.create_element("persona3"));

    doc.get_element_at(1).set_attribute("edad", "32");

    doc2.append_child(doc.create_element("persona4"));

    //cout << doc2.to_string() << "\n";

    return doc2.to_string() == "<personas><persona nombre=\"juan\" apellido=\"rios\" id=\"1432924\" />"
                                       "<persona nombre=\"andrea\" apellido=\"suarez\" id=\"14329240\">"
                                       "<cursos /></persona><persona4 /></personas>";
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
    tc += execute_test(test3, "Test3");
    tc += execute_test(test4, "Test4");
    tc += execute_test(test5, "Test5");
    tc += execute_test(test6, "Test6");
    tc += execute_test(test7, "Test7");
    tc += execute_test(test8, "Test8");
    tc += execute_test(test9, "Test9");

    auto t1 = clock();

    cout << "DURATION: " << (t1 - t0) << "\n";
    cout << "SCORE: " << tc << " / 9\n";
    return 0;
}

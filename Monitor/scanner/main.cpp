#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

enum class PType {Bool, Integer, Label, List, Real, String};

class PRules
{
    string name;
    string abrv;
    PType type;
    bool optional;
    size_t iquantity;

    public:
        PRules(const string &n, string a, PType t, bool o, size_t i) :
            name {n}, abrv {a}, type {t}, optional {o}, iquantity {i} {};
        string Get_name();
        bool IsARule(const string &token) const;
        struct Finder {
            string token;
            Finder(const string &t) : token {t} {};
            bool operator()(const PRules &rule) const
            {
                return rule.name.compare(token) == 0 || rule.abrv.compare(token) == 0;
            }
        };
};

string PRules::Get_name()
{
    return name;
}

bool PRules::IsARule(const string &token) const
{
    return true;
}

class MyParser
{
    vector<PRules> rules;
    vector<string> tokens;

    size_t GetLenght(const char* source);
    void CopyToken(char *token, const char* source, size_t len);

    public:
        void AddRule(const string &name, string abrv, PType type, bool optional, size_t iquantity = 1);
        void PrintRules(); //
        void Scanner(int argc, char** args);
        void PrintTokens(); //
        void LexicalAnalyzer() const;
};

void MyParser::AddRule(const string &name, string abrv, PType type, bool optional, size_t iquantity)
{
    PRules newRule(name, abrv, type, optional, iquantity);

    rules.push_back(newRule);
}

void MyParser::PrintRules()
{
    for (auto &r : rules)
        cout << r.Get_name() << endl;
}

size_t MyParser::GetLenght(const char* source)
{
    size_t c = 0;

    for (;source[c] != '\0'; ++c)
    {

    }

    return c;
}

void MyParser::CopyToken(char *token, const char* source, size_t len)
{
    for(size_t i = 0; i < len; i++)
        token[i] = source[i];

    token[len] = '\0';
}

void MyParser::Scanner(int argc, char** args)
{
    for (int i = 1; i < argc; ++i)
    {
        size_t len = GetLenght(args[i]);
        auto token = new char[len + 1];

        CopyToken(token, args[i], len);
        tokens.push_back(token);

        delete[] token;
    }
}

void MyParser::PrintTokens()
{
    for (auto &t : tokens)
        cout << t << endl;
}

void MyParser::LexicalAnalyzer() const
{
    vector<PRules>::const_iterator it;
    for (const string &t : tokens)
    {
        if(t[0] == '-')
        {
            it = find_if(rules.begin(), rules.end(), PRules::Finder(t));
            if(it == rules.end())
            {
                cout << "One or more parameters is not correct." << endl;
                return;
            }
        }
    }
}

int main(int argc, char* args[])
{
    MyParser np;

    np.AddRule("-calorias", "-c", PType::Integer, false);
    np.AddRule("-proteinas", "-p", PType::Integer, false);
    np.AddRule("-grasas_saturadas", "-g", PType::Real, false);
    np.AddRule("-grasas_hidrogenadas", "-h", PType::Real, true, 0);
    np.AddRule("-nombre", "-n", PType::String, false, 2);

    np.PrintRules();

    if(argc > 1)
    {
        np.Scanner(argc, args);
        //np.PrintTokens();
    }
    else
        cout << "Bad parameters usage." << endl;

    np.LexicalAnalyzer();

    return 0;
}

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class PType {Bool, Integer, Label, List, Real, String};

class PRules
{
    string name;
    char abrv;
    PType type;
    bool optional;
    size_t iquantity;

    public:
        PRules(const string &n, char a, PType t, bool o, size_t i) :
            name {n}, abrv {a}, type {t}, optional {o}, iquantity {i} {};
        string Get_name();
};

string PRules::Get_name()
{
    return name;
}

class MyParser
{
    vector<PRules> rules;
    vector<string> tokens;

    size_t GetLenght(const char* source);
    void CopyToken(string &token, const char* source);

    public:
        void AddRule(const string &name, char abrv, PType type, bool optional, size_t iquantity = 1);
        void PrintRules();
        void Scanner(int argc, char** args);
        void PrintTokens();
        void LexicalAnalyzer() const;
};

void MyParser::AddRule(const string &name, char abrv, PType type, bool optional, size_t iquantity)
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

void MyParser::CopyToken(string &token, const char* source)
{
    size_t len = GetLenght(source);

    for(size_t i = 0; i < len; i++)
        token[i] = source[i];

    token[len] = '\0';
}

void MyParser::Scanner(int argc, char** args)
{
    string token;

    for (int i = 0; i < argc; ++i)
    {
        CopyToken(token, args[i]);
        tokens.push_back(token);
    }
}

void MyParser::PrintTokens()
{
    for (auto &t : tokens)
        cout << t << endl;
}

int main(int argc, char* args[])
{
    MyParser np;

    np.AddRule("calorias", 'c', PType::Integer, false);
    np.AddRule("proteinas", 'p', PType::Integer, false);
    np.AddRule("grasas_saturadas", 'g', PType::Real, false);
    np.AddRule("grasas_hidrogenadas", 'h', PType::Real, true, 0);
    np.AddRule("nombre", 'n', PType::String, false, 2);

    np.PrintRules();

    /*for (int i = 1; i < argc; ++i)
    {
        cout << args[i] << endl;
    }*/

    np.PrintTokens();

    return 0;
}

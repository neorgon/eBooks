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
        string GetName();
        PType GetType() const;
        struct Finder {
            string token;
            Finder(const string &t) : token {t} {};
            bool operator()(const PRules &rule) const
            {
                return rule.name.compare(token) == 0 || rule.abrv.compare(token) == 0;
            }
        };
};

string PRules::GetName()
{
    return name;
}

PType PRules::GetType() const
{
    return type;
}

class POptions
{
    string name;
    PType type;
    string value;

    public:
        POptions(const string &n, PType t) : name{n}, type{t} {}
        void Print();
};

void POptions::Print()
{
    cout << name << " :" << static_cast<int>(type) << ": " << value << endl;
}

class MyParser
{
    vector<PRules> rules;
    vector<string> tokens;
    vector<POptions> options;

    size_t GetLenght(const char* source);
    void CopyToken(char *token, const char* source, size_t len);
    void AddRule(const string &name, string abrv, PType type, bool optional, size_t iquantity = 1);

    public:
        void AddBool(const string &name, string abrv, bool optional, size_t iquantity = 1);
        void AddInteger(const string &name, string abrv, bool optional, size_t iquantity = 1);
        void AddLabel(const string &name, string abrv, bool optional, size_t iquantity = 1);
        void AddList(const string &name, string abrv, bool optional, size_t iquantity = 1);
        void AddReal(const string &name, string abrv, bool optional, size_t iquantity = 1);
        void AddString(const string &name, string abrv, bool optional, size_t iquantity = 1);
        void PrintRules(); //
        void Scanner(int argc, char** args);
        void PrintTokens(); //
        void LexicalAnalyzer() const;
};

void MyParser::AddRule(const string &name, string abrv, PType type, bool optional, size_t iquantity)
{
    PRules newRule("--" + name, "-" + abrv, type, optional, iquantity);
    rules.push_back(newRule);
}

void MyParser::AddBool(const string &name, string abrv, bool optional, size_t iquantity)
{
    AddRule(name, abrv, PType::Bool, optional, iquantity);
}

void MyParser::AddInteger(const string &name, string abrv, bool optional, size_t iquantity)
{
    AddRule(name, abrv, PType::Integer, optional, iquantity);
}

void MyParser::AddLabel(const string &name, string abrv, bool optional, size_t iquantity)
{
    AddRule(name, abrv, PType::Label, optional, iquantity);
}

void MyParser::AddList(const string &name, string abrv, bool optional, size_t iquantity)
{
    AddRule(name, abrv, PType::List, optional, iquantity);
}

void MyParser::AddReal(const string &name, string abrv, bool optional, size_t iquantity)
{
    AddRule(name, abrv, PType::Real, optional, iquantity);
}

void MyParser::AddString(const string &name, string abrv, bool optional, size_t iquantity)
{
    AddRule(name, abrv, PType::String, optional, iquantity);
}

void MyParser::PrintRules()
{
    for (auto &r : rules)
        cout << r.GetName() << endl;
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
    int opCounter = 0;

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
            else
            {
                POptions option(t, it->GetType());
                options.push_back(option);
            }
        }
        else
        {
            // Añadir el valor a la regla.
            // devolver una lista de reglas con valor (value)
            // rules.at(position).value = siguiente token comparado si el token no empieza con '-'
        }
    }
}

int main(int argc, char* args[])
{
    MyParser np;

    np.AddInteger("calorias", "c", false);
    np.AddInteger("proteinas", "p", false);
    np.AddReal("grasas_saturadas", "g", false);
    np.AddReal("grasas_hidrogenadas", "h", true, 0);
    np.AddString("nombre", "n", false, 2);

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

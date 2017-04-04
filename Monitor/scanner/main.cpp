#include <iostream>
#include <vector>
#include <algorithm>

#include <Rules.h>
#include <Options.h>

using namespace std;

class MyParser
{
    vector<Rules> rules;
    vector<string> tokens;
    vector<Options> options;

    size_t GetLenght(const char* source);
    void CopyToken(char *token, const char* source, size_t len);
    void AddRule(const string &name, const string &abrv, PType type, bool optional, size_t iquantity = 1);

    public:
        void AddBool(const string &name, string abrv, bool optional, size_t iquantity = 1);
        void AddInteger(const string &name, string abrv, bool optional, size_t iquantity = 1);
        void AddLabel(const string &name, string abrv, bool optional, size_t iquantity = 1);
        void AddList(const string &name, string abrv, bool optional, size_t iquantity = 1);
        void AddReal(const string &name, string abrv, bool optional, size_t iquantity = 1);
        void AddString(const string &name, string abrv, bool optional, size_t iquantity = 1);
        void PrintRules() const;//
        void Scanner(int argc, char** args);
        void PrintTokens() const;//
        void LexicalAnalyzer();
        void PrintOptions() const;//
};

void MyParser::AddRule(const string &name, const string &abrv, PType type, bool optional, size_t iquantity)
{
    Rules newRule("--" + name, "-" + abrv, type, optional, iquantity);
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

void MyParser::PrintRules() const
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

void MyParser::PrintTokens() const
{
    for (auto &t : tokens)
        cout << t << endl;
}

void MyParser::LexicalAnalyzer()
{
    vector<Rules>::const_iterator it;
    int opCounter = 0;
    int tkCounter = 0;

    for (const string &t : tokens)
    {
        if(t[0] == '-')
        {
            it = find_if(rules.begin(), rules.end(), Rules::Finder(t));
            if(it == rules.end())
            {
                cout << "One or more parameters is not correct." << endl;
                return;
            }
            else
            {
                Options newOption(t, it->GetType());
                options.push_back(newOption);
                ++opCounter;
            }
        }
        else
        {
            if (!(tkCounter % 2 == 0))
            {
                options.at(opCounter - 1).SetValue(t);
            }
            else
            {
                cout << "Lexical error." << endl;
                return;
            }
        }
        ++tkCounter;
    }
}

void MyParser::PrintOptions() const
{
    for (auto &o : options)
    {
        cout << o.GetName().c_str() << ":" << o.GetTypeName() << ":" << o.GetValue().c_str() << endl;
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

    //np.PrintRules();

    if(argc > 1)
    {
        np.Scanner(argc, args);
        //np.PrintTokens();
    }
    else
        cout << "Missing parameters." << endl;

    np.LexicalAnalyzer();
    np.PrintOptions();

    return 0;
}

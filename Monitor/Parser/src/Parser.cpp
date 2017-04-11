#include "Parser.h"
#include <stdexcept>

void Parser::AddRule(const char* name, char abbr, PType type, bool optional, size_t quantity)
{
    Rules newRule("--" + string(name), "-" + string(1, abbr), type, optional, quantity);
    rules.push_back(newRule);
}

void Parser::AddInteger(const char* name, char abbr, bool optional, size_t quantity)
{
    AddRule(name, abbr, PType::Integer, optional, quantity);
}

void Parser::AddReal(const char* name, char abbr, bool optional, size_t quantity)
{
    AddRule(name, abbr, PType::Real, optional, quantity);
}

void Parser::Scanning(const char* input)
{
    tokens.push_back(string(input));
}

bool Parser::AnalyzingSyntax()
{
    vector<Rules>::const_iterator it;

    for (auto &t : tokens)
    {
        if (t[0] == '-')
        {
            it = find_if(rules.begin(), rules.end(), Rules::Finder(t));
            if(it == rules.end())
                throw; //Exceptions("One or more parameters is not correct.");
            //order to labels add a value in values vector
            //cout << (int)it->GetType() << endl;
            options.push_back(t);
        }
        else
        {
            values.push_back(t);
        }
    }

    return true;
}

bool Parser::AnalyzingSemantic()
{
    size_t counter = 0;
    vector<Rules>::const_iterator it;

    if (options.size() != values.size())
        return false; //syntax exception
    for (auto &o : options)
    {
        it = find_if(rules.begin(), rules.end(), Rules::Finder(o));
        string keyName = it->GetName().substr(2);
        Options newOption(keyName, it->GetAbbr()[1], it->GetType(), values.at(counter));
        //settings.insert(std::make_pair(it->GetName().substr(2), settings[string].push_back(newOption)));
        settings.insert(pair<string, vector<Options>>(keyName, vector<Options>()));
        settings[keyName].push_back(newOption);
        ++counter;
    }

    return true;
}

bool Parser::Validate(int argc, const char** args) //only of testing int argc, char* args[]
{
    //Scanning && AnalyzingSyntax && AnalyzingSemantic
    if (argc == 0)
        return false;
    else
    {
        for (int i = 1; i < argc; i++)
            Scanning(args[i]);
    }

    return AnalyzingSyntax() && AnalyzingSemantic();
}

const map<string, vector<Options>> &Parser::GetOptions()
{
    /*for (auto &s : settings)
    {
        string v = s.first;
        for (auto& o : s.second)
        {
            //cout << "String: " << o.GetValue() << endl;
            o.SetValue();
            //cout << "Integer: " << *((int*)(o.Value)) << endl;
        }
    }*/

    return settings;
}

Parser::~Parser()
{
    //dtor
}

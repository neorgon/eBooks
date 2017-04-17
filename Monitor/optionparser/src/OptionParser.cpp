#include <OptionParser.h>
#include <Boolean.h>
/*#include <Integer.h>
#include <List.h>
#include <Real.h>
#include <Text.h>*/

OptionParser::OptionParser(int argc, const char** args)
{
    int token = 1;
    tokenOption = "";
    tokenValue = "";

    while (token < argc)
    {
        if(tokenOption.empty())
        {
            tokenOption = isOption(string(args[token]));
            token++;
        }
        else if(tokenValue.empty())
        {
            if (args[token][0] == '[')
                tokenValue = "[";
            else if (args[token][0] == '-')
                tokenValue = "true";
            else
            {
                tokenValue = isValue(string(args[token]));
                token++;
            }
        }

        if (!tokenOption.empty() && !tokenValue.empty())
        {
            tokens.push_back(make_pair(tokenOption, tokenValue));
            tokenOption = "";
            tokenValue = "";
        }

        if (addEndList)
        {
            tokens.push_back(make_pair("EndList",  "]"));
            addEndList = false;
        }
    }

    if (!tokenOption.empty())
        tokens.push_back(make_pair(tokenOption, "true"));
}

OptionParser::~OptionParser()
{
    //dtor
}

string OptionParser::isOption(string token)
{
    if(token[0] == '[')
        token = token.substr(1);

    if(token[0] == '-' && token[1] == '-')
    {
        if (token[token.length() - 1] == ']')
        {
            addEndList = true;
            return token.substr(2, token.length() - 1);
        }
        return token.substr(2);
    }
    else if (token[0] == '-')
    {
        if (token[token.length() - 1] == ']')
        {
            addEndList = true;
            return token.substr(1, token.length() - 1);
        }
        return token.substr(1);
    }
    else
    {
        cerr << "Syntax error: se esparaba un operador." << endl; //throw; //Syntax error: se esparaba un operador.
        return "";
    }
}

string OptionParser::isValue(const string &token)
{
    if (token[token.length() - 1] == ']')
    {
        addEndList = true;
        return token.substr(0, token.length() - 1);
    }
    return token;
}

void OptionParser::AddDefinition(const char* name, char abbr, OptionType type, bool optional, size_t quantity)
{
    OptionDefinition newDefinition(string(name), string(1, abbr), type, optional, quantity);
    definitions.push_back(newDefinition);
}

void OptionParser::AddInteger(const char* name, char abbr, bool optional, size_t quantity)
{
    AddDefinition(name, abbr, OptionType::Integer, optional, quantity);
}

void OptionParser::AddReal(const char* name, char abbr, bool optional, size_t quantity)
{
    AddDefinition(name, abbr, OptionType::Real, optional, quantity);
}

void OptionParser::AddBoolean(const char* name, char abbr, bool optional, size_t quantity)
{
    AddDefinition(name, abbr, OptionType::Boolean, optional, quantity);
}

void OptionParser::AddText(const char* name, char abbr, bool optional, size_t quantity)
{
    AddDefinition(name, abbr, OptionType::Text, optional, quantity);
}

void OptionParser::AddList(const char* name, char abbr, bool optional, size_t quantity)
{
    AddDefinition(name, abbr, OptionType::List, optional, quantity);
}

bool OptionParser::AnalyzeSintax()
{
    vector <OptionDefinition>::const_iterator it;

    for (auto &t : tokens)
    {
        it = find_if(definitions.begin(), definitions.end(), OptionDefinition::Finder(t.first));
        if (it == definitions.end() && t.first.compare("EndList") != 0)
            throw; // No existe el comando en la definición de opciones.
    }

    return true;
}

bool OptionParser::AnalyzeSemantic()
{
    vector <OptionDefinition>::const_iterator it;

    for (auto &t : tokens)
    {
        it = find_if(definitions.begin(), definitions.end(), OptionDefinition::Finder(t.first));
        string name = it->GetName();
        string abbr = it->GetAbbr();
        OptionType type = it->GetType();
        options.insert(pair<string, vector<IOptionType>> (name, vector<IOptionType>()));
        switch(type)
        {
            case OptionType::Boolean:
            {
                Boolean newOption(name, abbr[0], type, t.second);
                options[name].push_back(newOption);
                break;
            }
            /*case OptionType::Integer:
            {
                Integer newOption(name, abbr[0], type, t.second);
                options[name].push_back(newOption);
                break;
            }
            case OptionType::List:
            {
                //List newOption(name, abbr, type, t.second);
                break;
            }
            case OptionType::Real:
            {
                Real newOption(name, abbr[0], type, t.second);
                options[name].push_back(newOption);
                break;
            }
            case OptionType::Text:
            {
                Text newOption(name, abbr[0], type, t.second);
                options[name].push_back(newOption);
                break;
            }*/
        }
    }

    return true;
}

bool OptionParser::Validate()
{
    if (tokens.size() == 0)
        return false;

    return AnalyzeSintax();
}

const string OptionParser::GetToken(size_t i)
{
    if (i < tokens.size())
        return tokens.at(i).first + ": " + tokens.at(i).second;
    else
        return "";
}

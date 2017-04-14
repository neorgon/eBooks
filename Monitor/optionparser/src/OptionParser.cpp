#include "OptionParser.h"

OptionParser::OptionParser(int argc, const char** args)
{
    int token = 1;
    string tokenOption = "";
    string tokenValue = "";

    while (token < argc)
    {
        if (args[token][0] == '-' && args[token][1] == '-' && tokenOption.empty())
        {
            tokenOption = string(args[token]).substr(2);
            token++;
        }
        else
            if (args[token][0] == '-' && tokenOption.empty())
            {
                tokenOption = string(args[token]).substr(1);
                token++;
            }
            else
            {
                if (tokenValue.empty())
                {
                    tokenValue = string(args[token]);
                    token++;
                }
                else
                {
                    //throw
                }
            }

        if (!tokenOption.empty() && !tokenValue.empty())
        {
            tokens.push_back(make_pair(tokenOption, tokenValue));
            tokenOption = "";
            tokenValue = "";
        }
    }
}

OptionParser::~OptionParser()
{
    //dtor
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
    vector<OptionDefinition>::const_iterator it;

    for (auto &t : tokens)
    {
        it = find_if(definitions.begin(), definitions.end(), OptionDefinition::Finder(t.first))
        if (it == definitions.end())
            throw; // No existe el comando en la definición de opciones.
    }

    return true;
}

bool OptionParser::Validate()
{
    if (tokens.size() == 0)
        return false;

    return AnalyzeSintax();
}

const string OptionParser::GetToken(int i) const
{
    //return tokens.at(i);
    return "hola";
}

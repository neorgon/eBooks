#include "../include/OptionParser.h"
#include "../include/Boolean.h"
#include "../include/Integer.h"
#include "../include/Real.h"
#include "../include/Text.h"

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
            if (args[token][0] == '-')
                tokenValue = "true";
            else
                if (args[token][0] == '[')
                {
                    addList = true;
                    tokenValue = isValue(string(args[token]).substr(1));
                    token++;
                }
                else
                {
                    tokenValue = isValue(string(args[token]));
                    token++;
                }
        }

        if (!tokenOption.empty() && !tokenValue.empty())
        {
            tokens.push_back(make_pair(tokenOption, tokenValue));
            if (!addList)
                tokenOption = "";
            tokenValue = "";
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
    if(token[0] == '-' && token[1] == '-')
    {
        return token.substr(2);
    }
    else if (token[0] == '-')
    {
        return token.substr(1);
    }
    else
    {
        throw SyntaxException ("Operator expected");
        return "";
    }
}

string OptionParser::isValue(const string &token)
{
    if (token[token.length() - 1] == ']')
    {
        addList = false;
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

bool OptionParser::AnalyzeSintax()
{
    vector <OptionDefinition>::const_iterator it;

    for (auto &t : tokens)
    {
        it = find_if(definitions.begin(), definitions.end(), OptionDefinition::Finder(t.first));
        if (it == definitions.end() && t.first.compare("EndList") != 0)
            throw SyntaxException("Command not found");
    }

    return true;
}

bool OptionParser::AnalyzeSemantic()
{
    vector<OptionDefinition>::const_iterator itOptionDefinition;
    vector<pair<string, string>>::const_iterator itTokens;
    size_t e = 0;

    //for (auto &t : tokens)
    for (itTokens = tokens.begin(); itTokens < tokens.end(); itTokens++, e++)
    {
        itOptionDefinition = find_if(definitions.begin(),
                                     definitions.end(),
                                     OptionDefinition::Finder(tokens[e].first));
        string name = itOptionDefinition->GetName();
        string abbr = itOptionDefinition->GetAbbr();
        OptionType type = itOptionDefinition->GetType();
        options.insert(pair<string, vector<IOptionType*>> (name, vector<IOptionType*>()));
        switch(type)
        {
            case OptionType::Boolean:
            {
                IOptionType* newOption = new Boolean(name, abbr[0], type, tokens[e].second);
                options[name].push_back(newOption);
                break;
            }
            case OptionType::Integer:
            {
                IOptionType* newOption = new Integer(name, abbr[0], type, tokens[e].second);
                options[name].push_back(newOption);
                break;
            }
            case OptionType::Real:
            {
                IOptionType* newOption = new Real(name, abbr[0], type, tokens[e].second);
                options[name].push_back(newOption);
                break;
            }
            case OptionType::Text:
            {
                IOptionType* newOption = new Text(name, abbr[0], type, tokens[e].second);
                options[name].push_back(newOption);
                break;
            }
        }
    }

    return true;
}

bool OptionParser::Validate()
{
    if (tokens.size() == 0)
        return false;

    return AnalyzeSintax() && AnalyzeSemantic();
}

const string OptionParser::GetToken(size_t i)
{
    if (i < tokens.size())
        return tokens.at(i).first + ": " + tokens.at(i).second;
    else
        return "";
}

const map<string, vector<IOptionType*>> OptionParser::GetOptions() const
{
    return options;
}

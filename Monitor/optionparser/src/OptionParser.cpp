#include "OptionParser.h"

OptionParser::OptionParser(int argc, const char** args)
{
    for (int i = 1; i < argc; i++)
    {
        if(args[i][0] == '-' && args[i][1] == '-')
            tokens.push_back(string(args[i]).substr(2));
        else if(args[i][0] == '-')
                tokens.push_back(string(args[i]).substr(1));
            else
                tokens.push_back(string(args[i]));
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

bool OptionParser::AnalyzeSintax()
{
    vector<OptionDefinition>::const_iterator it;
    int tokenCounter = 0;

    for (auto &t : tokens)
    {
        if (tokenCounter % 2)
        {
            it = find_if(definitions.begin(), definitions.end(), OptionDefinition::Finder(t));
            if(it == definitions.end())
                throw; //Exceptions("One or more parameters is not correct.");
            //order to labels add a value in values vector
            //cout << (int)it->GetType() << endl;
            tokenOptions.push_back(t);
        }
        else
        {
            tokenValues.push_back(t);
        }
        tokenCounter++;
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
    return tokens.at(i);
}

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

const string OptionParser::GetToken(int i) const
{
    return tokens.at(i);
}

#ifndef OPTIONPARSER_H
#define OPTIONPARSER_H

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

#include<OptionDefinition.h>

using namespace std;

class OptionParser
{
    vector<string> tokens;
    vector<OptionDefinition> definitions;
    vector<string> tokenOptions;
    vector<string> tokenValues;

    void AddDefinition(const char* name, char abbr, OptionType type, bool optional, size_t quantity);
    bool AnalyzeSintax();

    public:
        OptionParser(int argc, const char** args);
        virtual ~OptionParser();
        void AddInteger(const char* name, char abbr, bool optional = false, size_t quantity = 1);
        void AddReal(const char* name, char abbr, bool optional = false, size_t quantity = 1);
        bool Validate();

        const string GetToken(int i) const;
};

#endif // OPTIONPARSER_H

#ifndef OPTIONPARSER_H
#define OPTIONPARSER_H

#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include<algorithm>
#include<map>

#include<OptionDefinition.h>
#include<IOptionType.h>

using namespace std;

class OptionParser
{
    string tokenOption;
    string tokenValue;
    bool addEndList = false;

    vector<OptionDefinition> definitions;
    vector<pair<string, string>> tokens;
    map<string, vector<IOptionType>> options;

    void AddDefinition(const char* name, char abbr, OptionType type, bool optional, size_t quantity);
    string isOption(string token);
    string isValue(const string &token);
    bool AnalyzeSintax();
    bool AnalyzeSemantic();

    public:
        OptionParser(int argc, const char** args);
        virtual ~OptionParser();
        void AddInteger(const char* name, char abbr, bool optional = false, size_t quantity = 1);
        void AddReal(const char* name, char abbr, bool optional = false, size_t quantity = 1);
        void AddBoolean(const char* name, char abbr, bool optional = true, size_t quantity = 1);
        void AddText(const char* name, char abbr, bool optional = false, size_t quantity = 1);
        void AddList(const char* name, char abbr, bool optional = false, size_t quantity = 1);
        bool Validate();

        const string GetToken(size_t i);
};

#endif // OPTIONPARSER_H

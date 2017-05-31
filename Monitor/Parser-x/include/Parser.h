#ifndef PARSER_H
#define PARSER_H
#include<vector>
#include<stdio.h>
#include<iostream>
#include<string>
#include<exception>
#include <algorithm>
#include <map>


#include<Options.h>
#include<Rules.h>
#include<Exceptions.h>

class Parser
{
    vector<Rules> rules;
    vector<string> tokens;
    vector<string> options;
    vector<string> values;
    map<string, vector<Options>> settings;

    string ToLower(const string &);
    void AddRule(const char* name, char abbr, PType type, bool optional, size_t quantity);
    void Scanning(const char* input);
    bool AnalyzingSyntax();
    bool AnalyzingSemantic();

public:

    void AddInteger(const char* name, char abbr, bool optional = false, size_t quantity = 1);
    void AddReal(const char* name, char abbr, bool optional = false, size_t quantity = 1);
    bool Validate(int argc, const char** args);
    const map<string, vector<Options>> &GetOptions();

    ~Parser();

};

#endif // PARSER_H

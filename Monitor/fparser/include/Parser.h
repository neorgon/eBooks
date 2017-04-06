#ifndef PARSER_H
#define PARSER_H
#include<vector>
#include<stdio.h>
#include<iostream>
#include<string>
#include<exception>
#include <algorithm>


#include<Options.h>
#include<Rules.h>
#include<Exceptions.h>

class Parser
{
    vector<Rules> rules;
    vector<string> tokens;
    vector<Options> options;
    size_t GetLenght(const char* source);
    void CopyToken(char *token, const char* source, size_t len);
    void AddRule(const string &name, const string &abrv, PType type, bool optional, size_t iquantity = 1);
    bool IsValueString(string);
    bool IsValueBool(string);
public:
    void AddBool(const string& name, string abrv, bool optional, size_t iquantity = 1);
    void AddInteger(const string& name, string abrv, bool optional, size_t iquantity = 1);
    void AddLabel(const string& name, string abrv, bool optional, size_t iquantity = 1);
    void AddList(const string& name, string abrv, bool optional, size_t iquantity = 1);
    void AddReal(const string& name, string abrv, bool optional, size_t iquantity = 1);
    void AddString(const string& name, string abrv, bool optional, size_t iquantity = 1);
    void PrintRules() const;//
    void Scanner(int argc, char** args);
    void PrintTokens() const;//
    void LexicalAnalyzer();
    void PrintOptions() const;//
    void Help() const; //
    void Analysing();
    bool IsValueLabel(const string&) const;
    bool IsValueReal(const string&) const;
    bool IsValueInteger(const string&) const;
    Parser();
    ~Parser();
};

#endif // PARSER_H

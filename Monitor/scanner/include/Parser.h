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

    bool SetBool(const string &);
    string SetInteger(const string &);
    string SetLabel(const string &);
    Options* SetList(const string &);
    string SetReal(const string &);
    string SetString(const string &);

public:
    void AddInteger(const char* name, char abbr, bool optional = false, size_t quantity = 1);
    void AddReal(const char* name, char abbr, bool optional = false, size_t quantity = 1);
    bool Validate(int argc, const char** args);

    void Print();
    ~Parser();

    /*
     * Only for testing
     */

    /*vector<Rules> rules;
    vector<string> tokens;
    vector<Options> options;
    size_t GetLenght(const char* source);
    void CopyToken(char *token, const char* source, size_t len);
    void AddRule(const string &name, const string &abrv, PType type, bool optional, size_t iquantity = 1);

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
    bool VerifySemantic()const;
    bool IsValueLabel(const string&) const;
    bool IsValueReal(const string&) const;
    bool IsValueInteger(const string&) const;
    bool Validate() const;
    ~Parser();*/
};

#endif // PARSER_H

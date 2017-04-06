#ifndef RULES_H
#define RULES_H

#include <string>

#include "../PType.h"

using namespace std;

class Rules
{
    string name;
    string abbr;
    PType type;
    bool optional;
    size_t quantity;
public:
    Rules(const string&, string, PType, bool, size_t);
    string GetName() const;
    PType GetType() const;
    string GetAbbr() const;
    string GetTypeName() const;
    struct Finder {
        string token;
        Finder(const string &t) : token {t} {};
        bool operator()(const Rules &rule) const
        {
            return rule.name.compare(token) == 0 || rule.abbr.compare(token) == 0;
        }
    };
    ~Rules();
};


#endif // RULES_H

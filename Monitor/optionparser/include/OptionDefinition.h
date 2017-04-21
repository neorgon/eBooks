#ifndef OPTIONDEFINITION_H
#define OPTIONDEFINITION_H

#include<string>

#include "OptionType.h"

using namespace std;

class OptionDefinition
{
    string name;
    string abbr;
    OptionType type;
    bool optional;

    public:
        OptionDefinition(const string &n, const string &abbr, OptionType t, bool o);
        virtual ~OptionDefinition();

        const string GetName() const;
        const string GetAbbr() const;
        const OptionType GetType() const;
        const bool GetOptional() const;

        struct Finder {
            string token;
            Finder(const string &t) : token {t} {};
            bool operator()(const OptionDefinition &od) const
            {
                return od.name.compare(token) == 0 || od.abbr.compare(token) == 0;
            }
        };
};

#endif // OPTIONDEFINITION_H

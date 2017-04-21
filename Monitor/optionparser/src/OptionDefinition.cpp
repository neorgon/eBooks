#include "../include/OptionDefinition.h"

OptionDefinition::OptionDefinition(const string &n, const string &a, OptionType t, bool o)
    : name {n}, abbr {a}, type {t}, optional {o}
{

}

OptionDefinition::~OptionDefinition()
{
    //dtor
}

const string OptionDefinition::GetName() const
{
    return name;
}

const string OptionDefinition::GetAbbr() const
{
    return abbr;
}

const OptionType OptionDefinition::GetType() const
{
    return type;
}

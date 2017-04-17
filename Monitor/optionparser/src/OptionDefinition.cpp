#include "OptionDefinition.h"

OptionDefinition::OptionDefinition(const string &n, const string &a, OptionType t, bool o, size_t q)
    : name {n}, abbr {a}, type {t}, optional {o}, quantity {q}
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

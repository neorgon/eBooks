#include "OptionDefinition.h"

OptionDefinition::OptionDefinition(const string &n, const string &a, OptionType t, bool o, size_t q)
    : name {n}, abbr {a}, type {t}, optional {o}, quantity {q}
{

}

OptionDefinition::~OptionDefinition()
{
    //dtor
}

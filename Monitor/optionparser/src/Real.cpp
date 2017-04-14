#include "Real.h"

Real::Real(const string& name, const char abbr, const OptionType type, const string& strValue)
:name{name}, abbr{abbr}, type{type}, strValue{strValue}
{
    value=stof(strValue);
}

string Real::GetName()const
{
    return name;
}

char Real::GetAbbbr()const
{
    return abbr;
}

string Real::GetValueString()const
{
    return strValue;
}

OptionType Real::GetType()const
{
    return type;
}

float Real::GetValue()const
{
    return value;
}


Real::~Real()
{
    //dtor
}

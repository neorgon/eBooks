#include "Boolean.h"

Boolean::Boolean(const string& name, const char abbr, const OptionType type, const string& strValue="true")
:name{name}, abbr{abbr}, type{type}, strValue{strValue}
{
    if (strValue=="false")
        value=0;
    if (strValue=="true"||strValue==""||strValue==" ")
        value=1;
}

string Boolean::GetName()const
{
    return name;
}

char Boolean::GetAbbbr()const
{
    return abbr;
}

string Boolean::GetValueString()const
{
    return strValue;
}

OptionType Boolean::GetType()const
{
    return type;
}

bool Boolean::GetValue()const
{
    return value;
}

Boolean::~Boolean()
{
    //dtor
}

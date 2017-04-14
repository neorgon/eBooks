#include "List.h"

List::List(const string& name, const char abbr, const OptionType type, const vector<IOptionType*>& value)
:name{name}, abbr{abbr}, type{type}, value{value}
{

}

string List::GetName() const
{
    return name;
}

char List::GetAbbbr() const
{
    return abbr;
}

string List::GetValueString() const
{
    return "";
}

OptionType List::GetType() const
{
    return type;
}

vector<IOptionType*> List::GetValue()const
{
    return value;
}

List::~List()
{
    //dtor
}

#include "Rules.h"

Rules::Rules(const string &n, string a, PType t, bool o, size_t i)
: name {n}, abrv {a}, type {t}, optional {o}, iquantity {i}
{

}

string Rules::GetName() const
{
    return name;
}

PType Rules::GetType() const
{
    return type;
}

string Rules::GetAbrv() const
{

    return abrv;
}
string Rules::GetTypeName() const
{

    switch (type)
    {
        case PType::Bool:
            return "<Boolean>";
            break;
        case PType::Integer:
            return "<Integer>";
            break;
        case PType::Label:
            return "<Label>";
            break;
        case PType::List:
            return "<List>";
            break;
        case PType::Real:
            return "<Real>";
            break;
        case PType::String:
            return "<String>";
            break;

        default:
            return "<Unknow>";
            break;
    }
}

Rules::~Rules()
{
    //dtor
}

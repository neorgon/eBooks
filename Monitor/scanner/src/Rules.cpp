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

Rules::~Rules()
{
    //dtor
}

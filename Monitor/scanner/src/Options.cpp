#include "Options.h"

Options::~Options()
{
    //dtor
}

string Options::GetTypeName() const
{
    switch (type)
    {
        case PType::Bool:
            return "Boolean";
            break;
        case PType::Integer:
            return "Integer";
            break;
        case PType::Label:
            return "Label";
            break;
        case PType::List:
            return "List";
            break;
        case PType::Real:
            return "Real";
            break;
        case PType::String:
            return "String";
            break;

        default:
            return "Unknow";
            break;
    }
}

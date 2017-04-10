#include "Options.h"

Options::Options(const string &n, char a, PType t, const string &v)
: name{n}, abbr{a}, type{t}, value{v}
{
    switch (t)
    {
        case PType::Bool:
        {

        }
        break;
        case PType::Integer:
        {
            size_t sz;

            Integer = stoi(v, &sz);
            if(sz != v.length())
                throw; //Exceptions("Is not a valid integer.");
        }
        break;
        case PType::Label:
        {

        }
        break;
        case PType::List:
        {

        }
        break;
        case PType::Real:
        {
            size_t sz;

            Real = stod (v, &sz);
            if(sz != v.length())
                throw; //Exceptions("Is not a valid float.");
        }
        break;
        case PType::String:
        {
            String = "\"" + value + "\"";
        }
        break;
    }

}

string Options::GetName() const
{
    return name;
}

string Options::GetValue()
{
    return value;
}

PType Options::GetType() const
{
    return type;
}

void Options::SetValue()
{
    switch(type)
    {
        case PType::Bool:
        break;
        case PType::Integer:
            {
                int i = GetDataValue<int, PType::Integer>(value);
                int* p = &i;
                Value = (void*)(p);
            }
        break;
        case PType::Label:
        break;
        case PType::List:
        break;
        case PType::Real:
            {
                double d = GetDataValue<int, PType::Real>(value);
                double* p = &d;
                Value = (void*)(p);
            }
        break;
        case PType::String:
        break;
    }
}

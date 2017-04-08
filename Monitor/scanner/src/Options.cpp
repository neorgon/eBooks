#include "Options.h"

/*
Options::Options(const string& n, PType t)
: name{n}, type{t}
{

}

void Options::SetValue(const string& val)
{
    value = val;
}

string Options::GetName() const
{
    return name;
}

PType Options::GetType() const
{
    return type;
}

string Options::GetValue() const
{
    return value;
}

void Options::SetValueType(PType t,const string& val)
{
    switch(t)
    {
        case PType::Bool:
            resBool=("true" == val)?true:false;
            break;
        case PType::Integer:
            resInt = atoi(val.c_str());
            break;
        case PType::Real:
            resDouble = atof(val.c_str());
            break;
        case PType::String:
            resString = val;
            break;
        case PType::Label:
            resLabel = val;
            break;
    }
}

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
*/

//Options::Options(const string &n, char a, PType t, void* v)
//: name{n}, abbr{a}, type{t}/*, value{v}*/
//{

//}

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

string Options::GetValue() const
{
    return value;
}

//int* Options::GetInteger() const
//{
//    return (int*)value;
//}

//double* Options::GetReal() const
//{
//    return (double*)value;
//}

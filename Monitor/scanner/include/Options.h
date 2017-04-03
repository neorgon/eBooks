#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

#include "../PType.h"

using namespace std;

class Options
{
    string name;
    PType type;
    string value;

    public:
        Options(const string& n, PType t) : name{n}, type{t} {};
        virtual ~Options();
        void SetValue(string val) { value = val; }
        string GetName() const { return name; }
        PType GetType() const { return type; }
        string GetTypeName() const;
        string GetValue() const { return value; }
};

#endif // OPTIONS_H

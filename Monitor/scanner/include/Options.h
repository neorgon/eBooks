#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <vector>
#include "../PType.h"
#include<../exceptions/SemanticException.h>
#include<../exceptions/SyntaxException.h>

using namespace std;

class Options
{
    string name;
    char abbr;
    PType type;
    string value;
    void* Value;
    bool Boolean;
    int Integer;
    vector<Options> List;
    double Real;
    string String;

    public:
        Options(const string &, char, PType, const string &);
        string GetName() const;
        string GetValue();
        PType GetType() const;
        template <class T, PType type>
        T GetDataValue(const string v) const
        {
            if (type == PType::Integer)
                return Integer;
            if (type == PType::Real)
                return Real;
        }
        void SetValue();
};

#endif // OPTIONS_H

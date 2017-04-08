#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <vector>
#include "../PType.h"

using namespace std;

class Options
{
    string name;
    char abbr;
    PType type;
    string value;
    bool Boolean;
    int Integer;
    vector<Options> List;
    double Real;
    string String;

    public:
        //Options(const string &, char, PType, void*);
        Options(const string &, char, PType, const string &);
        string GetName() const;
        string GetValue() const;
        PType GetType() const;
        bool GetBool() const;
        int GetInteger() const;
        double GetReal() const;
        string GetString() const;
        //int* GetInteger() const;
        //double* GetReal() const;
};


/*
class Options
{
string name;
PType type;
string value;
int resInt;
double resDouble;
string resString;
string resLabel;
bool resBool;
public:
    Options(const string&, PType);
    virtual ~Options();
    void SetValue(const string&);
    string GetName() const;
    PType GetType() const;
    string GetTypeName() const;
    string GetValue() const;
    void SetValueType(PType ,const string& );
};
*/

#endif // OPTIONS_H

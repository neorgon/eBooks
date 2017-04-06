#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>
#include <stdlib.h>
#include "../PType.h"

using namespace std;

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

#endif // OPTIONS_H

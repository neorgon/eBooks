#ifndef LIST_H
#define LIST_H

#include<vector>

#include "IOptionType.h"

class List:public IOptionType
{
    string name;
    char abbr;
    OptionType type;
    vector<IOptionType*> value;
public:
    List(const string& name, const char abbr, const OptionType type, const vector<IOptionType*>& Value);
    string GetName() const override;
    char GetAbbr() const override;
    string GetValueString() const override;
    OptionType GetType() const override;
    vector<IOptionType*> GetValue()const;
    ~List();
};

#endif // LIST_H

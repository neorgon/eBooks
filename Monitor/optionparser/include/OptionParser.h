#ifndef OPTIONPARSER_H
#define OPTIONPARSER_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class OptionParser
{
    vector<string> tokens;
    //vector<Option> options;
    public:
        OptionParser(int argc, const char** args);
        const string GetToken(int i) const;
        virtual ~OptionParser();

    protected:

    private:
};

#endif // OPTIONPARSER_H

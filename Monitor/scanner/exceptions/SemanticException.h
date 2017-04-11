#ifndef SEMANTICEXCEPTION_H
#define SEMANTICEXCEPTION_H

#include<exception>

using namespace std;

class SemanticException:public exception
{
    const char* msg;
    public:
        SemanticException(const char*);
        const char* what() const throw();
};

#endif // SEMANTICEXCEPTION_H

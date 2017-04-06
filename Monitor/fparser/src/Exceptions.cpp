#include "Exceptions.h"

Exceptions::Exceptions(char* exceptionMsg )
{
    this->exceptionMessage = exceptionMsg;
}

const char* Exceptions::what() const throw()
{
    return exceptionMessage;
}

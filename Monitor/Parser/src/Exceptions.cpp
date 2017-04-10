#include "Exceptions.h"

Exceptions::Exceptions(char * exception_msg)
{
    this->exception_message = exception_msg;
}

const char* Exceptions::what() const throw()
{
    return exception_message;
}

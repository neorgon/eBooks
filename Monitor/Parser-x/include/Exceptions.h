#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <cstdio>

using namespace std;

class Exceptions:public exception
{
    private:
		char * exception_message;
	public:
		Exceptions(char * exception_msg);
		const char* what() const throw();
};

#endif // EXCEPTIONS_H

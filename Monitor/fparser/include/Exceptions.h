#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <cstdio>

using namespace std;

class Exceptions:public exception
{
    private:
		char* exceptionMessage;
	public:
		Exceptions(char*);
		const char* what() const throw();
};

#endif // EXCEPTIONS_H

#include <iostream>
#include <exception>
#include <string>

using namespace std;

class my_exception: public exception
{
    string msg;

    public:
        my_exception(const string &s) : msg(s) {}
        const char* what() const noexcept override
        {
            return msg.c_str();
        }
};

int main()
{
    try
    {
        int x = 2;
        throw my_exception("error 4");
    }
    catch(const exception &e)
    {
        cerr << e.what() << endl;
    }
    return 0;
}

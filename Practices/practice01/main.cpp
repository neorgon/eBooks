#include <iostream>
#include <string>

using namespace std;

void get_data(const string &data, string &key, string &value)
{
    for(auto c : data)
    {
        if(c != '=')
            key.push_back(c);
        else
            break;
    }
    for(auto c = data.rbegin(); c != data.rend(); ++c)
    {
        if(*c != '=')
            value.push_back(*c);
        else
            break;
    }
}

int main()
{
    string s = "nombre=juan";
    auto len = s.length();

    for(auto i = s.rbegin(); i != s.rend() ; ++i)
        cout << *i;

    cout << endl;

    for(auto i : s)
        cout << i;

    cout << endl;

    string key;
    string value;

    get_data("edad=15", key, value);

    cout << key << " = " << value << endl;
    return 0;
}

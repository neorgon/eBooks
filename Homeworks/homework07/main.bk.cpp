#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<class TElement>
class IElement
{
    public:
        virtual TElement GetData() const = 0;
};

template<class TElement>
class Element : public IElement<int>
{
    TElement data;

    public:
        Element(TElement e) : data{e} {}
        int GetData() const
        {
            return data;
        }
};

/*class Vector
{
    vector<IElement*> elements;
};*/

class Parser
{
    vector<char> operators;
    vector<IElement<int>*> elements;

    public:
        Parser(const char* s);
};

Parser::Parser(const char* s)
{
    string s_number = "";
    for (int i = 0; s[i] != '\0'; i++)
    {
        switch (s[i])
        {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
                operators.push_back(s[i]);
            break;
            case '|':
                if (!s_number.empty())
                {
                    IElement<int>* e = new Element<int>(stoi(s_number));
                    elements.push_back(e);
                    s_number = "";
                }
            break;
            case '0' ... '9':
                s_number += s[i];
            break;
        }
    }

    for (auto &e : elements)
        cout << e->GetData() << endl;
}

vector<char> operators;
vector<int> my_stack;

template<class element>
element add(element a, element b)
{
    return a + b;
}

template<class element>
element subtract(element a, element b)
{
    return a - b;
}

template<class element>
element multiply(element a, element b)
{
    return a * b;
}

template<class element>
element divide(element a, element b)
{
    if (b == 0) return 0;
    return a / b;
}

template<class element>
element my_modulus(element a, element b)
{
    return a % b;
}

template<class element>
element calculate(element a, element b, element (*operation)(element, element))
{
    return (*operation)(a, b);
}

int main(/*int argc, char* args[]*/)
{
    //Parser p("6|8|+|15|*|2|/");

    operators.push_back('+');
    operators.push_back('*');
    operators.push_back('/');
    my_stack.push_back(6);
    my_stack.push_back(8);
    my_stack.push_back(15);
    my_stack.push_back(2);

    while(my_stack.size() > 1 && !operators.empty())
    {
        int a = my_stack.front();
        my_stack.erase(my_stack.begin());
        int b = my_stack.front();
        my_stack.erase(my_stack.begin());
        char op = operators.front();
        operators.erase(operators.begin());
        switch (op)
        {
            case '+':
                my_stack.insert(my_stack.begin(), calculate(a, b, add));
                break;
            case '-':
                my_stack.insert(my_stack.begin(), calculate(a, b, subtract));
                break;
            case '*':
                my_stack.insert(my_stack.begin(), calculate(a, b, multiply));
                break;
            case '/':
                my_stack.insert(my_stack.begin(), calculate(a, b, divide));
                break;
            case '%':
                my_stack.insert(my_stack.begin(), calculate(a, b, my_modulus));
                break;
        }
    }

    for (auto i = my_stack.begin(); i < my_stack.end(); i++)
        cout << *i << endl;

    return 0;
}

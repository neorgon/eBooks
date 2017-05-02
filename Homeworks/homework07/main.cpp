#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

class Parser
{
    vector<char> operators;
    vector<int> elements;

    public:
        Parser(const char* s);
        void Calculate();
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
                    int e = (stoi(s_number));
                    elements.push_back(e);
                    s_number = "";
                }
            break;
            case '0' ... '9':
                s_number += s[i];
            break;
        }
    }
}

void Parser::Calculate()
{
    while(elements.size() > 1 && !operators.empty())
    {
        int a = elements.front();
        elements.erase(elements.begin());
        int b = elements.front();
        elements.erase(elements.begin());
        char op = operators.front();
        operators.erase(operators.begin());
        switch (op)
        {
            case '+':
                elements.insert(elements.begin(), calculate(a, b, add));
                break;
            case '-':
                elements.insert(elements.begin(), calculate(a, b, subtract));
                break;
            case '*':
                elements.insert(elements.begin(), calculate(a, b, multiply));
                break;
            case '/':
                elements.insert(elements.begin(), calculate(a, b, divide));
                break;
            case '%':
                elements.insert(elements.begin(), calculate(a, b, my_modulus));
                break;
        }
    }

    for (auto i = elements.begin(); i < elements.end(); i++)
        cout << *i << endl;
}

int main(/*int argc, char* args[]*/)
{
    Parser p("6|8|+|15|*|2|/");
    p.Calculate();

    return 0;
}

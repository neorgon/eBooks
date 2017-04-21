#include <iostream>
#include <vector>

using namespace std;

vector<char> operators;
vector<int> my_stack;
vector<void(*)()> functions;

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

/*
int calculate(int a, int b, char o)
{
    switch(o)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '%': return a % b;
    }

    return 0;
}
*/

template<class element>
element calculate(element a, element b, element (*operation)(element, element))
{
    return (*operation)(a, b);
}

void addOperation(void(*function)())
{
    functions.push_back(function);
}

int main(/*int argc, char* args[]*/)
{
    operators.push_back('+');
    operators.push_back('*');
    operators.push_back('/');
    addOperation(void(*add)());
    functions.push_back(void(*multiply)());
    functions.push_back(void(*divide)());
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
        /*char op = operators.front();
        operators.erase(operators.begin());
        int res;
        switch (op)
        {
            case '+':
                res = calculate(a, b, add);
                break;
            case '-':
                res = calculate(a, b, subtract);
                break;
            case '*':
                res = calculate(a, b, multiply);
                break;
            case '/':
                res = calculate(a, b, divide);
                break;
            case '%':
                res = calculate(a, b, my_modulus);
                break;
        }
        */
        my_stack.insert(my_stack.begin(), calculate(a, b, functions.front()));
        functions.erase(functions.begin());
    }

    for (auto i = my_stack.begin(); i < my_stack.end(); i++)
        cout << *i << endl;

    return 0;
}

#include <iostream>
#include <vector>

using namespace std;

vector<char> operators;
vector<int> my_stack;

int calculate(int a, int b, char o)
{
    switch(o)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }

    return 0;
}

int main(/*int argc, char* args[]*/)
{
    operators.push_back('+');
    operators.push_back('*');
    operators.push_back('/');
    my_stack.push_back(6);
    my_stack.push_back(8);
    my_stack.push_back(15);
    my_stack.push_back(2);

    while(my_stack.size() > 1 && !operators.empty())
    {
        int o1 = my_stack.front();
        my_stack.erase(my_stack.begin());
        int o2 = my_stack.front();
        my_stack.erase(my_stack.begin());
        char op = operators.front();
        operators.erase(operators.begin());
        my_stack.insert(my_stack.begin(), calculate(o1, o2, op));
    }

    for (auto i = my_stack.begin(); i < my_stack.end(); i++)
        cout << *i << endl;

    return 0;
}

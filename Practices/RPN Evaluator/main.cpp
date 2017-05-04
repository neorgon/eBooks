#include <iostream>
#include <unordered_map>
#include <stack>
#include <vector>

using namespace std;

class RpnEval final
{
    unordered_map<string, int(*)(int, int)> ops;
    void init()
    {
        add("+", [](int a, int b)
        {
            return a + b;
        });
        add("*", [](int a, int b)
        {
            return a * b;
        });
    }
    vector<string> get_ops(const string &s)const
    {
        vector<string> ops;
        string aux;

        for (auto k : s)
        {
            if (k == ' ')
            {
                ops.push_back(aux);
                aux.clear();
            }
            else
            {
                aux.push_back(k);
            }
        }
        ops.push_back(aux);
        return ops;
    }

    bool verify_if_is_number(const string &s) const
    {
        for (auto k : s)
        {
            if (!isdigit(k))
                return false;
            return true;
        }
    }

    void process(const string &e, stack<int> &ss) const
    {
        auto it = ops.find(e);
        if (it == ops.end())
            throw "Unsupported operator";
        auto f = it->second;
        auto b = ss.top();
        ss.pop();
        auto a = ss.top();
        ss.pop();
        auto c = f(a, b);
        ss.push(c);
    }

    public:
        RpnEval()
        {
            init();
        }
        void add(const string &op, int (*f)(int, int))
        {
            ops[op] = f;
        }
        int eval(const string &s) const
        {
            stack<int> ss;
            auto exp =  get_ops(s);
            for (auto &e : exp)
            {
                bool is_number = verify_if_is_number(e);
                if (is_number)
                    ss.push(stoi(e));
                else
                    process(e, ss);
            }

            return ss.top();
        }
};

int main()
{
    RpnEval e;
    cout << e.eval("6 8 + 2 *") << endl;

    return 0;
}

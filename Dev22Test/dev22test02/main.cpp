#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;

vector<string> explode(string const &s, char delim)
{
    vector<string> result;
    istringstream iss(s);

    for (string token; getline(iss, token, delim); )
    {
        result.push_back(move(token));
    }

    return result;
}

struct dino
{
    vector<string> tokens;
    map<string, int> vars;
    stack<int> my_stack;

    vector<string> execute(const vector<string> &v)
    {
        vector<string> to_execute;
        map<string, int> &cvars = vars;
        stack<int> &cstack = my_stack;
        bool go = true;

        for (auto &e : v)
        {
            tokens = explode(e, ' ');

            if (tokens[0].compare("PRINTLN_TEXT") == 0 && go)
            {
                size_t pos = e.find(" ");
                string texto = e.substr(pos + 1);
                to_execute.push_back(texto);
            }
            if (tokens[0].compare("LET") == 0 && go)
            {
                vars[tokens[1]] = stoi(tokens[2]);
            }
            if (tokens[0].compare("PRINTLN_VAR") == 0 && go)
            {
                bool is_var = false;
                string this_var = tokens[1];
                for_each(
                    vars.begin(), vars.end(),
                    [this_var, &is_var, &to_execute](const auto &s)
                    {
                        if (s.first.compare(this_var) == 0)
                        {
                            is_var = true;
                            to_execute.push_back(to_string(s.second));
                        }
                    }
                );
                if (!is_var)
                {
                    to_execute.push_back("[Unknown variable " + this_var + "]");
                }
            }
            if (tokens[0].compare("INC") == 0 && go)
            {
                bool is_var = false;
                string this_var = tokens[1];
                for_each(
                    vars.begin(), vars.end(),
                    [this_var, &is_var, &cvars](const auto &s)
                    {
                        if (s.first.compare(this_var) == 0)
                        {
                            is_var = true;
                            cvars[this_var]++;
                        }
                    }
                );
                if (!is_var)
                {
                    to_execute.push_back("[Unknown variable " + this_var + "]");
                }
            }
            if (tokens[0].compare("PUSH_VAL") == 0 && go)
            {
                my_stack.push(stoi(tokens[1]));
            }
            if (tokens[0].compare("POP") == 0 && go)
            {
                string this_var = tokens[1];
                int value = my_stack.top();
                my_stack.pop();
                for_each(
                    vars.begin(), vars.end(),
                    [this_var, value, &cvars](const auto &s)
                    {
                        if (s.first.compare(this_var) == 0)
                        {
                            cvars[this_var] = value;
                        }
                    }
                );
            }
            if (tokens[0].compare("PUSH_VAR") == 0 && go)
            {
                string this_var = tokens[1];
                for_each(
                    vars.begin(), vars.end(),
                    [this_var, &cstack](const auto &s)
                    {
                        if (s.first.compare(this_var) == 0)
                        {
                            cstack.push(s.second);
                        }
                    }
                );
            }
            if (tokens[0].compare("SUM") == 0 && go)
            {
                int a = my_stack.top();
                my_stack.pop();
                int b = my_stack.top();
                my_stack.pop();
                my_stack.push(a + b);
            }
            if (tokens[0].compare("END_IFEQ") == 0)
            {
                go = true;
            }
            if (tokens[0].compare("IFEQ") == 0)
            {
                string this_var = tokens[1];
                int value = stoi(tokens[2]);
                for_each(
                    vars.begin(), vars.end(),
                    [this_var, value, &go](const auto &s)
                    {
                        if (s.first.compare(this_var) == 0)
                        {
                            if (s.second == value)
                                go = true;
                            else
                                go = false;
                        }
                    }
                );
            }
        }

        return to_execute;
    }
};


template <typename T>
void show(size_t n, const T& r)
{
       cout << "**********************************************\n";
       cout << "TEST " << n << "\n";

       for (auto& i : r)
              cout << i << "\n";
}

bool test_1()
{
       dino dex;

       auto r = dex.execute(vector<string> {
              "PRINTLN_TEXT HELLO WORLD",
              "PRINTLN_TEXT MI PRIMER PROGRAMA EN DINO"
       });

       show(1, r);

       return r[0] == "HELLO WORLD" && r[1] == "MI PRIMER PROGRAMA EN DINO";
}

bool test_2()
{
       dino dex;

       auto r = dex.execute(vector<string> {
              "LET EDAD 37",
              "PRINTLN_VAR A",
              "PRINTLN_VAR EDAD"
       });

       show(2, r);

       return r[0] == "[Unknown variable A]" && r[1] == "37";
}

bool test_3()
{
       dino dex;

       auto r = dex.execute(vector<string> {
              "LET NUMERO 4",
              "INC NUM",
              "INC NUMERO",
              "PRINTLN_VAR NUMERO"
       });

       show(3, r);

       return r[0] == "[Unknown variable NUM]" && r[1] == "5";
}

bool test_4()
{
       dino dex;

       auto r = dex.execute(vector<string> {
              "LET VALOR_TOP 0",
              "PUSH_VAL 10",
              "PUSH_VAL 20",
              "PUSH_VAL 40",
              "POP VALOR_TOP",
              "PRINTLN_VAR VALOR_TOP",
              "POP VALOR_TOP",
              "PRINTLN_VAR VALOR_TOP"
       });

       show(4, r);

       return r[0] == "40" && r[1] == "20";
}

bool test_5()
{
       dino dex;

       auto r = dex.execute(vector<string> {
              "LET VALOR1 10",
              "LET VALOR2 20",
              "LET R 0",
              "PUSH_VAR VALOR2",
              "PUSH_VAL 50",
              "PUSH_VAR VALOR1",
              "POP R",
              "PRINTLN_VAR R",
              "POP R",
              "PRINTLN_VAR R"
       });

       show(5, r);

       return r[0] == "10" && r[1] == "50";
}

bool test_6()
{
       dino dex;

       auto r = dex.execute(vector<string> {
              "LET VALOR1 13",
              "LET VALOR2 14",
              "LET RESULT 0",
              "PUSH_VAR VALOR1",
              "PUSH_VAR VALOR2",
              "PUSH_VAL 15",
              "SUM",
              "SUM",
              "POP RESULT",
              "PRINTLN_VAR RESULT"
       });

       show(6, r);

       return r[0] == "42";
}

bool test_7()
{
       dino dex;

       auto r = dex.execute(vector<string> {
              "LET I 0",
              "INC I",
              "INC I",
              "IFEQ I 2",
              "INC I",
              "INC I",
              "END_IFEQ",
              "IFEQ I 8",
              "INC I",
              "INC I",
              "END_IFEQ",
              "PRINTLN_VAR I"
       });

       show(7, r);

       return r[0] == "4";

}

int main()
{
       int passed = 0;

       try
       {
            passed += test_1();
            passed += test_2();
            passed += test_3();
            passed += test_4();
            passed += test_5();
            passed += test_6();
            passed += test_7();
       }
       catch (const exception& ex)
       {
           cerr << "EXCEPTION: " << ex.what() << "\n";
       }
       catch (const char*  msg)
       {
           cerr << "ERROR: " << msg << "\n";
       }

       cout << "FINAL SCORE: [" << passed << " / 6]\n";
}


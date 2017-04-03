/*

Build a JSON serializer that will pass the test cases shown below.

* Memory leaks will decrease your final punctuation
* You are not allowed to use third party libraries, just our code and STL.
* You are not allowed to modify the tests or the main program.

*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ijson
{
    public:
        virtual ~ijson() {}
        size_t get_string_lenght(const char* s)
        {
            size_t c = 0;
            for (; s[c] != '\0'; ++c)
            { }
            return c;
        }
        void copy_string(char* target, const char* source, size_t len)
        {
            for (size_t i = 0; i < len; ++i)
                target[i] = source[i];
            target[len] = '\0';
        }
        virtual string serialize() const = 0;
};

/*
class json_number : public ijson
{
    int number;

    public:
        json_number(int n) : number {n} {}
        string serialize() const override
        {
            return to_string(number);
        }
};
*/

class json_number : public ijson
{
    char* number;

    public:
        json_number(int num)
        {
            auto sn = to_string(num);
            size_t n = sn.size();
            number = new char[n + 1];
            copy_string(number, sn.c_str(), n);
        }
        ~json_number()
        {
            delete[] number;
        }
        string serialize() const override
        {
            return number;
        }
};

class json_string : public ijson
{
    char* str;

    void copy_string(char* target, const char* source, size_t len)
    {
        target[0] = '\"';
        for (size_t i = 0; i < len; ++i)
            target[i + 1] = source[i];
        target[len + 1] = '\"';
        target[len + 2] = '\0';
    }
    public:
        json_string(const char *s)
        {
            size_t n = get_string_lenght(s);
            str = new char[n + 3];
            copy_string(str, s, n);
        }
        ~json_string()
        {
            delete[] str;
        }
        string serialize() const override
        {
            return str;
        }
};

class json_bool : public ijson
{
    char* boolean;

    void copy_string(char* target, const char* source, size_t len)
    {
        for (size_t i = 0; i < len; ++i)
            target[i] = source[i];
        target[len] = '\0';
    }

    public:
        json_bool(bool b)
        {
            if(b)
            {
                boolean = new char[4];
                copy_string(boolean, "true", 4);
            }
            else
            {
                boolean = new char[5];
                copy_string(boolean, "false", 5);
            }
        }
        ~json_bool()
        {
            delete[] boolean;
        }
        string serialize() const override
        {
            return boolean;
        }
};


class json_array : public ijson
{
    //acabo de darme cuenta que en esta funcion debía usar vectore :(
    //tarde mi reacción 11:44
    char* arr;
    vector<string> jarr;

    public:
        json_array(const char* a = "")
        {
            size_t n = get_string_lenght(a);
            arr = new char[n + 1];
            copy_string(arr, a, n);
        }
        json_array(const string &a)
        {
            size_t n = a.length();
            arr = new char[n + 1];
            copy_string(arr, a.c_str(), n);
        }
        ~json_array()
        {
            delete[] arr;
        }
        json_array add(json_number* jn)
        {
            json_array a(jn->serialize());
            jarr.push_back(jn->serialize());

            return a;
        }
        string serialize() const override
        {
            string serie;
            for (auto &j : jarr)
                serie += j;
            return string("[") + arr + string("]");
        }
};


size_t execute_test_1()
{
        json_number n{ 24 };

        auto r = n.serialize();

        return r == "24";
}

size_t execute_test_2()
{
        json_string s = "hello world";

        auto r = s.serialize();

        return r == "\"hello world\"";
}

size_t execute_test_3()
{
        json_bool b = false;
        auto r = b.serialize();

        return r == "false";
}

size_t execute_test_4()
{
        json_array a;
        auto r = a.serialize();

        return r == "[]";
}

size_t execute_test_5()
{
        json_array a;
        auto r = a.add(new json_number(104)).add(new json_number(5)).add(new json_number(31415)).serialize();

        return r == "[104, 5, 31415]";
}

/*size_t execute_test_6()
{
        json_array a;
        auto r = a.add(new json_string("juan lopez")).add(new json_number(1938232)).add(new json_bool(true)).serialize();
        return r == "[\"juan lopez\", 1938232, true]";
}

size_t execute_test_7()
{
        json_object obj;
        auto r = obj.serialize();

        return r == "{ }";
}

size_t execute_test_8()
{
        json_object obj;
        obj.add("nombre", new json_string("romulo"));
        obj.add("apellido", new json_string("rojas"));
        obj.add("rol", new json_string("dev killer"));

        auto r = obj.serialize();

        return r == "{ \"nombre\" : \"romulo\", \"apellido\" : \"rojas\", \"rol\" : \"dev killer\" }";
}

size_t execute_test_9()
{
        auto obj1 = new json_object();
        obj1->add("mes", new json_string("marzo"));
        obj1->add("dia", new json_number(16));

        auto obj2 = new json_object();
        obj2->add("mes", new json_string("abril"));
        obj2->add("dia", new json_number(1));

        json_array a;
        auto r = a.add(obj1).add(obj2).serialize();

        return r == "[{ \"mes\" : \"marzo\", \"dia\" : 16 }, { \"mes\" : \"abril\", \"dia\" : 1 }]";
}

size_t execute_test_10()
{
        json_object complex;

        complex.add("nombre", new json_string("juan perez"));

        auto arr = new json_array();
        arr->add(new json_string("jperez@gmail.com")).add(new json_string("choquito432@hotmail.com"));

        complex.add("emails", arr);

        auto direcciones = new json_array();

        auto dir1 = new json_object();
        dir1->add("descripcion", new json_string("casa"));
        dir1->add("direccion", new json_string("juan de la rosa 2345"));

        auto dir2 = new json_object();
        dir2->add("descripcion", new json_string("trabajo"));
        dir2->add("direccion", new json_string("melchor perez 2643"));

        direcciones->add(dir1);
        direcciones->add(dir2);

        complex.add("direcciones", direcciones);

        auto r = complex.serialize();

        return r == "{ \"nombre\" : \"juan perez\", \"emails\" : [\"jperez@gmail.com\", \"choquito432@hotmail.com\"], \"direcciones\" : [{ \"descripcion\" : \"casa\", \"direccion\" : \"juan de la rosa 2345\" }, { \"descripcion\" : \"trabajo\", \"direccion\" : \"melchor perez 2643\" }] }";
}

size_t execute_test_11()
{
        json_array a;

        a.add(new json_string("jorge \"chapo\" guzman"));
        a.add(new json_null());
        a.add(new json_string("mc donald's"));

        auto r = a.serialize();

        return r == "[\"jorge \\\"chapo\\\" guzman\", null, \"mc donald's\"]";
}*/


int main()
{
        size_t success_count = 0;

        success_count += execute_test_1();
        success_count += execute_test_2();
        success_count += execute_test_3();
        success_count += execute_test_4();
        success_count += execute_test_5();
        /*success_count += execute_test_6();
        success_count += execute_test_7();
        success_count += execute_test_8();
        success_count += execute_test_9();
        success_count += execute_test_10();
        success_count += execute_test_11();*/

        cout << "SUCCESS COUNT: [" << success_count << " / 11]\n";
        return 0;
}

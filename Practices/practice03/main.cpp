#include <iostream>

using namespace std;

class person
{
    string fn;
    string ln;
    size_t id; // En tipos primitivos no es necesario devolver un valor por referencia &

    public:

        person(const string &fn, const string &ln, size_t id) : fn(fn), ln(ln), id(id)
        {
            cout << "Hi ";
        }

        const string &get_firstname() const //Devuelve la misma copia de fn, no hace una copia de fn
        {
            return fn;
        }

        size_t get_id() const
        {
            return id;
        }

        string get_fullname() const // no se puede colocar const string & porque retornamos un el valor de objeto que se crea y se destruye en la misma linea 30
        {
            return fn + " " + ln;
        }
};

int main()
{
    person p {"Juan", "Perez", 1234};

    cout << p.get_firstname() << endl;
    cout << p.get_fullname() << endl;

    return 0;
}

#include <iostream>
#include <list> //consumen mucha memoria, son mas lentos de acceder a un elemento.

using namespace std;

void remove(list<string> &s, char c)
{
    for (auto i = s.begin(); i != s.end(); /*NOTHING*/)
    {
        if((*i)[0] == c)
            i = s.erase(i);
        else
            ++i;
    }
}

int main()
{
    list<int> p;
    cout << "P size: " << p.size() << endl;

    p.push_back(2);
    p.push_back(8);
    p.push_front(10); // Es más eficiente que los vectores lo mismo pasa con remover

    for (auto i = p.rbegin(); i != p.rend(); i++) //list<int>::iterator
        cout << *i << endl;

    cout << p.front() << endl;
    cout << p.back() << endl;

    list<string> dd = { "Monday", "Tuesday", "Wednesday", "Thrusday", "Friday", "Saturday", "Sunday" };

    remove(dd, 'T');

    for (auto &i : dd)
        cout << i << endl;

    return 0;
}

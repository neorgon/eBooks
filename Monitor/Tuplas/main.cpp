#include <iostream>
#include <tuple>

using namespace std;

int main()
{
    tuple<int, char, int> mytuple;
    ruta(1, 2, 3, 4);
    mytuple.push_back(make_tuple(1, 'V', 0));
    make_tuple(1, 0, 2);
    mytuple.push_back(make_tuple(1, 'H', 2));
    mytuple.push_back(make_tuple(2, 'V', 6));
    make_tuple(2, 6, 3);
    mytuple.push_back(make_tuple(2, 'H', 3));
    mytuple.push_back(make_tuple(3, 'V', 0));
    make_tuple(3, 0, 4);
    mytuple.push_back(make_tuple(3, 'H', 4));
    mytuple.push_back(make_tuple(4, 'V', 8));
    make_tuple(4, 8, 0);
    mytuple.push_back(make_tuple(4, 'H', 0));
    mytuple.push_back(make_tuple(5, 'V', 1));
    mytuple.push_back(make_tuple(5, 'H', 6));
    mytuple.push_back(make_tuple(6, 'V', 10));
    mytuple.push_back(make_tuple(6, 'H', 7));
    mytuple.push_back(make_tuple(7, 'V', 3));
    mytuple.push_back(make_tuple(7, 'H', 8));
    mytuple.push_back(make_tuple(8, 'V', 12));
    mytuple.push_back(make_tuple(8, 'H', 0));
    cout << "Hello world!" << endl;
    return 0;
}

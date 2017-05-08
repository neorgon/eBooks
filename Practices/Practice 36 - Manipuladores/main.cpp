#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    bool a = true;
    bool b = false;

    cout << boolalpha << a << endl;
    cout << b << endl;
    cout << noboolalpha << b << endl;

    for (int i = 1; i < 10'000'000; i *= 10)
        cout << setw(10) << i << endl;

    auto c = 299799.58326789;

    cout << setprecision(11) <<  c << "\n";
    cout << scientific << c << "\n";
    cout << fixed << c << "\n";

    auto f = 0xCAFE0102;

    cout << f << "\n";
    cout << hex << f << "\n";
    cout << dec << f << "\n";
    cout << hex << uppercase << f << "\n";
    cout << nouppercase << f << "\n";

    return 0;
}

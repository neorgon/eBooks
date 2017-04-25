#include <iostream>
#include <array>

using namespace std;

int main()
{
    array<string, 3> q;
    q[0] = "Jesus";
    q[1] = "Maria";
    q[2] = "Jose";

    for (auto i = q.begin(); i != q.end(); ++i)
        cout << *i << endl;

    return 0;
}

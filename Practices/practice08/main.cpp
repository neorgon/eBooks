#include <iostream>

using namespace std;

void show(const int* a, size_t n)
{
    while (n)
    {
        cout << *a++ << endl;
        n--;
        //*a = 2; cada elemento del puntero es constante
    }
}

void modify(int* const a, size_t n)
{
    for (int i=0; i<n; i++)
        a[i]++;
}

int main()
{
    int fib[] = {1,1,2,3,5,8,13};
    show(fib, 7);
    modify(fib, 7);
    show(fib, 7);

    return 0;
}

#include <iostream>
#include <string>

using namespace std;

template <class T>
struct point
{
    T x;
    T y;

    const T &get_x() const
    {
        return x;
    }

    const T &get_y() const
    {
        return y;
    }
};

template <typename T>
class my_vector
{
    T* elems;
    size_t count;
    size_t cap;

    void resize()
    {
        auto ncap = cap * 2;
        auto ne = new T[ncap];
        for (auto i = 0U; i < count; i++)
            ne[i] = elems[i];
        cap = ncap;
        delete[] elems;
        elems = ne;
    }

    public:
        my_vector() : elems{new T[4]}, count{0}, cap{4}
        {

        }
        ~my_vector()
        {
            delete[] elems;
        }
        size_t size() const noexcept
        {
            return count;
        }
        void push_back(const T &x)
        {
            if(cap == count)
            {
                resize();
            }
            elems[count++] = x;
        }
        const T &operator[](size_t index) const
        {
            return elems[index];
        }
        T &operator[](size_t index)
        {
            return elems[index];
        }
};

int main()
{
    point<int> p1 {4, 8};
    point<double> p2 {3.2, 8.4};

    cout << p1.get_x() << "; " << p1.get_y() << endl;
    cout << p2.get_x() << endl;

    my_vector<int> x;
    my_vector<string> y;

    for (int i = 0; i < 100; i++)
        x.push_back(i);

    for (int i = 0; i < 50; i++)
        y.push_back(to_string(i));

    auto xlen = x.size();
    for (auto i = 0U; i < xlen; i++)
        cout << x[i] << endl;

    auto ylen = y.size();
    for (auto i = 0U; i < ylen; i++)
        cout << y[i] << endl;

    return 0;
}

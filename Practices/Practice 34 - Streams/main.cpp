#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct point
{
    int x, y;
};

struct car
{
    char brand[16];
    char model[16];
    short year;
};

class car_reader
{
    mutable ifstream f;

    public:
        car_reader(const string &s) : f {s, ios::binary} {}
        size_t get_count() const
        {
            f.seekg(0, ios::end);
            auto size = f.tellg();
            return size / sizeof(car);
        }

        car operator[](size_t idx)const
        {
            car c;
            size_t pos = idx * sizeof(car);
            f.seekg(pos, ios::beg);
            f.read(reinterpret_cast<char*>(&c), sizeof(car));

            return c;
        }
};

ostream &operator<<(ostream &os, const point &p)
{
    os << p.x << ", " << p.y;

    return os;
}

istream &operator>>(istream &is, point &p)
{
    string line;
    getline(is, line);
    if (is.fail()) return is;
    auto idx = line.find(',');
    auto xs = line.substr(0, idx);
    auto ys = line.substr(idx + 1);
    p.x = stoi(xs);
    p.y = stoi(ys);

    return is;
}

int main()
{
    vector<car> cs {
        car { "VW", "Peta", 1969 },
        car { "Suzuki", "Alto", 2015 },
        car { "Kia", "Rio", 2013 },
        car { "Jeep", "Cherokee", 2010 },
    };

    ofstream oc { "cars.bin", ios::binary };
    for (auto &i : cs)
        oc.write(reinterpret_cast<char*>(&i), sizeof(car));
    oc.close();

    car_reader cr { "cars.bin" };
    auto count = cr.get_count();
    for (int i = count - 1; i >= 0; i--)
    {
        car c = cr[i];
        cout << c.brand << " " << c.model << endl;
    }
    cout << count << endl;

    /*
    vector<point> pp { point{6,4}, point{8,5}, point{19,16}, point{20,20}  };
    ofstream opf { "points.txt" };
    for (auto &i : pp)
        opf << i << endl;

    ifstream ipf { "points.txt" };
    while (true)
    {
        point p;
        ipf >> p;
        if (ipf.fail()) break;
        cout << p << endl;
    }
    */
    /*
    vector<string> ms = { "ed sheeran", "dj sanke", "taylor swift", "maaron 5", "drake", "ariana grande", "lady gaga", "niki ninaj" };
    ofstream f { "to_dispose.txt" };

    if (f.fail()) return 0;
    for (auto &i : ms)
        f << i << endl;
    f.close();

    ifstream g { "to_dispose.txt" };
    if (g.fail())
    {
        cerr << "Falla\n";
        return 0;
    }
    while (true)
    {
        string aux;
        getline(g, aux);
        if (g.fail()) break;
        cout << aux << endl;
    }
    g.close();
    */

    return 0;
}

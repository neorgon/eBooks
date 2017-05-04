#include <iostream>
#include <set>
#include <vector>
#include <memory>

using namespace std;

class TrafficLight
{
    int row, column;
    char orientation;
    bool canCross;
    set<shared_ptr<TrafficLight>> NextTL;

    public:
        TrafficLight(int y, int x, char o, bool c = false) : row{y}, column{x}, orientation{o}, canCross{c}
        {
            //canCross may be initialize with a some uniform distribution.
        }
        void Show() const;
};

void TrafficLight::Show() const
{
    cout << "TL(" << row << "," << column << "," << orientation << ")\n";
}

class TrafficSimulator
{
    int maxTL;
    vector<shared_ptr<TrafficLight>> TL;

    public:
        TrafficSimulator(int t = 4);
        void Show() const;
};

void TrafficSimulator::Show() const
{
    for (auto &t : TL)
        t->Show();
}

TrafficSimulator::TrafficSimulator(int t)
{
    maxTL = t;

    for (int f = 1; f <= maxTL; f++)
        for (int c = 1; c <= maxTL; c++)
        {
            if (c == 1)
                c % 2 == 0 ? TL.push_back(make_shared<TrafficLight>(f, c, 'S')) : TL.push_back(make_shared<TrafficLight>(f, c, 'N'));
            else
                if (f == 1)
                    f % 2 == 0 ? TL.push_back(make_shared<TrafficLight>(f, c, 'O')) : TL.push_back(make_shared<TrafficLight>(f, c, 'E'));
                else
                {
                    f % 2 == 0 ? TL.push_back(make_shared<TrafficLight>(f, c, 'O')) : TL.push_back(make_shared<TrafficLight>(f, c, 'E'));
                    c % 2 == 0 ? TL.push_back(make_shared<TrafficLight>(f, c, 'S')) : TL.push_back(make_shared<TrafficLight>(f, c, 'N'));
                }
        }
}

int main()
{
    TrafficSimulator ts;
    ts.Show();

    return 0;
}

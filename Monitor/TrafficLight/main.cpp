#include <iostream>
#include <queue>
#include <memory>

using namespace std;

class Vehicle
{

};

class TrafficLight
{
    string ID;
    unsigned int maxQVehicles;
    bool light;
    queue<shared_ptr<Vehicle>> vehicles;

    public:
        TrafficLight(string id, unsigned int m, bool l = true) : ID{id}, maxQVehicles{m}, light{l} {}
        unsigned int GetNQueue();
        void EnQueue(const Vehicle &v);
        void DeQueue();
        size_t QueuePosition(const Vehicle &v);
        void MoveVehicles(unsigned int time);
};

unsigned int TrafficLight::GetNQueue()
{
    return vehicles.size();
}

void TrafficLight::EnQueue(const Vehicle &v)
{
    if (maxQVehicles < vehicles.size())
        vehicles.push(make_shared<Vehicle>(v));
}

void TrafficLight::DeQueue()
{
    vehicles.pop();
}

size_t TrafficLight::QueuePosition(const Vehicle &v)
{
    return 0;
}

void TrafficLight::MoveVehicles(unsigned int time)
{

}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

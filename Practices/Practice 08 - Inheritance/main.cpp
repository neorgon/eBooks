#include <iostream>

using namespace std;

class Vehicle
{
    string id;

    public:
        Vehicle(const string &id) : id{id} {}

        virtual ~Vehicle()
        {
            cout << "Bye V" << endl;
        }

        const string &Get_id() const
        {
            return id;
        }

        virtual void Show() const
        {
            cout << "ID: " << id << "\n";
        }

};

class Car: public Vehicle
{
    size_t door_count;

    public:
        Car(const string &id, size_t door) :
            Vehicle {id},
            door_count {door}
        {

        }

        ~Car()
        {
            cout << "Bye C" << endl;
        }

        size_t Get_door_count() const
        {
            return door_count;
        }

        void Show() const override
        {
            //cout << "ID: " << Get_id() << "\n";
            Vehicle::Show();
            cout << "Doors: " << door_count << "\n";
        }
};

/*
void show(const Vehicle &x)
{
    cout << "ID: " << x.Get_id() << "\n";
}

void show(const Car &x)
{
    cout << "ID: " << x.Get_id() << "\n";
    cout << "Doors: " << x.Get_door_count() << "\n";
}
*/


int main()
{
    /*Vehicle c1 {"316HAB"};
    c1.Show();
    Car c2 {"4116ABC", 4};
    c2.Show();*/

    Vehicle* c3 = new Vehicle("123ABC");
    c3->Show();

    Car* c4 = new Car("678DEF", 3);
    c4->Show();

    Vehicle* c5 = new Car("001XYZ", 6);
    c5->Show();

    delete c3;
    delete c4;
    delete c5;

    return 0;
}

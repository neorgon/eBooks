#include <thread>
#include <iostream>
#include <string>
#include <chrono>
#include <mutex>

using namespace std;

void f(const string &s, mutex &m)
{
    for (int i = 0; i < 60; i++)
    {
        //m.lock();
        lock_guard<mutex> z {m};
        //printf("%s %d\n", s.c_str(), i); //Thread safe
        cout << s << " " << i << "\n"; //No Thread safe
        this_thread::sleep_for(1ms);
        //m.unlock();
    }
}

int main()
{
    mutex m;
    thread t1 {f, string("Hello"), ref(m)};
    thread t2 {f, string("Last"), ref(m)};
    thread t3 {f, string("Week"), ref(m)};
    t1.join();
    t2.join();
    t3.join();

    return 0;
}

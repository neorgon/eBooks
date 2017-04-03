#include <cstdio>

#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

class ITask
{
public:
    ~ITask() { }
    virtual void operator()() = 0;
};

template<typename T>
class Task : public ITask
{
    mutex mtx;
    T task;
public:
    Task(T task)
    {
        this->task = task;
        mtx.lock();
    }

    void operator()() override
    {
        task();
        mtx.unlock();
    }

    void Wait()
    {
        mtx.lock();
        mtx.unlock();
    }
};

template<typename T>
class Task<T*> : public ITask
{
    mutex mtx;
    T* task;
public:
    Task(T* task)
    {
        this->task = task;
        mtx.lock();
    }

    void operator()() override
    {
        (*task)();
        mtx.unlock();
    }

    void Wait()
    {
        mtx.lock();
        mtx.unlock();
    }
};

class Worker
{
    thread t;
    bool pendingWork;
    ITask *task;
    bool alive;
public:
    Worker()
    {
        alive = true;
        pendingWork = false;
        t = thread
            (
                [this] ()
                {
                    while (alive)
                    {
                        if (pendingWork)
                        {
                            (*task)();
                            pendingWork = false;
                        }
                        this_thread::sleep_for(chrono::milliseconds(100));
                    }
                }
            );
    }

    bool IsWorking()
    {
        return pendingWork;
    }

    void SetWork(ITask *task)
    {
        this->task = task;
        pendingWork = true;
    }

    ~Worker()
    {
        alive = false;
        t.join();
    }
};

class ThreadPool
{
    vector<Worker *> workers;
    queue<ITask *> tasks;
    thread master;
    bool alive;
public:
    ThreadPool(int numberOfThreads)
    {
        alive = true;
        for (int i = 0; i < numberOfThreads; i++)
        {
            workers.push_back(new Worker());
        }
        master = thread
        (
            [this] ()
            {
                while (alive)
                {
                    for (auto w : workers)
                    {
                        if (!w->IsWorking() && !tasks.empty())
                        {
                            w->SetWork(tasks.front());
                            tasks.pop();
                        }
                    }
                    this_thread::sleep_for(chrono::milliseconds(100));
                }
            }
        );
    }

    void Enqueue(ITask *task)
    {
        tasks.push(task);
    }

    ~ThreadPool()
    {
        alive = false;
        master.join();
        for (auto w : workers)
        {
            delete w;
        }
    }
};

#define ENABLE_TEST_1

#define ENABLE_TEST_2

bool test1()
{
#ifdef ENABLE_TEST_1
    int numberOfThreads = 1;

    ThreadPool threadPool(numberOfThreads);

    string s1 = "Hola mundo!";
    string s2 = "Hola mundo!";

    thread::id threadId = this_thread::get_id();
    thread::id uniqueThread1;
    thread::id uniqueThread2;

    Task<function<void ()>> t1(
        [&] ()
        {
            uniqueThread1 = this_thread::get_id();
            reverse(s1.begin(), s1.end());
        }
    );

    Task<function<void ()>> t2(
        [&] ()
        {
            uniqueThread2 = this_thread::get_id();
            reverse(s2.begin(), s2.end());
        }
    );

    threadPool.Enqueue(&t1);
    threadPool.Enqueue(&t2);

    t2.Wait();
    bool assertion1 = (s2.compare("!odnum aloH") == 0);

    t1.Wait();
    bool assertion2 = (s1.compare("!odnum aloH") == 0);

    bool assertion3 = ((uniqueThread1 == uniqueThread2) && (threadId != uniqueThread1));

    return (assertion1 && assertion2 && assertion3);
#else
    return false;
#endif
}

bool test2()
{
#ifdef ENABLE_TEST_2
    class InvertString
    {
    private:
        thread::id threadId;
        string s;
    public:
        InvertString(string s)
        {
            this->s = s;
        }

        thread::id GetThreadId()
        {
            return threadId;
        }

        string GetString()
        {
            return s;
        }

        void operator()()
        {
            threadId = this_thread::get_id();
            reverse(s.begin(), s.end());
        }
    };

    thread::id threadId = this_thread::get_id();

    int numberOfThreads = 2;

    ThreadPool threadPool(numberOfThreads);

    InvertString invertString("Hola mundo!");

    Task<InvertString*> t(&invertString);

    threadPool.Enqueue(&t);

    t.Wait();

    bool assertion1 = (invertString.GetString().compare("!odnum aloH") == 0);

    bool assertion2 = (threadId != invertString.GetThreadId());

    return (assertion1 && assertion2);
#else
    return false;
#endif
}

class TestSuite
{
    unsigned int passed;
    unsigned int executed;
    unsigned int id;

public:
    TestSuite() : passed(0), executed(0), id(0)
    {
    }

    void run(bool (*test)(), int points)
    {
        bool r = test();
        passed += ((unsigned int) r) * points;
        executed += points;
        ++id;
        const char *result = r ? "PASSED" : "FAILED";
        printf("Test #%d for %d points => %s\n", id, points, result);
    }

    unsigned int getPassed() const
    {
        return passed;
    }

    unsigned int getExecuted() const
    {
        return executed;
    }
};

int main()
{
    TestSuite testSuite;

    testSuite.run(test1, 75);
    testSuite.run(test2, 25);

    printf("FINAL SCORE: %d / %d\n", testSuite.getPassed(), testSuite.getExecuted());

    return 0;
}

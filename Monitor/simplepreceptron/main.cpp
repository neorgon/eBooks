#include <iostream>
#include <random>
#include <ctime>
#include <chrono>

using namespace std;

char *led[] = {"off", "on"};

float inputs[] = {0 ,0};
float weights[] = {0 ,0};
int elements = 5;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);
uniform_int_distribution <> input(1, 30);
uniform_int_distribution <> weight(-1, 1);

void createIW(float inputs[], float weights[], int manyInputs = 2)
{
    for(int i = 0; i < manyInputs; ++i)
    {
        inputs[i] = input(gen);
        weights[i] = weight(gen);
    }
}

int activate(float sum)
{
    if(sum > 0) return 1;
    return 0;
}

int main()
{
    float sum = 0;
    createIW(inputs, weights);
    for(int i = 0; i < elements; ++i)
    {
        sum += inputs[i] * weights[i];
    }
    cout << "Led status: " << led[activate(sum)] << endl;
    return 0;
}

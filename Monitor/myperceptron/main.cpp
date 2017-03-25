#include <iostream>
#include <random>
#include <chrono>

using namespace std;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine gen(seed);
uniform_int_distribution <> width(-80 / 2, 80 / 2);
uniform_int_distribution <> height(-20 / 2, 20 / 2);
uniform_int_distribution <> weight(-1, 1);

class Perceptron
{
    vector <double> weights;
    double learning = 0.001;

    public:
        Perceptron(int n)
        {
            for (int i = 0; i < n; ++i)
            {
                weights.push_back(weight(gen));
            }
        }

        int FeedForward(vector <double> inputs)
        {
            double sum = 0;
            int i = 0;

            for (auto w : weights)
            {
                sum += inputs.at(i) * w;
                ++i;
            }

            return sum;
        }

        int Activate(int sum)
        {
            return sum > 0 ? 1 : -1;
        }

        void Train(vector <double> inputs, int desired)
        {
            int guess = FeedForward(inputs);
            double error = desired - guess;
            int i = 0;

            for (auto w : weights)
            {
                w += error * inputs.at(i) * learning;
                ++i;
            }
        }
};

class Trainer
{
    public:
        vector <double> inputs;
        int answer;

        Trainer(double x, double y, int a)
        {
            inputs.push_back(x);
            inputs.push_back(y);
            inputs.push_back(1);
            answer = a;
        }
};

double f(double x)
{
    return 2 * x + 1;
}

int main()
{
    Perceptron tron(3);
    vector <Trainer> trainer;
    int trainerSize = 20;
    int answer;

    for (int i = 0; i < trainerSize; ++i)
    {
        double x = width(gen);
        double y = height(gen);

        answer = y < f(x) ? -1 : 1;

        trainer.push_back(Trainer(x, y, answer));
    }

    for (auto t : trainer)
        tron.Train(t.inputs, t.answer);

    for (auto t: trainer)
    {
        int guess = tron.FeedForward(t.inputs);

        cout << (guess > 0 ? "fill" : "no fill")
            << " -> x: " << t.inputs.at(0) << ","
            << " -> y: " << t.inputs.at(1) << "\n";
    }

    return 0;
}

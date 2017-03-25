#include <iostream>

using namespace std;

int sum(int a , int b)
{
	return a + b;
}

double sum(double a, double b)
{
	return a + b;
}

int sum(int a, int b, int c)
{
	return a + b + c;
}

void is_even(int n)
{

}

size_t get_digit_count(size_t n)
{
	size_t count = 0;
	while(n / 10) count++;
	
	return count;
}

int main()
{
	/*auto a = sum(2, 8);
	auto d = sum((double)2, 3.1);*/
	auto x = get_digit_count(12345);
	
	cout << x << endl;
	
	return 0;
}

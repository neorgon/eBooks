#include <iostream>
#include <string>

using namespace std;

string get_month(int month)
{
    string months[] = {
        "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noveimbre", "Diciembre"
    };

    return months[month];
}

bool leap_year(size_t y)
{
	if(y % 400 == 0)
		return true;
	if(y % 100 == 0)
		return false;
	if(y % 4 == 0)
		return true;
}

bool valid_day(size_t d, size_t m, size_t y)
{
	if(m == 2)
	{
		return leap_year(y) ? d <= 29 : d <= 28;
	}
	else if(m == 4 || m == 6 || m == 9 || m == 11) return d <= 30;
		else return d <= 31;

	return false;
}

bool is_valid_date(size_t d, size_t m, size_t y)
{
	if(m >= 1 && m <= 12)
		return valid_day(d, m, y);
	else
		return false;
}

string fromDate(size_t d, size_t m, size_t y)
{
    if(valid_day(d, m, y))
        return to_string(d) + " de " + get_month(m - 1) + " de " + to_string(y);
    else
        return "Date is not valid.";
}

int main()
{
    cout << "Hello world!" << endl;
    cout << "Today is : " << fromDate(10, 3, 2017) << endl;
    return 0;
}

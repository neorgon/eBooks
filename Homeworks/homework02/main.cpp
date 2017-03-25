#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

vector <string> first_number = {
    "cero", "un", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve", "diez",
    "once", "doce", "trece", "catorce", "quince"
};

vector <string> tens = {
    "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"
};

string to_literal(const unsigned int &value)
{
    if(value <= 15)
        return first_number.at(value);
    if(value < 20)
        return "dieci" + first_number.at(value - 10);
    if(value < 100)
    {
        unsigned int remain = value - (int)((value / 10) * 10);
        if((int)(value / 10) == 2)
            return remain == 0 ? tens.at(value / 10 - 2) : "veinti" + to_literal(remain);
        else
            return tens.at(value / 10 - 2) + (remain != 0 ? " y " + to_literal(remain) : "");
    }
    if(value < 1000)
    {
        unsigned int remain = value - (int)((value / 100) * 100);
        if((int)(value / 100) == 1)
            return remain == 0 ? "cien" : "ciento " + to_literal(remain);
        if((int)(value / 100) == 5)
            return "quinientos" + (remain != 0 ? " " + to_literal(remain) : "");
        if((int)(value / 100) == 7)
            return "setecientos" + (remain != 0 ? " " + to_literal(remain) : "");
        if((int)(value / 100) == 9)
            return "novecientos" + (remain != 0 ? " " + to_literal(remain) : "");
        return first_number.at(value / 100) + "cientos" + (remain != 0 ? " " + to_literal(remain) : "");
    }
    if(value < 1000000)
    {
        unsigned int remain = value - (int)((value / 1000) * 1000);
        if((int)(value / 1000) <= 15)
        {
            if((int)(value / 1000) == 1)
                return "mil" + (remain != 0 ? " " + to_literal(remain) : "");
            else
                return first_number.at(value / 1000) + " mil" + (remain != 0 ? " " + to_literal(remain) : "");
        }
        if((int)(value / 1000) < 20)
            return "dieci" + first_number.at((value / 1000) - 10) + "mil" + (remain != 0 ? " " + to_literal(remain) : "");
        return to_literal(value / 1000) + " mil" + (remain != 0 ? " " + to_literal(remain) : "");
    }

    return "none";
}

void literal(const double value, const string unit = "Bs.")
{
    unsigned int integer = floor(value);
    string s_number = to_string(value);
    auto p = s_number.find('.');
    string decimal = p ? s_number.substr(p + 1, 2) : "00";

    cout << integer << "." << decimal << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << "Son: " << to_literal(integer) << " " << decimal << " / 100 " << unit << endl;

}

int main()
{
    literal(61000.98);

    return 0;
}

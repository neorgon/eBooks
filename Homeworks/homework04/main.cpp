#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

vector <string> first_number = {
    "cero", "un", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve", "diez",
    "once", "doce", "trece", "catorce", "quince"
};

vector <string> tens = {
    "veinte", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa"
};

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
    return false;
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

string date(size_t d, size_t m, size_t y)
{
    if(valid_day(d, m, y))
        return to_string(d) + " de " + get_month(m - 1) + " de " + to_string(y);
    else
        return "Date is not valid.";
}

string double_to_string(double const number)
{
    unsigned int integer = floor(number);
    string s_number = to_string(number);
    auto p = s_number.find('.');
    string decimal = p ? "." + s_number.substr(p + 1, 2) : ".00";

    return to_string(integer) + decimal;
}

class Item
{
    string detail;
    unsigned int amount;
    double price;

    public:
        Item(
            string d,
            unsigned int a,
            double p
             ) : detail{d}, amount{a}, price{p} {}
        const string &Get_detail() const;
        int Get_amount() const;
        double Get_price() const;
        double Get_total_price() const;
};

const string &Item::Get_detail() const
{
    return detail;
}

int Item::Get_amount() const
{
    return amount;
}

double Item::Get_price() const
{
    return price;
}

double Item::Get_total_price() const
{
    return amount * price;
}

class Bill
{
    unsigned int id;
    string date;
    string name;
    string nit;
    vector <Item> items;
    double total;

    string To_literal(int value) const;
    string Total_to_literal(double total) const;

    public:
        Bill(
            unsigned int i,
            string d,
            string n,
            string t) : id{i}, date{d}, name{n}, nit{t} {};
        void Add_item(Item item);
        unsigned int Get_id() const;
        const string &Get_date() const;
        string To_string() const;
        void Set_total();
};

string Bill::To_literal(int value) const
{
    if(value <= 15)
        return first_number.at(value);
    if(value < 20)
        return "dieci" + first_number.at(value - 10);
    if(value < 100)
    {
        unsigned int remain = value - (int)((value / 10) * 10);
        if((int)(value / 10) == 2)
            return remain == 0 ? tens.at(value / 10 - 2) : "veinti" + To_literal(remain);
        else
            return tens.at(value / 10 - 2) + (remain != 0 ? " y " + To_literal(remain) : "");
    }
    if(value < 1000)
    {
        unsigned int remain = value - (int)((value / 100) * 100);
        if((int)(value / 100) == 1)
            return remain == 0 ? "cien" : "ciento " + To_literal(remain);
        if((int)(value / 100) == 5)
            return "quinientos" + (remain != 0 ? " " + To_literal(remain) : "");
        if((int)(value / 100) == 7)
            return "setecientos" + (remain != 0 ? " " + To_literal(remain) : "");
        if((int)(value / 100) == 9)
            return "novecientos" + (remain != 0 ? " " + To_literal(remain) : "");
        return first_number.at(value / 100) + "cientos" + (remain != 0 ? " " + To_literal(remain) : "");
    }
    if(value < 1000000)
    {
        unsigned int remain = value - (int)((value / 1000) * 1000);
        if((int)(value / 1000) <= 15)
        {
            if((int)(value / 1000) == 1)
                return "mil" + (remain != 0 ? " " + To_literal(remain) : "");
            else
                return first_number.at(value / 1000) + " mil" + (remain != 0 ? " " + To_literal(remain) : "");
        }
        if((int)(value / 1000) < 20)
            return "dieci" + first_number.at((value / 1000) - 10) + "mil" + (remain != 0 ? " " + To_literal(remain) : "");
        return To_literal(value / 1000) + " mil" + (remain != 0 ? " " + To_literal(remain) : "");
    }

    return "none";
}

string Bill::Total_to_literal(double total) const
{
    unsigned int integer = floor(total);
    string s_number = to_string(total);
    auto p = s_number.find('.');
    string decimal = p ? s_number.substr(p + 1, 2) : "00";

    return to_string(integer) + "." + decimal + "\n" +
        "--------------------------------------------------------------------------\n" +
        "Son: " + To_literal(integer) + " " + decimal + " / 100 Bolivianos\n";
}

string Bill::To_string() const
{
    int n = 0;
    string lItems = "";

    for (auto i : items)
    {
        ++n;
        lItems += to_string(n)
            + ".- " + i.Get_detail() + " " + to_string(i.Get_amount()) + " p/u " + double_to_string(i.Get_price())
            + " total " + double_to_string(i.Get_total_price()) + "\n";
    }
    return "Factura numero: " + to_string(id) + "\n" +
        "Fecha: " + date + "\n" +
        "Senores: " + name + " NIT: " + nit + "\n" +
        "================================================\n" +
        lItems +
        "================================================\n" +
        "TOTAL: " + Total_to_literal(total);
}

void Bill::Add_item(Item item)
{
    items.push_back(item);
}

unsigned int Bill::Get_id() const
{
    return id;
}

const string &Bill::Get_date() const
{
    return date;
}

void Bill::Set_total()
{
    total = 0;
    for(auto i : items)
    {
        total += i.Get_total_price();
    }
}

class Bill_Manager
{
    vector <Bill> bills;

    public:
        void add(Bill bill);
        const Bill Get_bill_by_id(size_t id) const;
        vector <Bill> Get_bill_by_date(const string &date) const;
};

void Bill_Manager::add(Bill bill)
{
    bills.push_back(bill);
}

const Bill Bill_Manager::Get_bill_by_id(size_t id) const
{
    for (auto b : bills)
    {
        if (b.Get_id() == id)
            return b;
    }
    Bill noBill(0, date(1, 1, 2017), "0", "0");
    noBill.Set_total();
    return noBill;
}

vector <Bill> Bill_Manager::Get_bill_by_date(const string &s_date) const
{
    vector <Bill> lBills;

    for (auto b : bills)
    {
        if(b.Get_date().compare(s_date) == 0)
            lBills.push_back(b);
    }

    if (lBills.size() == 0)
    {
        Bill bill(0, date(1, 1, 2017), "0", "0");
        bill.Set_total();
        lBills.push_back(bill);
    }

    return lBills;
}

Bill create_bill_1()
{
    Item item1("Detail item one", 2, 50.25);
    Item item2("Detail item two", 1, 150);
    Item item3("Detail item three", 4, 25.75);
    Item item4("Detail item four", 3, 100);
    Bill bill(1, date(12, 1, 2017), "Anzoleaga", "4383197");
    bill.Add_item(item1);
    bill.Add_item(item2);
    bill.Add_item(item3);
    bill.Add_item(item4);
    bill.Set_total();

    return bill;
}

Bill create_bill_2()
{
    Item item1("Detail item one", 2, 50.25);
    Item item2("Detail item two", 1, 150);
    Item item3("Detail item three", 4, 25.75);
    Item item4("Detail item four", 3, 100);
    Bill bill(2, date(14, 1, 2017), "Anzoleaga", "4383197");
    bill.Add_item(item1);
    bill.Add_item(item2);
    bill.Add_item(item3);
    bill.Add_item(item4);
    bill.Set_total();

    return bill;
}

Bill create_bill_3()
{
    Item item1("Detail item one", 2, 50.25);
    Item item2("Detail item two", 1, 150);
    Item item3("Detail item three", 4, 255.75);
    Item item4("Detail item four", 3, 10.30);
    Bill bill(3, date(10, 3, 2017), "Anzoleaga", "4383197");
    bill.Add_item(item1);
    bill.Add_item(item2);
    bill.Add_item(item3);
    bill.Add_item(item4);
    bill.Set_total();

    return bill;
}

Bill create_bill_4()
{
    Item item1("Detail item one", 2, 500.25);
    Item item2("Detail item two", 1, 15);
    Item item3("Detail item three", 4, 25.75);
    Item item4("Detail item four", 3, 100.50);
    Bill bill(4, date(10, 3, 2017), "Anzoleaga", "4383197");
    bill.Add_item(item1);
    bill.Add_item(item2);
    bill.Add_item(item3);
    bill.Add_item(item4);
    bill.Set_total();

    return bill;
}

int main()
{
    Bill_Manager fm;
    fm.add(create_bill_1()); //create test facturas here and below
    fm.add(create_bill_2());
    fm.add(create_bill_3());
    fm.add(create_bill_4());

    auto& f = fm.Get_bill_by_id(1); //if not found, return a generic facture (with all values empty or 0).
    cout << f.To_string() << "\n";

    auto fs = fm.Get_bill_by_date(date(10, 3, 2017));
    for (auto f : fs)
    {
        cout << f.To_string() << "\n";
    }

    return 0;
}

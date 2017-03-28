#include <iostream>

using namespace std;

class MyString
{
    char* ss;
    size_t n;

    MyString(char* s, size_t n) : ss{s}, n{n} { /*cout << "String created\n";*/ }
    size_t Get_string_lenght(const char* s);
    void Copy_string(char* result, const char* source, size_t len) const;

    public:
        MyString(const char* s = "")
        {
            n = Get_string_lenght(s);
            ss = new char[n + 1];
            Copy_string(ss, s, n);
            /*cout << "String created\n";*/
        }

        ~MyString()
        {
            /*cout << "Bye string \n";*/
            delete [] ss;
        }

        MyString(const MyString &src) // Copy constructor
        {
            n = src.n;
            ss = new char[n + 1];
            Copy_string(ss, src.ss, n);
            /*cout << "String copied \n";*/
        }

        void Show() const
        {
            cout << ss << "\n";
        }

        MyString operator+(const MyString &s) const;
        MyString &operator+=(const MyString &x);
        bool operator==(const MyString &c) const;
        bool operator!=(const MyString &c) const;
        bool Start_with(const MyString &e) const;
        MyString &Trim();
        MyString Substring(size_t from);
        MyString Substring(size_t from, size_t len);

};

size_t MyString::Get_string_lenght(const char *s)
{
    size_t c = 0;
    for (; s[c] != '\0'; ++c)
    {

    }

    return c;
}

void MyString::Copy_string(char *p, const char *q, size_t len) const
{
    for (size_t i = 0; i < len; ++i)
    {
        p[i] = q[i];
    }
    p[len] = '\0';
}

MyString MyString::operator+(const MyString &s) const
{
    auto len = n + s.n;
    auto ns = new char[len + 1];

    Copy_string(ns, ss, n);
    Copy_string(ns + n, s.ss, s.n);

    /*MyString x {ns};
    delete []ns;

    return x;*/

    return MyString {ns, n};
}

MyString &MyString::operator+=(const MyString &x)
{
    auto len = n + x.n;
    auto ns = new char[len + 1];

    Copy_string(ns, ss, n);
    Copy_string(ns + n, x.ss, x.n);

    delete [] ss;

    ss = ns;
    n = len;

    return *this;
}

bool MyString::operator==(const MyString &c) const
{
    if (this == &c) return true;

    if (n != c.n) return false;

    for (auto i=0U; i<n; i++)
        if (ss[i] != c.ss[i]) return false;

    return true;
}

bool MyString::operator!=(const MyString &c) const
{
    return !operator==(c);
}

bool MyString::Start_with(const MyString &e) const
{
    if (e.n > n) return false;
    if (this == &e) return true;

    for (auto i=0U; i<e.n; i++)
        if (e.ss[i] != ss[i]) return false;

    return true;
}

MyString &MyString::Trim()
{
    if(n == 0) return *this;
    size_t left = 0, right = n - 1;

    while(ss[left] == ' ' && left < right) left++;
    if(left == right) return *this;
    while(ss[right] == ' ' && right > left) right--;

    auto len = right - left;
    auto ns = new char[len + 1];

    Copy_string(ns, ss + left, len);
    delete [] ss;
    ss = ns;
    n = len;

    return *this;
}

MyString MyString::Substring(size_t from)
{
    size_t len = n - from;
    auto ns = new char[len + 1];

    Copy_string(ns, ss + from, len);

    return  MyString {ns, len};
}

MyString MyString::Substring(size_t from, size_t len)
{
    auto ns = new char[len + 1];

    Copy_string(ns, ss + from, len);

    return MyString {ns, len};
}

int main()
{
    MyString s;
    s.Show();

    MyString p = "Happy";
    MyString q = " Thuesday";

    cout << "****\n";

    (p+q).Show();

    cout << "****\n";

    MyString r = "Depeche";
    r += " Mode dfghjjhdffghjmdefjtnmklcdoiveuivghnoacmovngubvsvmoecvuvecnaocneuivueivbuivceoicnaerovuivefcnwoiceoivuivbeivbucbaiuvcbeivbreivubaevuibaeoviadovne;ovnoivoevn";
    r.Show();

    MyString a = "hello";
    MyString b = "hola";
    MyString &c = a;
    MyString d = "holo";
    MyString e = "hello";

    cout << (a == b) << endl;
    cout << (a == c) << endl;
    cout << (b == d) << endl;
    cout << (a == e) << endl;
    cout << (a != b) << endl;

    MyString x = "UbuntuLinux";

    cout << x.Start_with("Ubuntu") << endl;
    cout << x.Start_with("Windows") << endl;
    cout << x.Start_with("") << endl;

    MyString t = "    hello world!    ";
    //MyString t = "  ";

    t.Trim().Show();

    MyString z = "Zanahoria";
    z.Substring(4).Show(); //horia
    z.Substring(1, 3).Show(); //ana
    z.Substring(0, 9).Show(); //Zanahoria

    return 0;
}

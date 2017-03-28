#include <iostream>

using namespace std;

constexpr size_t MAX_SSO = 16;

class MyString
{
    char *ss;
    char sso[MAX_SSO];
    size_t n;

    MyString(const char* s, size_t n)
    {
        if (n < MAX_SSO)
        {
            ss = nullptr;
            Copy_string(sso, s, n);
        }
        else
        {
            ss = new char[n + 1];
            Copy_string(ss, s, n);
        }
        this->n = n;
    }
    size_t Get_string_lenght(const char* s);
    void Copy_string(char* target, const char* source, size_t len) const;
    void Copy_string(char* target, size_t n, const char* source, size_t len) const;
    void Copy_sub(char* target, const char* source, size_t from, size_t len) const;

    public:
        MyString(const char* s);
        ~MyString();
        MyString(const MyString &src);

        void Show() const;
        MyString operator+(const MyString &s) const;
        MyString &operator+=(const MyString &x);
        bool operator==(const MyString &c) const;
        bool operator!=(const MyString &c) const;
        bool Start_with(const MyString &e) const;
        MyString &Trim();
        MyString Substring(size_t from);
        MyString Substring(size_t from, size_t len);
};

MyString::MyString(const char* s = "")
{
    n = Get_string_lenght(s);
    if (n < MAX_SSO)
    {
        ss = nullptr;
        Copy_string(sso, s, n);
    }
    else
    {
        ss = new char[n + 1];
        Copy_string(ss, s, n);
    }
}

MyString::~MyString()
{
    if (n < MAX_SSO)
        delete [] ss;
}

MyString::MyString(const MyString &src)
{
    n = src.n;
    if(n < MAX_SSO)
    {
        ss = nullptr;
        Copy_string(sso, src.sso, n);
    }
    else
    {
        ss = new char[n + 1];
        Copy_string(ss, src.ss, n);
    }
}

size_t MyString::Get_string_lenght(const char* s)
{
    size_t c = 0;

    for (; s[c] != '\0'; ++c)
    {

    }

    return c;
}

void MyString::Copy_string(char* target, const char* source, size_t len) const
{
    for (size_t i = 0; i < len; ++i)
    {
        target[i] = source[i];
    }
    target[len] = '\0';
}

void MyString::Copy_string(char* target, size_t n, const char* source, size_t len) const
{
    size_t i;

    for (i = 0; i < len; ++i)
    {
        target[n + i] = source[i];
    }
    target[n + i] = '\0';
}

void MyString::Copy_sub(char* target, const char* source, size_t from, size_t len) const
{
    for (size_t i = 0; i < len; ++i)
    {
        target[i] = source[from + i];
    }
    target[len] = '\0';
}

void MyString::Show() const
{
    if (n < MAX_SSO)
        cout << sso << "\n";
    else
        cout << ss << "\n";
}

MyString MyString::operator+(const MyString &s) const
{
    auto len = n + s.n;

    if (len < MAX_SSO)
    {
        Copy_string((char*)sso, n, s.sso, s.n);

        return MyString {sso, len};
    }
    else
    {
        auto ns = new char[len + 1];

        Copy_string(ns, (n < MAX_SSO ? sso : ss), n);
        Copy_string(ns + n, (s.n < MAX_SSO ? s.sso : s.ss), s.n);

        return MyString {ns, len};
    }
}

MyString &MyString::operator+=(const MyString &x)
{
    auto len = n + x.n;
    char* ns = nullptr;

    if (len < MAX_SSO)
    {
        Copy_string(sso, n, x.sso, x.n);
    }
    else
    {
        ns = new char[len + 1];

        Copy_string(ns, (n < MAX_SSO ? sso : ss), n);
        Copy_string(ns + n, (x.n < MAX_SSO ? x.sso : x.ss), x.n);

        delete [] ss;
    }

    ss = ns;
    n = len;

    return *this;
}

bool MyString::operator==(const MyString &c) const
{
    if (this == &c) return true;

    if (n != c.n) return false;

    if (n < MAX_SSO)
    {
        for (auto i=0U; i<n; i++)
            if (sso[i] != c.sso[i]) return false;
    }
    else
    {
        for (auto i=0U; i<n; i++)
            if (ss[i] != c.ss[i]) return false;
    }

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

    if (n < MAX_SSO && e.n < MAX_SSO)
    {
        for (auto i=0U; i<e.n; i++)
            if (e.sso[i] != sso[i]) return false;
    }
    else
        if (n < MAX_SSO)
        {
            for (auto i=0U; i<e.n; i++)
                if (e.ss[i] != sso[i]) return false;
        }
        else
        {
            for (auto i=0U; i<e.n; i++)
                if (e.ss[i] != ss[i]) return false;
        }

    return true;
}

MyString &MyString::Trim()
{
    if (n == 0) return *this;
    size_t left = 0, right = n - 1, len = n;
    char* ns;
    char nso[MAX_SSO];

    if (n < MAX_SSO)
    {
        ns = nullptr;

        while(sso[left] == ' ' && left < right) left++;
        if(left == right) return *this;
        while(sso[right] == ' ' && right > left) right--;

        len = right - left;
        Copy_sub(nso, sso, left, len + 1);
        Copy_string(sso, nso, len);
    }
    else
    {
        while(ss[left] == ' ' && left < right) left++;
        if(left == right) return *this;
        while(ss[right] == ' ' && right > left) right--;

        len = right - left;
        if(len < MAX_SSO)
        {
            ns = nullptr;

            Copy_sub(sso, ss, left, len + 1);
        }
        else
        {
            ns = new char[len + 1];

            Copy_string(ns, ss + left, len);
        }
        delete [] ss;
    }

    ss = ns;
    n = len;

    return *this;
}

MyString MyString::Substring(size_t from)
{
    size_t len = n - from;
    if(len < MAX_SSO)
    {
        char nso[MAX_SSO];

        Copy_sub(nso, (n < MAX_SSO ? sso : ss), from, len + 1);

        return MyString {nso, len};
    }
    else
    {
        auto ns = new char[len + 1];

        Copy_string(ns, ss + from, len);

        return MyString {ns, len};
    }
}

MyString MyString::Substring(size_t from, size_t len)
{
    if(len < MAX_SSO)
    {
        char nso[MAX_SSO];

        Copy_sub(nso, (n < MAX_SSO ? sso : ss), from, len + 1);

        return MyString {nso, len};
    }
    else
    {
        auto ns = new char[len + 1];

        Copy_string(ns, ss + from, len);

        return MyString {ns, len};
    }
}

int main()
{

    MyString s = "hola";
    s.Show();

    MyString cp = s;
    cp.Show();

    s = cp;
    s.Show();

    MyString em;
    em.Show();

    MyString p = "Happy";
    MyString q = " Thuesday";

    cout << "****\n";

    (p + q).Show();

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

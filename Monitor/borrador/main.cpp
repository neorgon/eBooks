#include <iostream>
#include <string>

using namespace std;

struct foo
{
    virtual int get() const { return 0; }
};

struct bar : foo
{
    string get() const { return "this certainly isn't an int"; }
};

int main()
{
    bar b;
    foo* f = &b;

    int result = f->get(); // int, right? ...right?
}

/*
enum class PType { Integer, Real };

template <class T, PType type>
T foo(string value)
{
    if (type == PType::Integer)
        return stoi(value);
    if (type == PType::Real)
        return stod(value);
}

int main()
{
    cout << foo<int, PType::Integer>("5") << endl;
    cout << foo<double, PType::Real>("7.8") << endl;

    return 0;
}
*/
/*
#include <string>
#include <map>
#include <iostream>

struct T
{
   T(int x, int y) : x_(x), y_(y)
   {}

   int x_, y_;
};

int main()
{
   typedef std::map<std::string, T> map_type;
   map_type m;

   m.insert(std::make_pair("0:0", T(0,0)));
   m.insert(std::make_pair("0:1", T(0,1)));
   m.insert(std::make_pair("1:1", T(2,2)));

   // find the desired item (returns an iterator to the item
   // or end() if the item doesn't exist.
   map_type::const_iterator t_0_1 = m.find("1:1");

   if(m.end() != t_0_1)
   {
      // access via the iterator (a std::pair) with
      // key stored in first, and your contained type
      // stored in second.
      std::cout << t_0_1->second.x_ << ':' << t_0_1->second.y_ << '\n';
   }

   std::cout << m.find("1:1")->second.x_ << ':' << m.find("1:1")->second.y_ << '\n';

   return 0;
}
*/
/*
#include <iostream>
#include <map>
#include <vector>

using namespace std;
int main ()
{
  std::map<char, vector<int>> mymap;
  std::map<char, vector<int>>::iterator it;

  mymap['a'].push_back(50);
  mymap['b'].push_back(100);
  mymap['c'].push_back(150);
  mymap['d'].push_back(200);
  mymap['a'].push_back(250);
  mymap['b'].push_back(300);

  it = mymap.find('b');
  if (it != mymap.end())
    mymap.erase (it);

  // print content:
  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';
  std::cout << "d => " << mymap.find('d')->second << '\n';

  return 0;
}
*/

/*
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class A
{
    private:
       string b;
       string c;
    public:
    A(string i) : b(i) {}
    A(string n, string l) { b = n ;c = l; }
    string Getb(){ return b; }
    string Getc(){ return c; }
    bool operator==(const A & obj2) const
    {
       return (this->b.compare(obj2.b) == 0);
    }
};

int main()
{
   vector<A> a1;
   a1.push_back(A("AA","aa"));
   a1.push_back(A("BB","bb"));
   a1.push_back(A("CC","cc"));
   a1.push_back(A("DD","dd"));

   auto it = find(a1.begin(), a1.end(), A("DD", "dd"));
   if (it != a1.end()) {
      auto idx = distance(a1.begin(), it);
      cout << "b= " << it->Getb() << " c= " << it->Getc() << endl;
      cout << "Index= " << idx << endl;
    } else
      cout << "CC is not found" << endl;

    return 0;
}
*/

/*
// Warning: I didn't try to compile this...
#include <cassert>
#include <string>
#include <iostream>
#include <windows.h>

using namespace std;

void displayFrame( int w, int h ) {
    assert( h >= 2 );   // Height has to be at least 2 for a top and bottom side
    assert( w >= 2 );  // Width has to be at least 2 for a left and right side

    // Draw row of 'w' asterisks for top side
    cout << string( w, '*' ) << endl;

    // Draw sides: asterisk, width-2 spaces, asterisk
    for( int j = 0; j < h - 2; ++j )
        cout << '*' << string( w - 2, ' ' ) << '*' << endl;

    // Draw row of 'w' asterisks for bottom side
    cout << string( w, '*' ) << endl;
}

int main()
{
    short int x = 5;  short int y = 6;
COORD pos = {x, y};
HANDLE hConsole_c = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
SetConsoleActiveScreenBuffer(hConsole_c);
char *str = "Some Text\r\n";
DWORD len = strlen(str);
DWORD dwBytesWritten = 0;
WriteConsoleOutputCharacter(hConsole_c, str, len, pos, &dwBytesWritten);
CloseHandle(hConsole_c);

    return 0;
}
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector <string> my_list {
    "lorem", "ipsum", "dolor", "sit", "amet", "consectetur", "adipiscing", "elit", "duis", "aliquam", "enim", "in", "semper",
    "lobortis", "donec", "commodo", "justo", "vitae", "porttitor", "tempor", "sed", "non", "libero", "fermentum", "maximus",
    "enim", "et", "tincidunt", "elit", "duis", "accumsan", "libero", "vel", "scelerisque", "bibendum", "nunc", "sed", "massa",
    "eget", "dui", "volutpat", "commodo", "eget", "at", "leo", "in", "non", "turpis", "ut", "elit", "ultrices", "maximus",
    "vel", "in", "dui", "ut", "ac", "tellus", "ornare", "mi", "malesuada", "pretium"
};

int main()
{
    unsigned int uniques = my_list.size();
    unsigned int check = 0;
    string element;

    cout << "Elements: " << uniques << endl;

    while(check < uniques)
    {
        element = my_list.at(check);
        ++check;

        for(unsigned int i = check; i <= uniques; ++i)
        {
            if(i < my_list.size() && element == my_list.at(i))
                my_list.erase(my_list.begin() + i);
        }
        uniques = my_list.size();
    }

    for(auto e : my_list)
        cout << e << endl;

    cout << "\n" << "Unique elements: " << uniques << endl;

    return 0;
}

//#include <iostream>
#include <Map.h>
#include <WindowsConsole.h>

using namespace std;

int main()
{
    vector<tuple<int, int, size_t, bool, int, size_t, bool, int>> tls =
        {
            make_tuple(1, 0, 90, true, 2, 0, false, 3),
            make_tuple(2, 4, 270, false, 0, 0, true, 2),
            make_tuple(3, 1, 90, true, 4, 0, false, 2),
            make_tuple(4, 3, 180, false, 0, 180, true, 1)
            /*,
            make_tuple(1, make_pair(make_pair(0, true), make_pair(2, false)), 3),
            make_tuple(2, make_pair(make_pair(3, true), make_pair(0, false)), 2),
            make_tuple(3, make_pair(make_pair(0, true), make_pair(4, false)), 2),
            make_tuple(4, make_pair(make_pair(0, true), make_pair(1, false)), 1),
            make_tuple(1, make_pair(make_pair(0, true), make_pair(2, false)), 3),
            make_tuple(2, make_pair(make_pair(3, true), make_pair(0, false)), 2),
            make_tuple(3, make_pair(make_pair(0, true), make_pair(4, false)), 2),
            make_tuple(4, make_pair(make_pair(0, true), make_pair(1, false)), 1),
            make_tuple(1, make_pair(make_pair(0, true), make_pair(2, false)), 3),
            make_tuple(2, make_pair(make_pair(3, true), make_pair(0, false)), 2),
            make_tuple(3, make_pair(make_pair(0, true), make_pair(4, false)), 2),
            make_tuple(4, make_pair(make_pair(0, true), make_pair(1, false)), 1)*/
        };

    Map m;
	m.createMap(4);
	//m.show();

	WindowsConsole wc(600, 800, "Traffic Simulator");
	wc.PrintMap(tls, 2);

    getchar();

    return 0;
}

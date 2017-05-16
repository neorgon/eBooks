#include <Map.h>
#include <WindowsConsole.h>

using namespace std;

int main()
{
    vector<tuple<int, int, size_t, bool, int, size_t, bool>> tls =
        {
            make_tuple(1, 0, 90,  true,  2, 0,   false),
            make_tuple(2, 4, 270, false, 0, 0,   true),
            make_tuple(3, 1, 90,  true,  0, 0,   false),
            make_tuple(4, 3, 270, false, 0, 0,   true)
            ,
            make_tuple(5, 0, 90,  true,  2, 180, false),
            make_tuple(6, 4, 270, false, 0, 180, true),
            make_tuple(7, 1, 90,  true,  0, 180, false),
            make_tuple(8, 3, 270, false, 0, 180, true),

            make_tuple(9, 0, 90,   true,  2, 0, false),
            make_tuple(10, 4, 270, false, 0, 0, true),
            make_tuple(11, 1, 90,  true,  0, 0, false),
            make_tuple(12, 3, 270, false, 0, 0, true),

            make_tuple(13, 0, 90,  true,  2, 180, false),
            make_tuple(14, 4, 270, false, 0, 180, true),
            make_tuple(15, 1, 90,  true,  0, 180, false),
            make_tuple(16, 3, 270, false, 0, 180, true)
        };

	WindowsConsole wc(600, 800, "Traffic Simulator", 7, 4);
	wc.PrintCity();
	wc.ClearScreen();
	wc.PrintMap(tls, 4);

    getchar();

    return 0;
}

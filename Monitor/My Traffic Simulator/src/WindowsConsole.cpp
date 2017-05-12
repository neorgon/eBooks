#include "WindowsConsole.h"

void WindowsConsole::GotoXY(short int x, short int y)
{
	COORD coord = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	return;
}

void WindowsConsole::GetXY(short int &x, short int &y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;
	}
}

void WindowsConsole::PrintMap(vector<tuple<int, int, size_t, bool, int, size_t, bool, int>> &tls, size_t mapSize)
{
    size_t x = 0, y = 0;

    for (auto &t : tls)
    {
        GotoXY(x * 7, y * 3);
        cout << ":"; //<< get<2>(t)

        if ((x + 1) % mapSize == 0)
        {
            x = 0;
            y++;
        }
        else
        {
            x++;
        }
    }

    /*for (size_t i = 1; i <= tls.size(); i++)
    {
        x = i + (i - 1) * 7;
        for(size_t j = 1; j <= tls.size(); j++)
        {
            y = j + (j - 1) * 3;
            j % 2 == 0 ? SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2) : SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            GotoXY(x, y);
            cout << "*";
        }
    }*/
}

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

void WindowsConsole::PrintMap(vector<tuple<int, pair<int, int>, int, bool>> &tls)
{
    size_t x, y;
    size_t maxTLs = tls.size();

    for (size_t i = 1; i <= maxTLs; i++)
    {
        x = i + (i - 1) * 7;
        for(size_t j = 1; j <= maxTLs; j++)
        {
            y = j + (j - 1) * 3;
            j % 2 == 0 ? SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2) : SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            GotoXY(x, y);
            cout << "*";
        }
    }
}

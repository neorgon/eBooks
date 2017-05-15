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

void WindowsConsole::SetColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), color);
}

void WindowsConsole::PrintMap(vector<tuple<int, int, size_t, bool, int, size_t, bool>> &tls, size_t mapSize)
{
    size_t x = 1, y = 1;

    for (auto &t : tls)
    {
        SetColor(7);
        GotoXY(x * dx, y * dy);
        cout << ":"; //<< get<2>(t)
        DrawDirection(x * dx, y * dy, get<2>(t), get<3>(t));
        DrawDirection(x * dx, y * dy, get<5>(t), get<6>(t));

        if (x % mapSize == 0)
        {
            x = 1;
            y++;
        }
        else
        {
            x++;
        }
    }
}

void WindowsConsole::DrawDirection(int cx, int cy, size_t dir, bool tlGreen)
{
    int i;

    switch (dir)
    {
        case 0:
            for (i = cx + 1; i < cx + (dx - 1); i++)
            {
                SetColor(7);
                GotoXY(i, cy);
                cout << char(196);
            }
            tlGreen ?  SetColor(10): SetColor(12);
            GotoXY(i, cy);
            cout << "*";
        break;
        case 90:
            for (i = cy - 1; i > cy - (dy - 1); i--)
            {
                SetColor(7);
                GotoXY(cx, i);
                cout << char(179);
            }
            tlGreen ?  SetColor(10): SetColor(12);
            GotoXY(cx, i);
            cout << "*";
        break;
        case 180:
            for (i = cx - 1; i > cx - (dx - 1); i--)
            {
                SetColor(7);
                GotoXY(i, cy);
                cout << char(196);
            }
            tlGreen ?  SetColor(10): SetColor(12);
            GotoXY(i, cy);
            cout << "*";
        break;
        case 270:
            for (i = cy + 1; i < cy + (dy - 1); i++)
            {
                SetColor(7);
                GotoXY(cx, i);
                cout << char(179);
            }
            tlGreen ?  SetColor(10): SetColor(12);
            GotoXY(cx, i);
            cout << "*";
        break;
    }
}

#include "../include/WindowsConsole.h"

void WindowsConsole::ClearScreen() const
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
}

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

void WindowsConsole::PrintCity() const
{
    /*const char city[] =
    "\n\
                             *                *                   *     \n\
                 *                                     *                \n\
         *              |           *             *        *         *  \n\
              *        -+-                 *                            \n\
           __           |      *             *          *        *      \n\
       ___|  |   *     _|_              *    ____    ____               \n\
       [_]|``|__      _| |_        *    |   |....|  |....|    *     *   \n\
          |     |   _|[] []|_    ___    |   |....|  | ___|__            \n\
       [_]|  `` |__|_  ______|  |   |  |_|  |....|  || -- - |   *     * \n\
          |________  |__     |  |# #|  |_|  |....|  || - -- |  _____    \n\
       [_]| _____ |     |__[]|  |   |  |_|  |....|__|| -- - | |* * *|   \n\
          | [___] |        |__  |# #|  |_|  |....|__|| -- -_|_|* * *|   \n\
       [_]|       | ``        | |   |__| |__|....|  || ___|* *|* * *|   \n\
          | _____ |           |__  #|_______|....|  | |* *|* *|* * *|   \n\
       [_]| [___] |       ``     |__|_______|__  |  | |* *|* *|* * *|   \n\
          |       |            __|_____________|__    |* *|* *|* * *|   \n\
       [_]| _____ |  ``      _|___________________|_  |* *|* *|* * *|   \n\
          | [___] |         |_______________________|  ______________   \n\
        __|_______|_________|_______________________| _________________ \n\
       |_______________________________________________________________|\n\
       |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\
       ||||||||||||||||||||||  Traffic Simulator  ||||||||||||||||||||||\n\
       |||||||||||||||    ...:: FUNDACION JALA ::...    ||||||||||||||||\n\
       ||||||||||||||||||||||||||||DEV INT 22|||||||||||||||||||||||||||\n\
       |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\
       |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\
       |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n\
    ";

    for (int i = 0; i < 18; i ++) printf("\n");
    printf("%s", city);
    int j = 300000;
    for (int i = 0; i < 18; i ++) {
        usleep(j);
        j = (int)(j * 0.9);
        printf("\n");
    }
    printf("Press any key to continue\n");
    getchar();*/
}

void WindowsConsole::PrintMap(const map<int, vector<shared_ptr<TrafficLight>>> &tls, size_t mapSize)
{
    size_t x = 1, y = 1;
    int cx, cy;

    for (auto &t : tls)
    {
        SetColor(7);
        GotoXY(x * dx, y * dy);
        cout << ":";
        DrawDirection
            (
                cx = x * dx,
                cy = y * dy,
                t.second[0]->GetDirection(),
                t.second[0]->GetLight(),
                t.second[0]->CountVehicles()
            );
        t.second[0]->SetCoord(cx, cy);
        DrawDirection
            (
                cx = x * dx,
                cy = y * dy,
                t.second[1]->GetDirection(),
                t.second[1]->GetLight(),
                t.second[1]->CountVehicles()
            );
        t.second[1]->SetCoord(cx, cy);
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

void WindowsConsole::DrawDirection(int &cx, int &cy, size_t dir, bool tlGreen, size_t vehicles)
{
    int i;

    switch (dir)
    {
        case 0:
            tlGreen ?  SetColor(10): SetColor(12);
            GotoXY(cx - 1, cy);
            cout << "*";
            for (i = cx - (dx - 1); i < cx; i++)
            {
                SetColor(7);
                GotoXY(i, cy);
                cout << char(196);
            }
            SetColor(15);
            GotoXY(cx - 3, cy);
            cout << vehicles;
            cx--;
        break;
        case 90:
            tlGreen ?  SetColor(10): SetColor(12);
            GotoXY(cx, cy + 1);
            cout << "*";
            for (i = cy + 1; i < cy + dy; i++)
            {
                SetColor(7);
                GotoXY(cx, i);
                cout << char(179);
            }
            SetColor(15);
            GotoXY(cx, cy + 2);
            cout << vehicles;
            cy++;
        break;
        case 180:
            tlGreen ?  SetColor(10): SetColor(12);
            GotoXY(cx + 1, cy);
            cout << "*";
            for (i = cx + 1; i < cx + dx; i++)
            {
                SetColor(7);
                GotoXY(i, cy);
                cout << char(196);
            }
            SetColor(15);
            GotoXY(cx + 3, cy);
            cout << vehicles;
            cx++;
        break;
        case 270:
            tlGreen ?  SetColor(10): SetColor(12);
            GotoXY(cx, cy - 1);
            cout << "*";
            for (i = cy - (dy - 1); i < cy; i++)
            {
                SetColor(7);
                GotoXY(cx, i);
                cout << char(179);
            }
            SetColor(15);
            GotoXY(cx, cy - 2);
            cout << vehicles;
            cy--;
        break;
    }
}

void WindowsConsole::ToUpdate(bool light, int x, int y, int direction, int vehicles)
{
    light ? SetColor(10) : SetColor(12);
    GotoXY(x, y);
    cout << "*";
    switch (direction)
    {
        case 0:
            SetColor(15);
            GotoXY(x - 2, y);
            cout << vehicles;
        break;
        case 90:
            SetColor(15);
            GotoXY(x, y + 1);
            cout << vehicles;
        break;
        case 180:
            SetColor(15);
            GotoXY(x + 2, y);
            cout << vehicles;
        break;
        case 270:
            SetColor(15);
            GotoXY(x, y - 1);
            cout << vehicles;
        break;
    }
}

void WindowsConsole::UpdateMap(const map<int, vector<shared_ptr<TrafficLight>>> &tls)
{
    for (auto &t : tls)
    {
        ToUpdate
        (
            t.second[0]->GetLight(),
            t.second[0]->GetCoord().x,
            t.second[0]->GetCoord().y,
            t.second[0]->GetDirection(),
            t.second[0]->CountVehicles()
        );
        ToUpdate
        (
            t.second[1]->GetLight(),
            t.second[1]->GetCoord().x,
            t.second[1]->GetCoord().y,
            t.second[1]->GetDirection(),
            t.second[1]->CountVehicles()
        );
    }
}

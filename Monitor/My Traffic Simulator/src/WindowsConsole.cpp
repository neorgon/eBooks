#include "WindowsConsole.h"

#include <stdio.h>
#include <unistd.h>
#include <TrafficLight.h>

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
    const char city[] =
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
    getchar();
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

#ifndef WINDOWSCONSOLE_H
#define WINDOWSCONSOLE_H

#include <iostream>
#include <tuple>
#include <vector>
#include <windows.h>

using namespace std;

class WindowsConsole
{
    HWND console = GetConsoleWindow();
    RECT wSizePos;
    size_t vsHeight, vsWidth;
    const char* windowTitle;

    public:
        WindowsConsole(size_t h, size_t w, const char* t) : vsHeight{h}, vsWidth{w}, windowTitle {t}
        {
            SetConsoleTitle(windowTitle);
            GetWindowRect(console, &wSizePos);
            MoveWindow(console, wSizePos.left, wSizePos.top, vsWidth, vsHeight, TRUE);
        }

        void GotoXY(short int x, short int y);
        void GetXY(short int &x, short int &y);
        void PrintMap(vector<tuple<int, int, size_t, bool, int, size_t, bool, int>> &tls, size_t mapSize);
};

#endif // WINDOWSCONSOLE_H

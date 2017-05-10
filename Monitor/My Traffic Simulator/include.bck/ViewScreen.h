#ifndef VIEWSCREEN_H
#define VIEWSCREEN_H

#include <iostream>
#include <windows.h>

using namespace std;

class ViewScreen
{
    HWND console = GetConsoleWindow();
    RECT wSizePos;
    size_t vsHeight, vsWidth;
    const char* windowTitle;

    public:
        ViewScreen(size_t h, size_t w, const char* t) : vsHeight{h}, vsWidth{w}, windowTitle {t}
        {
            SetConsoleTitle(windowTitle);
            GetWindowRect(console, &wSizePos);
            MoveWindow(console, wSizePos.left, wSizePos.top, vsWidth, vsHeight, TRUE);
        }

        void GotoXY(short int x, short int y);
        void GetXY(short int &x, short int &y);
        void PrintTL(size_t maxTLs);
};

#endif // VIEWSCREEN_H

#ifndef WINDOWSCONSOLE_H
#define WINDOWSCONSOLE_H

#include <iostream>
#include <Map.h>
#include <windows.h>

using namespace std;

class WindowsConsole
{
    HWND console = GetConsoleWindow();
    RECT wSizePos;
    size_t vsHeight, vsWidth;
    const char* windowTitle;
    int dx, dy;

    public:
        WindowsConsole(size_t h, size_t w, const char* t, int dx, int dy) :
            vsHeight{h}, vsWidth{w}, windowTitle {t}, dx {dx}, dy {dy}
        {
            SetConsoleTitle(windowTitle);
            GetWindowRect(console, &wSizePos);
            MoveWindow(console, wSizePos.left, wSizePos.top, vsWidth, vsHeight, TRUE);
        }

        void ClearScreen() const;
        void GotoXY(short int x, short int y);
        void GetXY(short int &x, short int &y);
        void SetColor(int color);
        void PrintCity() const;
        void PrintMap(const map<int, vector<shared_ptr<TrafficLight>>> &tls, size_t mapSize);
        void DrawDirection(int cx, int cy, size_t dir, bool tlGreen);
};

#endif // WINDOWSCONSOLE_H

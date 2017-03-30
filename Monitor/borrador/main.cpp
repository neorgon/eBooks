// Warning: I didn't try to compile this...
#include <cassert>
#include <string>
#include <iostream>
#include <windows.h>

using namespace std;

void displayFrame( int w, int h ) {
    assert( h >= 2 );   // Height has to be at least 2 for a top and bottom side
    assert( w >= 2 );  // Width has to be at least 2 for a left and right side

    // Draw row of 'w' asterisks for top side
    cout << string( w, '*' ) << endl;

    // Draw sides: asterisk, width-2 spaces, asterisk
    for( int j = 0; j < h - 2; ++j )
        cout << '*' << string( w - 2, ' ' ) << '*' << endl;

    // Draw row of 'w' asterisks for bottom side
    cout << string( w, '*' ) << endl;
}

int main()
{
    short int x = 5;  short int y = 6;
COORD pos = {x, y};
HANDLE hConsole_c = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
SetConsoleActiveScreenBuffer(hConsole_c);
char *str = "Some Text\r\n";
DWORD len = strlen(str);
DWORD dwBytesWritten = 0;
WriteConsoleOutputCharacter(hConsole_c, str, len, pos, &dwBytesWritten);
CloseHandle(hConsole_c);

    return 0;
}
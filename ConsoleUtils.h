#ifndef CONSOLEUTILS_H
#define CONSOLEUTILS_H

#include <windows.h>

class ConsoleUtils {
private:
    static HANDLE hConsole;      // For output
    static HANDLE hInput;        // For input

public:
    // Initialization
    static void init();

    // Screen manipulation
    static void gotoxy(int x, int y);
    static void setColor(int color);
    static void clearScreen();

    // Mouse input functions
    static bool getMouseClick(int& x, int& y);           // Non-blocking version
    static bool getMouseClickBlocking(int& x, int& y);   // Blocking version (instructor's exact method)

    // Console mode configuration
    static void enableMouseInput();

    // Additional utility functions (optional)
    static void hideCursor();
    static void showCursor();
    static int getConsoleWidth();
    static int getConsoleHeight();

    // Alternative: Functions matching instructor's style
    static void gotoRowCol(int row, int col);  // Same as gotoxy but with row/col naming
    static void getRowColbyLeftClick(int& row, int& col);  // Instructor's exact method
};

#endif
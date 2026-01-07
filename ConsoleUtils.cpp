#include "ConsoleUtils.h"
#include <iostream>
using namespace std;

HANDLE ConsoleUtils::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE ConsoleUtils::hInput = GetStdHandle(STD_INPUT_HANDLE);

void ConsoleUtils::init() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    hInput = GetStdHandle(STD_INPUT_HANDLE);

    // Hide cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    // Enable mouse input
    enableMouseInput();
}

void ConsoleUtils::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
}

void ConsoleUtils::setColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

// Using instructor's reliable mouse input method
bool ConsoleUtils::getMouseClick(int& x, int& y) {
    DWORD Events;
    INPUT_RECORD InputRecord;

    // Set console mode
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    // Check if there's input available
    if (!PeekConsoleInput(hInput, &InputRecord, 1, &Events)) {
        return false;
    }

    if (Events > 0) {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);

        if (InputRecord.EventType == MOUSE_EVENT) {
            if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                x = InputRecord.Event.MouseEvent.dwMousePosition.X;
                y = InputRecord.Event.MouseEvent.dwMousePosition.Y;

                // Flush buffer to prevent multiple clicks
                FlushConsoleInputBuffer(hInput);
                return true;
            }
        }
    }

    return false;
}

// Alternative: Instructor's exact blocking method
bool ConsoleUtils::getMouseClickBlocking(int& x, int& y) {
    DWORD Events;
    INPUT_RECORD InputRecord;

    // Set console mode
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

    do {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
            x = InputRecord.Event.MouseEvent.dwMousePosition.X;
            y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            return true;
        }
    } while (true);

    return false;
}

void ConsoleUtils::enableMouseInput() {
    DWORD mode;
    GetConsoleMode(hInput, &mode);

    // Enable mouse input and extended flags
    mode |= ENABLE_MOUSE_INPUT;
    mode |= ENABLE_EXTENDED_FLAGS;

    // Disable quick edit mode - CRUCIAL!
    mode &= ~ENABLE_QUICK_EDIT_MODE;

    SetConsoleMode(hInput, mode);
}

void ConsoleUtils::clearScreen() {
    system("cls");
}
#ifndef SETTINGS_H
#define SETTINGS_H

class Settings {
public:
    static int boardSize;
    static int lightSquare;
    static int darkSquare;
    static int highlightColor;

    static void setDefaults();
    static void showSettingsMenu();
};

#endif
#pragma once
#define _HAS_STD_BYTE 0
#include <windows.h>

class ConsoleSystem
{
public:
    static void SetColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    static void HideCursor() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(hConsole, &cursorInfo);
        cursorInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hConsole, &cursorInfo);
    }

    static void MoveCursorToTop() {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });
    }
    
    static void ClearLine(int x, int y, int length = 80) {
        COORD pos = { (SHORT)x, (SHORT)y };
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsole, pos);
        for (int i = 0; i < length; i++) std::cout << " "; // 공백으로 밀기
        SetConsoleCursorPosition(hConsole, pos); // 다시 원래 위치로
    }
};

#include "Colors.h"
#include <iostream>
#include <Windows.h>

void setColor(int textColor, int bgColor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}

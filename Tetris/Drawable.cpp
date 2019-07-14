#include "Drawable.h"
#include <windows.h>

int Drawable::getstartX()
{
	return startX;
}

void Drawable::hideCursor()
{
	CONSOLE_CURSOR_INFO info = { 100,FALSE };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Drawable::MoveTo(int x, int y)
{
	COORD coord = { startY + y,startX + x };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
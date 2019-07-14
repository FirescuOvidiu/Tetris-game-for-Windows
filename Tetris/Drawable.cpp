#include "Drawable.h"
#include <windows.h>


int Drawable::getstartPositionX()
{
	return startPositionX;
}

void Drawable::hideCursor()
{
	CONSOLE_CURSOR_INFO info = { 100,FALSE };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Drawable::MoveTo(int x, int y)
{
	COORD coord = { startPositionY + y,startPositionX + x };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
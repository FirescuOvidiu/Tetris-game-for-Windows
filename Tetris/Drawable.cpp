#include "Drawable.h"

int Drawable::getstartPositionX()
{
	return startPositionX;
}

void Drawable::hidecursor()
{
	CONSOLE_CURSOR_INFO info = { 100,FALSE };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Drawable::MoveTo(const int &x, const int &y)
{
	COORD coord = { startPositionY + y,startPositionX + x };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#pragma once

#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <windows.h>

class Drawable
{
protected:
	//The position where the table game will be displayed in console
	static constexpr int startPositionX{ 10 };
	static constexpr int startPositionY{ 25 };

public:
	static int getstartPositionX();
	static void hidecursor();
	static void MoveTo(const int &x,const int &y);
	virtual void Draw() = 0;
	virtual void DeleteDraw() = 0;
};

#endif // !DRAWABLE_H
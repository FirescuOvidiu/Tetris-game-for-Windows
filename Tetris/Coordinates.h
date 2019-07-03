#pragma once

#ifndef COORDINATES_H
#define COORDINATES_H

#include "Drawable.h"
#include "Actions.h"
#include <iostream>

using namespace std;

class Coordinates : public Drawable
{
private:
	int x;
	int y;
	static constexpr char form{ '*' };
	static constexpr int color{ 1 };
public:
	Coordinates(int x = 0, int y = 0);
	Coordinates& operator =(const Coordinates &coord);
	static char getForm();
	int getX();
	int getY();
	void setX(const int &x);
	void setY(const int &y);
	void moveCoordinatesInADirection(char direction);
	void Draw() override;
	void DeleteDraw() override;
};

#endif // !Coordinates_H
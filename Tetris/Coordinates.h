#pragma once

#ifndef COORDINATES_H
#define COORDINATES_H

#include "Actions.h"
#include "Drawable.h"
#include <iostream>

using namespace std;

class Coordinates : public Drawable
{
private:
	int x;
	int y;
public:
	static constexpr char form{ '*' };

public:
	Coordinates(int x = 0, int y = 0);
	Coordinates& operator =(const Coordinates &coord);
	int getX();
	int getY();
	void setX(const int &x);
	void setY(const int &y);
	// Methods using a coordinate
	void moveCoordinatesInADirection(char direction);
	void Draw() override;
	void DeleteDraw() override;
};

#endif // !Coordinates_H
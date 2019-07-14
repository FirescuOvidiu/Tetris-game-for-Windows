#pragma once

#ifndef COORDINATES_H
#define COORDINATES_H

#include "Drawable.h"

using namespace std;

class Coordinates : public Drawable
{
public:
	Coordinates(int x = 0, int y = 0);

	int getX() const;
	int getY() const;

	void setX(int x);
	void setY(int y);

	void moveCoordinates(char direction);

	void draw() override;
	void deleteDraw() override;

public:
	static constexpr char form{ '*' };

private:
	int x;
	int y;
};

#endif // !Coordinates_H
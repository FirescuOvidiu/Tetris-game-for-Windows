#include "Actions.h"
#include "Coordinates.h"
#include <iostream>

namespace tetris
{
	int Coordinates::getX() const
	{
		return x;
	}

	int Coordinates::getY() const
	{
		return y;
	}

	void Coordinates::setX(int x)
	{
		this->x = x;
	}

	void Coordinates::setY(int y)
	{
		this->y = y;
	}

	void Coordinates::moveCoordinates(char direction)
	{
		switch (direction)
		{
		case Action::moveLEFT:
			y--;
			break;
		case Action::moveRIGHT:
			y++;
			break;
		case Action::moveDOWN:
			x++;
			break;
		default:
			break;
		}
	}

	void Coordinates::draw()
	{
		MoveTo(x + Drawable::startX, y + Drawable::startY);
		std::cout << form;
	}

	void Coordinates::deleteDraw()
	{
		MoveTo(x + Drawable::startX, y + Drawable::startY);
		std::cout << " ";
	}
}
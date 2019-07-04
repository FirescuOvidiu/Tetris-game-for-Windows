#include "Coordinates.h"

Coordinates::Coordinates(int x, int y)
{
	this->x = x;
	this->y = y;
}

Coordinates& Coordinates::operator=(const Coordinates &coord)
{
	if (this != &coord)
	{
		this->x = coord.x;
		this->y = coord.y;
	}
	return *this;
}

char Coordinates::getForm()
{
	return form;
}

int Coordinates::getX()
{
	return x;
}

int Coordinates::getY()
{
	return y;
}

void Coordinates::setX(const int &x)
{
	this->x = x;
}

void Coordinates::setY(const int &y)
{
	this->y = y;
}

void Coordinates::moveCoordinatesInADirection(char direction)
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

void Coordinates::Draw()
{
	MoveTo(x + Drawable::startPositionX, y + Drawable::startPositionY);
	cout << form;
}

void Coordinates::DeleteDraw()
{
	MoveTo(x + Drawable::startPositionX, y + Drawable::startPositionY);
	cout << " ";
}
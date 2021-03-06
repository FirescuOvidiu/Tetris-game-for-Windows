#pragma once

#ifndef COORDINATES_H
#define COORDINATES_H

#include "Drawable.h"

namespace tetris
{
	class Coordinates : public Drawable
	{
	public:
		Coordinates(int x = 0, int y = 0) : x(x), y(y) {}

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

}
#endif // !Coordinates_H
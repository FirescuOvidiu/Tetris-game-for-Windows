#include "Actions.h"
#include "Table.h"
#include <fstream>

namespace tetris
{
	/*
		A tile is in tiles.in is saved like this:
			0 0 0 2
			0 2 2 2
			0 0 0 0
			0 0 0 0
		A tile stores has a array of 4 coordinates(Coordinates) and a center(int)
		In the array we will save the 4 coordinates ((0,3) (1,1) (1,2) (1,3)) that don't have the value 0 in matrix, and in the centerOfTile the center of the figure
	*/

	void Tile::initTile(std::ifstream& input)
	{
		int counter = 0;
		int checkValue = 0;

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				input >> checkValue;

				if (checkValue != 0)
				{
					coordTile.at(counter).setX(x);
					coordTile.at(counter).setY(Table::numberOfColumns / 2 + 2 - y);	// Setting the coordinate for Y in the middle of the table
					counter++;

					if ((x == 1) && (y == 2))
					{
						centerOfTile = counter - 1;
					}
				}
			}
		}
	}

	int Tile::getcoordX(int position) const
	{
		return coordTile.at(position).getX();
	}

	int Tile::getcoordY(int position) const
	{
		return coordTile.at(position).getY();
	}

	int Tile::getcenterOfTile(int position) const
	{
		return centerOfTile;
	}

	void Tile::setcoordX(int position, int x)
	{
		coordTile.at(position).setX(x);
	}

	void Tile::setcoordY(int position, int y)
	{
		coordTile.at(position).setY(y);
	}

	void Tile::setcenterOfTile(int centerOfTile)
	{
		this->centerOfTile = centerOfTile;
	}

	void Tile::moveTile(char direction)
	{
		for (int currentCoordinate = 0; currentCoordinate < 4; currentCoordinate++)
		{
			coordTile.at(currentCoordinate).moveCoordinates(direction);
		}
	}

	void Tile::rotateTile(char direction)
	{
		int dir = 0;

		switch (direction)
		{
		case Action::rotateRIGHT:           // To rotate the tile to the right we need +90* check formula down
			dir = +90;
			break;
		case Action::rotateLEFT:           // To rotate the tile to the left we need -90* check formula down
			dir = -90;
			break;
		default:
			return;
		}

		// If the tile can be rotated
		if (centerOfTile != -1)
		{
			double centerOfTileX = coordTile.at(centerOfTile).getX();
			double centerOfTileY = coordTile.at(centerOfTile).getY();

			double tileX = 0;
			double tileY = 0;

			// Rotate every piece(point/coordinate) from the tile with 90*(to right) or -90*(to left) depends on dir
			for (int currentCoordinate = 0; currentCoordinate < 4; currentCoordinate++)
			{
				tileX = (double)coordTile.at(currentCoordinate).getX();
				tileY = (double)coordTile.at(currentCoordinate).getY();

				coordTile.at(currentCoordinate).setX((int)round((tileX - centerOfTileX) * cos((3.14 * dir) / 180) +
					(tileY - centerOfTileY) * sin((3.14 * dir) / 180) + centerOfTileX));
				coordTile.at(currentCoordinate).setY((int)round((centerOfTileX - tileX) * sin((3.14 * dir) / 180) +
					(tileY - centerOfTileY) * cos((3.14 * dir) / 180) + centerOfTileY));
			}
		}
	}

	void Tile::draw()
	{
		for (int currentCoordinate = 0; currentCoordinate < 4; currentCoordinate++)
		{
			coordTile.at(currentCoordinate).draw();             // Drawing the tile by drawing every piece (point/coordinate) of it
		}
	}

	void Tile::deleteDraw()
	{
		for (int currentCoordinate = 0; currentCoordinate < 4; currentCoordinate++)
		{
			coordTile.at(currentCoordinate).deleteDraw();      // Deleting the tile by deleting every piece (point/coordinate) of it
		}
	}
}
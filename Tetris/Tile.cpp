#include "Tile.h"
#include "Table.h"

Tile::Tile()
{
	for (int index = 0; index < 4; index++)
	{
		coordTile[index].setX(0);
		coordTile[index].setY(0);
	}

	centerOfTile = -1;
}

Tile& Tile::operator=(const Tile &tile)
{
	if (this != &tile)
	{
		for (int i = 0; i < 4; i++)
		{
			this->coordTile[i] = tile.coordTile[i];
		}
		this->centerOfTile = tile.centerOfTile;
	}

	return *this;
}

/*
	A tile is in tiles.in is saved like this:
		0 0 0 2
		0 2 2 2
		0 0 0 0
		0 0 0 0
	A tile stores has a array of 4 coordinates(Coordinates) and a center(int)
	In the array we will save the 4 coordinates ((0,3) (1,1) (1,2) (1,3)) that don't have the value 0 in matrix, and in the centerOfTile the center of the figure
*/

void Tile::initializationOfTile(ifstream& input)
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
				coordTile[counter].setX(x);
				coordTile[counter++].setY(Table::numberOfColumns / 2 + 2 - y);	// Setting the coordinate for Y in the middle of the table

				if ((x == 1) && (y == 2))
				{
					centerOfTile = counter - 1;
				}
			}
		}
	}
}

int Tile::getcoordX(const int &position)
{
	return coordTile[position].getX();
}

int Tile::getcoordY(const int &position)
{
	return coordTile[position].getY();
}

int Tile::getcenterOfTile(const int &position)
{
	return centerOfTile;
}

void Tile::setcoordX(const int &position, const int &x)
{
	coordTile[position].setX(x);
}

void Tile::setcoordY(const int &position, const int &y)
{
	coordTile[position].setY(y);
}

void Tile::setcenterOfTile(const int &centerOfTile)
{
	this->centerOfTile = centerOfTile;
}

void Tile::moveTileInADirection(char direction)
{
	for (int currentCoordinate = 0; currentCoordinate < 4; currentCoordinate++)
	{
		coordTile[currentCoordinate].moveCoordinatesInADirection(direction);
	}
}

void Tile::rotateTileInADirection(char direction)
{
	int dir = 0;

	switch (direction)
	{
	case Action::rotateRIGHT:           // to rotate the tile to the right we need +90* check formula down
		dir = +90;
		break;
	case Action::rotateLEFT:           // to rotate the tile to the left we need -90* check formula down
		dir = -90;
		break;
	default:
		return;
	}

	// If the tile can be rotated
	if (centerOfTile != -1)
	{
		double centerOfTileX = coordTile[centerOfTile].getX();
		double centerOfTileY = coordTile[centerOfTile].getY();

		double tileX = 0;
		double tileY = 0;

		// Rotate every piece(point/coordinate) from the tile with 90*(to right) or -90*(to left) depends on dir
		for (int currentCoordinate = 0; currentCoordinate < 4; currentCoordinate++)
		{
			tileX = (double) coordTile[currentCoordinate].getX();
			tileY = (double) coordTile[currentCoordinate].getY();

			coordTile[currentCoordinate].setX((int)round((tileX - centerOfTileX) * cos((3.14 * dir) / 180) +
				(tileY - centerOfTileY) * sin((3.14 * dir) / 180) + centerOfTileX));
			coordTile[currentCoordinate].setY((int)round((centerOfTileX - tileX) * sin((3.14 * dir) / 180) +
				(tileY - centerOfTileY) * cos((3.14 * dir) / 180) + centerOfTileY));
		}
	}
}

void Tile::Draw()
{
	for (int currentCoordinate = 0; currentCoordinate < 4; currentCoordinate++)
	{
		coordTile[currentCoordinate].Draw();             // Drawing the tile by drawing every piece (point/coordinate) of it
	}
}

void Tile::DeleteDraw()
{
	for (int currentCoordinate = 0; currentCoordinate < 4; currentCoordinate++)
	{
		coordTile[currentCoordinate].DeleteDraw();      // Deleting the tile by deleting every piece (point/coordinate) of it
	}
}
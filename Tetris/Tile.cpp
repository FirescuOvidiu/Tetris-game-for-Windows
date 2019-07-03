#include "Tile.h"

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
	In the array we will save the 4 coordinates ((0,3) (1,1) (1,2) (1,3)) that don't have the value 0 in matrix, and in the center the center of the figure
*/

void Tile::initializationOfTile(ifstream& input)
{
	int counter = 0;
	int check = 0;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (check != 0)
			{
				coordTile[counter].setX(x);
				coordTile[counter++].setY(y);

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
	for (int i = 0; i < 4; i++)
	{
		coordTile[i].moveCoordinatesInADirection(direction);
	}
}

void Tile::rotateTileInADirection(char direction)
{
	int dir = 0;

	switch (direction)
	{
	case Action::rotateRIGHT:           // to rotate the tile to the right we need +90* check formula down
		dir = 1;
		break;
	case Action::rotateLEFT:           // to rotate the tile to the left we need -90* check formula down
		dir = -1;
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
		for (int i = 0; i < 4; i++)
		{
			tileX = (double) coordTile[i].getX();
			tileY = (double) coordTile[i].getY();
			coordTile[i].setX((int)round((tileX - centerOfTileX)*cos((90 * 3.14*dir) / 180) + 
				(tileY - centerOfTileY)*sin((90 * 3.14*dir) / 180) + centerOfTileX));
			coordTile[i].setY((int)round((centerOfTileX - tileX)*sin((90 * 3.14*dir) / 180) +
				(tileY - centerOfTileY)*cos((90 * 3.14*dir) / 180) + centerOfTileY));
		}
	}
}

void Tile::DeleteDraw()
{
	for (int i = 0; i < 4; i++)
	{
		coordTile[i].DeleteDraw();      // Deleting the tile by deleting every piece(point/coordinate) of it
	}
}

void Tile::Draw()
{
	for (int i = 0; i < 4; i++)
	{
		coordTile[i].Draw();             // Drawing the tile by drawing every piece(point/coordinate) of it
	}
}
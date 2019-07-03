#include "Tiles.h"

Tiles::Tiles()
{
	ifstream input("tiles.in");
	input >> numberOfTiles;

	figures = new Tile[numberOfTiles];

	initializationOfTiles(input);

	input.close();
}

void Tiles::initializationOfTiles(ifstream &input)
{

	for (int currentTile = 0; currentTile < numberOfTiles; currentTile++)
	{
		figures[currentTile].initializationOfTile(input);
	}

	//The center of a line respectively a square is different than the other figures
	figures[0].setcenterOfTile(2);
	figures[3].setcenterOfTile(-1);
}

Tile Tiles::getTile(int number)
{
	return figures[number];
}

int Tiles::getNumberOfTiles()
{
	return numberOfTiles;
}

Tiles::~Tiles()
{
	delete[] figures;
}
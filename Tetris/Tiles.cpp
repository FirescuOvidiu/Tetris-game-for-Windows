#include "Tiles.h"


int Tiles::numberOfTiles = initializationOfNumberOfTiles();
Tile* Tiles::figures = initializationOfFigures();

int Tiles::initializationOfNumberOfTiles()
{
	int numberOfTiles = 0;

	ifstream input("tiles.in");
	input >> numberOfTiles;
	input.close();

	return numberOfTiles;
}

Tile* Tiles::initializationOfFigures()
{
	Tile* figures;
	int numberOfTiles = 0;

	ifstream input("tiles.in");
	input >> numberOfTiles;
	figures = new Tile[numberOfTiles];

	for (int currentTile = 0; currentTile < numberOfTiles; currentTile++)
	{
		figures[currentTile].initializationOfTile(input);
	}

	//The center of a line respectively a square is different than the other figures
	figures[0].setcenterOfTile(2);
	figures[3].setcenterOfTile(-1);

	input.close();

	return figures;
}

Tile Tiles::generateRandomTile()
{
	Tile randomTile;
	int randomNumber = 0;

	random_device random;
	uniform_int_distribution<int>dist(0, numberOfTiles - 1);

	randomNumber = dist(random);
	randomTile = figures[randomNumber];

	return randomTile;
}

Tiles::~Tiles()
{
	delete[] figures;
}

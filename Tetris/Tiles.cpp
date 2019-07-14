#include "Actions.h"
#include "Tiles.h"
#include <random>

using namespace std;

int Tiles::numberOfTiles = initNumberOfTiles();
vector<Tile> Tiles::figures = initFigures();

int Tiles::initNumberOfTiles()
{
	int numberOfTiles{ 0 };
	ifstream input("tiles.in");

	input >> numberOfTiles;

	input.close();

	return numberOfTiles;
}

vector<Tile> Tiles::initFigures()
{
	ifstream input("tiles.in");
	int numberOfTiles{};

	input >> numberOfTiles;

	vector<Tile> figures(numberOfTiles);
	for (int currentTile = 0; currentTile < numberOfTiles; currentTile++)
	{
		figures.at(currentTile).initTile(input);
	}

	//The center of a line respectively a square is different than the other figures
	figures.at(0).setcenterOfTile(2);
	figures.at(3).setcenterOfTile(-1);

	input.close();

	return figures;
}

Tile Tiles::generateRandomTile()
{
	Tile randomTile{};
	int randomNumber = 0;

	random_device random;
	uniform_int_distribution<int>dist(0, numberOfTiles - 1);

	randomNumber = dist(random);
	randomTile = figures[randomNumber];

	return randomTile;
}

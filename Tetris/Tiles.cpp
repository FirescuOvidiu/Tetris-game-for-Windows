#include "Actions.h"
#include "Tiles.h"
#include <random>

int Tiles::numberOfTiles = initNumberOfTiles();
std::vector<Tile> Tiles::figures = initFigures();

int Tiles::initNumberOfTiles()
{
	int numberOfTiles{ 0 };
	std::ifstream input("tiles.in");

	input >> numberOfTiles;

	input.close();

	return numberOfTiles;
}

std::vector<Tile> Tiles::initFigures()
{
	std::ifstream input("tiles.in");
	int numberOfTiles{};

	input >> numberOfTiles;

	std::vector<Tile> figures(numberOfTiles);
	for (int currentTile = 0; currentTile < numberOfTiles; currentTile++)
	{
		figures.at(currentTile).initTile(input);
	}

	// The center of a line respectively a square is different than the other figures
	figures.at(0).setcenterOfTile(2);
	figures.at(3).setcenterOfTile(-1);

	input.close();

	return figures;
}

Tile Tiles::generateRandomTile()
{
	Tile randomTile{};
	int randomNumber = 0;

	std::random_device random;
	std::uniform_int_distribution<int>dist(0, numberOfTiles - 1);

	randomNumber = dist(random);
	randomTile = figures[randomNumber];

	return randomTile;
}

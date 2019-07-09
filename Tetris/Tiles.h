#pragma once

#ifndef TILES_H
#define TILES_H

#include "Tile.h"
#include <fstream>
#include <random>

class Tiles                 // Contains the number of tiles and the tiles possible
{
private:
	static int numberOfTiles;
	static Tile* figures;

private:
	static int initializationOfNumberOfTiles();
	static Tile* initializationOfFigures();
	~Tiles();

public:
	static Tile generateRandomTile();
};

#endif // !TILES_H

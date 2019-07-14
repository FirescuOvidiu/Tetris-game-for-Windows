#pragma once

#ifndef TILES_H
#define TILES_H

#include "Tile.h"

// Contains the number of tiles and the tiles possible
class Tiles
{
public:
	static Tile generateRandomTile();

private:
	static int initNumberOfTiles();
	static Tile* initFigures();
	~Tiles();

private:
	static int numberOfTiles;
	static Tile* figures;
};

#endif // !TILES_H

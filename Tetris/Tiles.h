#pragma once

#ifndef TILES_H
#define TILES_H

#include "Tile.h"
#include <fstream>

class Tiles                 // class that represents the number of tiles the game has and all tiles
{
private:
	int numberOfTiles;
	Tile* figures;

public:
	Tiles();
	void initializationOfTiles(ifstream& input);
	Tile getTile(int number);
	int getNumberOfTiles();
	~Tiles();
};

#endif // !TILES_H

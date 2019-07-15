#pragma once

#ifndef TILES_H
#define TILES_H

#include "Tile.h"

// Contains the number of tiles and the tiles possible
namespace tetris
{
	class Tiles
	{
	public:
		static Tile generateRandomTile();

	private:
		static int initNumberOfTiles();
		static std::vector<Tile> initFigures();

	private:
		static int numberOfTiles;
		static std::vector<Tile> figures;
	};
}
#endif // !TILES_H

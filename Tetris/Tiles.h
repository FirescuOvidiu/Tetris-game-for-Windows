#pragma once

#ifndef TILES_H
#define TILES_H

#include "Tile.h"

namespace tetris
{
	// Contains the number of tiles and the tiles possible
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

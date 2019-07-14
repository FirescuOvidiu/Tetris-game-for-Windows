#pragma once

#ifndef TILE_H
#define TILE_H

#include "Coordinates.h"
#include <fstream>
#include <vector>

class Tile : public Drawable
{
public:
	Tile() : coordTile(4), centerOfTile(-1) {}

	void initTile(std::ifstream& input);

	int getcenterOfTile(int position) const;
	int getcoordX(int position) const;
	int getcoordY(int position) const;

	void setcenterOfTile(int centerOfTile);
	void setcoordX(int position, int x);
	void setcoordY(int position, int y);

	void moveTile(char direction);
	void rotateTile(char direction);

	void draw() override;                             // Method used to draw the tile in the game table
	void deleteDraw() override;                      // Method used to delete the tile from the game table

private:
	// Every tile is composed of 4 coordinates and a center
	std::vector <Coordinates> coordTile;
	int centerOfTile;
};

#endif // !TILE_H
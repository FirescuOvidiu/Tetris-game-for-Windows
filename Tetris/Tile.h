#pragma once

#ifndef TILE_H
#define TILE_H

#include "Coordinates.h"
#include "Drawable.h"
#include <fstream>

// Class that represents a tile and all its methods
class Tile : public Drawable
{
private:
	// Every tile is composed of 4 coordinates and a center
	Coordinates coordTile[4];
	int centerOfTile;

public:
	Tile();
	Tile& operator=(const Tile &tile);
	void initializationOfTile(ifstream& input);
	// Getter and setter
	int getcenterOfTile(const int &position);
	int getcoordX(const int &position);
	int getcoordY(const int &position);
	void setcenterOfTile(const int &centerOfTile);
	void setcoordX(const int &position, const int &x);
	void setcoordY(const int &position, const int &y);
	// Methods using a tile
	void moveTileInADirection(char direction);          // Moves the tile in a specific direction (right, left, down)
	void rotateTileInADirection(char direction);       // Rotates the tile in a specific direction (right, left)
	void Draw() override;                             // Overrides function Draw() from Drawable() and is used to draw the tile in the game table
	void DeleteDraw() override;                      // Overrides function DeleteDraw() from Drawable() and is used to delete the tile from the game table
};

#endif // !TILE_H
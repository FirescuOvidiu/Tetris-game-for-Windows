#pragma once

#ifndef TABLE_H
#define TABLE_H

#include "Difficulty.h"
#include "Tile.h"
#include "Tiles.h"
#include <conio.h>
#include <random>

class Table : public Drawable           // class that represents the game table 
{
public:
	static constexpr int  numberOfColumns{ 11 };
	static constexpr int numberOfLines{ 21 };
	long score;
private:
	int table[numberOfLines][numberOfColumns];            // the game table= a matrix with 0 if there is nothing draw in that point and 1 if there is something draw 
	Tile actualTile;         // the tile that moves in the game table(the actual tile)

public:
	Table();
	void informationAboutGame();
	void checkingAndDeletingCompletedLines();
	void deleteCompletedLineFromTable(const int& line);        // after a line from the table is completated, it will be deleted from the game table and the score will rise
	void moveTileDownAutomatically();
	void moveTileInADirection(char direction);
	void possibleMoves(int& counterTime);         // possible moves of a player (right, left, down)
	void positioningTileInTableAfterRotation();
	void rotateTileInADirection(char direction);
	void startGame();
	void Draw();
	void DeleteDraw();
	bool belongsToActualTile(const int& x, const int& y);
	bool checkIfCanMoveInADirection(char direction);
	bool checkIfPlayerLost();
};

#endif // !TABLE_H
#pragma once

#ifndef TABLE_H
#define TABLE_H

#include "Drawable.h"
#include "Tile.h"

// Class that represents the game table 

class Table : public Drawable
{
public:
	Table() : score(0), table(numberOfLines, std::vector<int>(numberOfColumns)) {}
	void gameInfo() const;

	void deleteCompletedLines();
	void deleteCompletedLine(int line);
	
	void moveTileDown();
	void moveTile(char direction);
	void possibleMoves(int& counterTime);
	
	// There are situations where a tile can't be rotate, after we rotate it we check if the rotation was valid
	// If it wasn't moveTileToLastPosition will change the tile coordinates to his original coordinates before rotation 
	// Than the tile is drawn in console
	void moveTileToLastPosition(char direction);
	void repositioningTile(char direction);
	void rotateTile(char direction);
	
	void startGame();
	
	void draw() override;
	void deleteDraw() override;
	
	bool belongsToActualTile(int x, int y) const;
	
	bool checkIfCanMove(char direction) const;
	bool checkIfPlayerLost() const;

public:
	static constexpr int  numberOfColumns{ 11 };
	static constexpr int numberOfLines{ 21 };
	long score;

private:
	std::vector<std::vector<int>> table;					// The game table = a matrix with 0 if there is nothing draw in that point and 1 if there is something draw 
	Tile actualTile;									 // The tile that moves in the game table(the actual tile)
};

#endif // !TABLE_H
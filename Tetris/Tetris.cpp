#include "pch.h"
#include <conio.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define numberOfColumns 11               // number of lines and columns for the game table
#define numberOfLines 21

using namespace std;

class Drawable                          // abstract class that is used to draw different tiles from the game or coordinates
{
protected:
	static short x;
	static short y;
public:
	static int getX();
	static void hidecursor();
	static void MoveTo(short _x, short _y);     // used to move to a specific coordinate in console
	virtual void DeleteDraw() = 0;
	virtual void Draw() = 0;
};

short Drawable::x = 5;                   // represents the coordinates where the game table will be positioning in console
short Drawable::y = 25;

int Drawable::getX()
{
	return x;
}

void Drawable::hidecursor()
{
	CONSOLE_CURSOR_INFO info = { 100,FALSE };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Drawable::MoveTo(short _x, short _y)
{
	COORD coord = { y + _y,x + _x };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class Coordinates: public Drawable                // class that represents one coordinate in console (x,y)
{
private:
	short x;
	short y;
	static char form;                             // the form that every piece(point) from every tile will have
public:
	Coordinates(short x = 0, short y = 0);
	Coordinates& operator =(const Coordinates &coord);
	// getter and setter
	short getX() const;
	short getY() const;
	static char getForm();
	void setX(short x);
	void setY(short y);
	//functions using coordinates(x,y)
	void moveCoordinatesInADirection(char direction);     // used to move the coordinates in a specific direction(right, left, down)
	                                                      // Will be used to move every piece(point) from a tile in a direction
	void DeleteDraw() override;
	void Draw() override;
};

char Coordinates::form = '*';

Coordinates::Coordinates(short x, short y)
{
	this->x = x;
	this->y = y;
}

Coordinates& Coordinates::operator=(const Coordinates &coord)
{
	if (this != &coord)
	{
		this->x = coord.x;
		this->y = coord.y;
		this->form = coord.form;
	}
	return *this;
}

char Coordinates::getForm()
{
	return form;
}

short Coordinates::getX() const
{
	return x;
}

short Coordinates::getY() const
{
	return y;
}

void Coordinates::setX(short x)
{
	this->x = x;
}

void Coordinates::setY(short y)
{
	this->y = y;
}

void Coordinates::moveCoordinatesInADirection(char direction)
{
	switch (direction)
	{
	case 'a':       // move left
		y--;
		break;
	case 'd':       // move right
		y++;
		break;
	case 's':       // move down
		x++;
		break;
	default:
		break;
	}
}

void Coordinates::DeleteDraw()
{
	MoveTo(x + Drawable::x, y + Drawable::y);   // Moves to the coordinates (x,y) and deletes a piece(point) from a tile
	cout << " ";
}

void Coordinates::Draw()
{
	MoveTo(x + Drawable::x, y + Drawable::y);   // Moves to the coordinates (x,y) and draw a piece(point) from a tile
	cout << form;
}


class Tile: public Drawable                     // class that represents a tile and all its methods
{
private:
	Coordinates coordTile[4];                         // any tile is composed of 4 coordinates and a center
	short centerOfTile;
public:
	Tile& operator=(const Tile &tile);
	// getter and setter
	short getcenterOfTile(short position) const;
	short getcoordX(short position) const;
	short getcoordY(short position) const;
	void setcenterOfTile(short centerOfTile);
	void setcoordX(short position, int x);
	void setcoordY(short position, int y);
	//methods using a tile
	void moveTileInADirection(char direction);          // moves the tile in a specific direction(right, left, down)
	void rotateTileInADirection(char direction);       // rotates the tile in a specific direction(right, left)
	void DeleteDraw() override;                       // overrides function DeleteDraw() from Drawable() and is used to delete the tile from the game table
	void Draw() override;                            // overrides function Draw() from Drawable() and is used to draw the tile in the game table
};

Tile& Tile::operator=(const Tile &tile)
{
	if (this != &tile)
	{
		for (short i = 0; i < 4; i++)
		{
			this->coordTile[i] = tile.coordTile[i];
		}
	}
	return *this;
}

short Tile::getcoordX(short position) const
{
	return coordTile[position].getX();
}

short Tile::getcoordY(short position) const
{
	return coordTile[position].getY();
}

short Tile::getcenterOfTile(short position) const
{
	return centerOfTile;
}

void Tile::setcoordX(short position, int x)
{
	coordTile[position].setX(x);
}

void Tile::setcoordY(short position, int y)
{
	coordTile[position].setY(y);
}

void Tile::setcenterOfTile(short centerOfTile)
{
	this->centerOfTile = centerOfTile;
}

void Tile::moveTileInADirection(char direction)
{
	for (short i = 0; i < 4; i++)
	{
		coordTile[i].moveCoordinatesInADirection(direction);
	}
}

void Tile::rotateTileInADirection(char direction)
{
	short dir = 0;

	switch (direction)
	{
	case 'e':           // to rotate the tile to the right we need +90* check formula down
		dir = 1;
		break;
	case 'q':           // to rotate the tile to the left we need -90* check formula down
		dir = -1;
		break;
	default:
		return;
	}

	if (centerOfTile != -1) // If the tile can be rotated
	{
		float centerOfTileX = coordTile[centerOfTile].getX();
		float centerOfTileY = coordTile[centerOfTile].getY();

		float tileX;
		float tileY;

		for (short i = 0; i < 4; i++)  // we rotate every piece(point) from the tile with 90*(to right) or -90*(to left) depends on dir
		{
			tileX = coordTile[i].getX();
			tileY = coordTile[i].getY();
			coordTile[i].setX(round((tileX - centerOfTileX)*cos((90 * 3.14*dir) / 180) + (tileY - centerOfTileY)*sin((90 * 3.14*dir) / 180) + centerOfTileX));
			coordTile[i].setY(round((centerOfTileX - tileX)*sin((90 * 3.14*dir) / 180) + (tileY - centerOfTileY)*cos((90 * 3.14*dir) / 180) + centerOfTileY));
		}
	}
}

void Tile::DeleteDraw()
{
	for (short i = 0; i < 4; i++)
	{
		coordTile[i].DeleteDraw();      // Deleting the tile by deleting every piece(point) of it
	}
}


void Tile::Draw()
{
	for (short i = 0; i < 4; i++)
	{
		coordTile[i].Draw();             // Drawing the tile by drawing every piece(point) of it
	}
}

class Tiles                       // class that represents the number of tiles the game has and all tiles
{
private:
	short numberOfTiles;
	Tile *figuri;
public:
	Tiles();
	Tile getTile(short number) const;
	short getNumberOfTiles() const;
	~Tiles();
};

Tiles::Tiles()
{
	ifstream input("tiles.in");               // reading from a file the number of tiles and than the coordinates of each tile and setting the center for every tile
	input >> numberOfTiles;

	figuri = new Tile[numberOfTiles];
	short auxiliaryVar = 0;
	short counter = 0;

	for (short i = 0; i < numberOfTiles; i++)
	{
		counter = 0;
		for (short j = 0; j < 4; j++)
		{
			for (short k = 0; k < 4; k++)
			{
				input >> auxiliaryVar;
				if (auxiliaryVar != 0)
				{
					figuri[i].setcoordX(counter, j);
					figuri[i].setcoordY(counter, k);
					counter++;
					if ((j == 1) && (k == 2))
					{
						figuri[i].setcenterOfTile(counter - 1);
					}
				}
			}
		}
	}

	figuri[0].setcenterOfTile(2);
	figuri[3].setcenterOfTile(-1);
	input.close();
}

Tile Tiles::getTile(short number) const
{
	return figuri[number];
}

short Tiles::getNumberOfTiles() const
{
	return numberOfTiles;
}

Tiles::~Tiles()
{
	delete[] figuri;
}


class Table: public Drawable           // class that represents the game table 
{
private:
	short **table;            // the game table= a matrix with 0 if there is nothing draw in that point and 1 if there is something draw 
	long score;
	Tile actualTile;         // the tile that moves in the game table(the actual tile)
	Tiles allTiles;         // the actual tile will be chosen random from all the tiles possible

public:
	Table();
	long getScore() const;
	void informationAboutGame() const;
	void generateRandomTile();
	void deleteLineFromTable(short line);        // after a line from the table is completated, it will be deleted from the game table and the score will rise
	void moveTileDownAutomatically();
	void moveTileInADirection(char direction);
	void possibleMoves(short &time);          // possible moves of a player (right, left, down)
	void positioningTileInTableAfterRotation();
	void rotateTileInADirection(char direction);
	void start();
	void DeleteDraw();
	void Draw();
	bool belongsToActualTile(short x, short y) const;
	bool checkIfCanMoveInADirection(char direction) const;
	bool checkIfPlayerLost() const;
	~Table();
};

Table::Table()
{
	// creating the game table and initialize the table

	time_t t;
	srand((unsigned)(time(&t)));

	score = 0;

	table = new short*[numberOfLines];
	for (short i = 0; i < numberOfLines; i++)
	{
		table[i] = new short[numberOfColumns];
	}

	for (short i = 0; i < numberOfLines; i++)
	{
		for (short j = 0; j < numberOfColumns; j++)
		{
			table[i][j] = 0;
		}
	}
}

long Table::getScore() const
{
	return score;
}

void Table::informationAboutGame() const
{
	cout << "\n\n\n\t This is a tetris game.The controls for the game are:\n";
	cout << "\n\t a - move the tile left";
	cout << "\n\t d - move the tile right";
	cout << "\n\t s - move the tile down";
	cout << "\n\t e - rotate the tile right";
	cout << "\n\t q - rotate the tile left";
	cout << "\n\n\t When you are ready, press any key to start the game. Good luck ! ";
	_getch();
}

void Table::generateRandomTile()
{
	// generating a random tile from all the tiles possible and setting its coordinates for the game table

	short randomTile;
	randomTile = rand() % allTiles.getNumberOfTiles();

	actualTile = allTiles.getTile(randomTile);
	actualTile.setcenterOfTile(allTiles.getTile(randomTile).getcenterOfTile(randomTile));

	for (short i = 0; i < 4; i++)
	{
		actualTile.setcoordY(i, numberOfColumns / 2 - actualTile.getcoordY(i) + 2);
	}
}

void Table::deleteLineFromTable(short line) 
{
	// Deleting the line which is completed
	// This is done by replacing every line starting that line by the previous one
	for (short i = line; i > 0; i--)
	{
		for (short j = 0; j < numberOfColumns; j++)
		{
			Drawable::MoveTo(i + Drawable::x, j + Drawable::y);
			if (table[i - 1][j] == 0)
			{
				cout << " ";
			}
			else {
				cout << Coordinates::getForm();
			}

			table[i][j] = table[i - 1][j];
		}
	}

	for (short i = 0; i < numberOfColumns; i++)
	{
		Drawable::MoveTo(0 + Drawable::x, i + Drawable::y);
		cout << " ";
		table[0][i] = 0;
	}
}

void Table::moveTileDownAutomatically()
{
	//Moving the actual tile down every 0.5s and checking if the player wants to make a move(right, left, down) or rotate(right, left) the tile
	actualTile.Draw();

	do {
		short time = 1;

		while (time < 500)
		{
			if (_kbhit())             // if the player presses a key on keyboard
			{
				possibleMoves(time);
			}

			Sleep(1);
			time = time + 1;
		}

		if (checkIfCanMoveInADirection('s'))
		{
			actualTile.DeleteDraw();
			moveTileInADirection('s');
			actualTile.Draw();
		}
		else {
			break;
		}
	} while (true); 
}

void Table::moveTileInADirection(char direction)
{
	// To move the tile in a direction we need to :
	// - delete the previous tile from the game table by putting 0
	// - move the tile to the new coordinates
	// - actualizate the game table by putting 1 on its coordinates 
	for (short i = 0; i < 4; i++)
	{
		table[actualTile.getcoordX(i)][actualTile.getcoordY(i)] = 0;
	}

	actualTile.moveTileInADirection(direction);

	for (short i = 0; i < 4; i++)
	{
		table[actualTile.getcoordX(i)][actualTile.getcoordY(i)] = 1;
	}
}

void Table::possibleMoves(short &time)
{
	//Possible moves that can be effectuated on a tile ( move and rotate )
	char direction = _getch();
	
	if (checkIfCanMoveInADirection(direction))
	{
		actualTile.DeleteDraw();                  // delete old tile
		moveTileInADirection(direction);          // move the tile in the direction the player wanted
		actualTile.Draw();                        // draw the new tile
		if (direction == 's')
		{
			time = 1;
		}
	}
	// check if the player wanted to rotate the tile (right, left)
	if ((direction == 'e') || (direction == 'q'))
	{
		actualTile.DeleteDraw();
		rotateTileInADirection(direction);
		actualTile.Draw();
	}
}

void Table::positioningTileInTableAfterRotation()
{
	// This method is used to check and correct a tile if it goes out of boundaries of the game table after a rotation
	short index = 0;
	short ok = 1;

	while (index < 4)
	{
		if (actualTile.getcoordY(index) < 0)
		{
			// passed left boundary of the game table
			for (short j = 0; j < 4; j++)
			{
				actualTile.setcoordY(j, actualTile.getcoordY(j) + 1);
			}
			ok = 0;
		}

		if (actualTile.getcoordY(index) > numberOfColumns - 1)
		{
			// passed right boundary of the game table
			for (short j = 0; j < 4; j++)
			{
				actualTile.setcoordY(j, actualTile.getcoordY(j) - 1);
			}
			ok = 0;
		}

		if (actualTile.getcoordX(index) < 0)
		{
			// passed top boundary of the game table and there are cases where the player loses
			for (short j = 0; j < 4; j++)
			{
				actualTile.setcoordX(j, actualTile.getcoordX(j) + 1);
			}

			for (short j = 0; j < 4; j++)
			{
				if ((actualTile.getcoordX(j) > 0) && (table[actualTile.getcoordX(j)][actualTile.getcoordY(j)] == 1))
				{
					throw 0;
				}
			}
			ok = 0;
		}

		if ((actualTile.getcoordX(index) > numberOfLines - 1) ||
			(table[actualTile.getcoordX(index)][actualTile.getcoordY(index)] == 1))
		{
			// passed the down boundary or reached a possition that is occupied
			for (short j = 0; j < 4; j++)
			{
				actualTile.setcoordX(j, actualTile.getcoordX(j) - 1);
			}
			ok = 0;
		}

		if (ok == 0)
		{
			index = 0;
			ok = 1;
		}
		else {
			index++;
		}
	}
}

void Table::rotateTileInADirection(char direction)
{
	// To rotate the tile in a direction we need to :
	// - delete the previous tile from the game table by putting 0
	// - move the tile to the new coordinates and adjust it so it doesnt pass the boundaries of the game table
	// - actualizate the game table by putting 1 on its coordinates
	for (short i = 0; i < 4; i++)
	{
		table[actualTile.getcoordX(i)][actualTile.getcoordY(i)] = 0;
	}

	actualTile.rotateTileInADirection(direction);
	positioningTileInTableAfterRotation();

	for (short i = 0; i < 4; i++)
	{
		table[actualTile.getcoordX(i)][actualTile.getcoordY(i)] = 1;
	}
}

void Table::start()
{
	Drawable::hidecursor();
	informationAboutGame();

	DeleteDraw();
	Draw();

	short ok = 1;

	while (true)
	{
		// This while will end when the player will lose and the program will end
		// checking if there is any line completed and needs to be deleted
		for (short i = 0; i < numberOfLines; i++)
		{
			ok = 1;

			for (short j = 0; j < numberOfColumns; j++)
			{
				if (table[i][j] == 0)
				{
					ok = 0;
					break;
				}
			}
			if (ok)
			{
				deleteLineFromTable(i);
				score++;
			}
		}

		generateRandomTile();

		if (checkIfPlayerLost() == 1)
		{
			moveTileDownAutomatically();
		}
		else {
			Drawable::MoveTo(numberOfLines + 1 + Drawable::x, 0);
			cout << "\n" << "Good job, you made " << score * 1000 << " points.\n";
			break;
		}
	}
}

void Table::DeleteDraw()
{
	// Method used to delete the table
	system("cls");
}

void Table::Draw()
{
	// Method used to draw the table 
	for (short i = -1; i <= numberOfLines; i++)
	{
		MoveTo(i + Drawable::x, -1 + Drawable::y);
		cout << char(219);
		MoveTo(i + Drawable::x, numberOfColumns + Drawable::y);
		cout << char(219);
	}
	for (short i = -1; i <= numberOfColumns; i++)
	{
		Drawable::MoveTo(-1 + Drawable::x, i + Drawable::y);
		cout << char(219);
		Drawable::MoveTo(numberOfLines + Drawable::x, i + Drawable::y);
		cout << char(219);
	}
}

bool Table::belongsToActualTile(short x, short y) const
{
	//Checking if a piece(point) of a tile belonds to the actual tile
	for (short i = 0; i < 4; i++)
	{
		if ((actualTile.getcoordX(i) == x) && (actualTile.getcoordY(i) == y))
		{
			return 0;
		}
	}

	return 1;
}

bool Table::checkIfCanMoveInADirection(char direction) const
{
	for (short i = 0; i < 4; i++)
	{
		switch (direction)
		{
			// Check if the player can move left
		case'a':
			if ((actualTile.getcoordY(i) - 1 < 0) ||
				((belongsToActualTile(actualTile.getcoordX(i), actualTile.getcoordY(i) - 1)) &&
				(table[actualTile.getcoordX(i)][actualTile.getcoordY(i) - 1] == 1)))
			{
				return 0;
			}
			break;
			// Check if the player can move right
		case'd':
			if ((actualTile.getcoordY(i) + 1 > numberOfColumns - 1) ||
				((belongsToActualTile(actualTile.getcoordX(i), actualTile.getcoordY(i) + 1)) &&
				(table[actualTile.getcoordX(i)][actualTile.getcoordY(i) + 1] == 1)))
			{
				return 0;
			}
			break;
			// Check if the player can move down
		case's':
			if ((actualTile.getcoordX(i) + 1 > numberOfLines - 1) ||
				((belongsToActualTile(actualTile.getcoordX(i) + 1, actualTile.getcoordY(i))) &&
				(table[actualTile.getcoordX(i) + 1][actualTile.getcoordY(i)] == 1)))
			{
				return 0;
			}
			break;
		default:
			break;
		}
	}
	return 1;
}

bool Table::checkIfPlayerLost() const
{
	for (short i = 0; i < 4; i++)
	{
		if (table[actualTile.getcoordX(i)][actualTile.getcoordY(i)] == 1)
		{
			return 0;
		}
	}

	return 1;
}

Table::~Table() 
{
	for (short i = 0; i < numberOfLines; i++)
	{
		delete[] table[i];
	}
	delete[] table;
}

int main() 
{
	Table a;
	try {
		a.start();
	}
	catch (...) {
		Drawable::MoveTo(numberOfLines + 1 + Drawable::getX(), 0);
		cout << "\n" << "Good job, you made " << a.getScore() * 1000 << " points.\n";
	}

	return 0;
}
#include "Table.h"

Table::Table()
{
	score = 0;
	speedOfTiles = 500;

	for (int currentLine = 0; currentLine < numberOfLines; currentLine++)
	{
		for (int currentColumn = 0; currentColumn < numberOfColumns; currentColumn++)
		{
			table[currentLine][currentColumn] = 0;
		}
	}
}

long Table::getScore()
{
	return score;
}

void Table::informationAboutGame()
{
	cout << "\n\n\n\t This is a tetris game.The controls for the game are:\n";
	cout << "\n\t a - move the tile left";
	cout << "\n\t d - move the tile right";
	cout << "\n\t s - move the tile down";
	cout << "\n\t e - rotate the tile right";
	cout << "\n\t q - rotate the tile left";
	cout << "\n\n\t When you are ready, press any key to start the game. Good luck ! ";
	(void)_getch();
}

void Table::generateRandomTile()
{
	// generating a random tile from all the tiles possible and setting its coordinates for the game table

	int randomTile;
	random_device random;
	uniform_int_distribution<int>dist(0, allTiles.getNumberOfTiles() - 1);

	randomTile = dist(random);

	actualTile = allTiles.getTile(randomTile);
	actualTile.setcenterOfTile(allTiles.getTile(randomTile).getcenterOfTile(randomTile));

	for (int i = 0; i < 4; i++)
	{
		actualTile.setcoordY(i, numberOfColumns / 2 - actualTile.getcoordY(i) + 2);
	}
}

void Table::deleteLineFromTable(int line)
{
	// Deleting the line which is completed
	// This is done by replacing every line starting that line by the previous one
	for (int currentLine = line; currentLine > 0; currentLine--)
	{
		for (int currentColumn = 0; currentColumn < numberOfColumns; currentColumn++)
		{
			Drawable::MoveTo(currentLine + Drawable::startPositionX, currentColumn + Drawable::startPositionY);
			if (table[currentLine - 1][currentColumn] == 0)
			{
				cout << " ";
			}
			else {
				cout << Coordinates::getForm();
			}

			table[currentLine][currentColumn] = table[currentLine - 1][currentColumn];
		}
	}

	for (int currentColumn = 0; currentColumn < numberOfColumns; currentColumn++)
	{
		Drawable::MoveTo(0 + Drawable::startPositionX, currentColumn + Drawable::startPositionY);
		cout << " ";
		table[0][currentColumn] = 0;
	}
}

void Table::moveTileDownAutomatically()
{
	//Moving the actual tile down every 0.5s and checking if the player wants to make a move(right, left, down) or rotate(right, left) the tile
	actualTile.Draw();

	int counterTime = 1;

	do {
		counterTime = 1;

		while (counterTime < speedOfTiles)
		{
			if (_kbhit())             // if the player presses a key on keyboard
			{
				possibleMoves(counterTime);
			}

			Sleep(1);
			counterTime = counterTime + 1;
		}

		if (checkIfCanMoveInADirection(Action::moveDOWN))
		{
			actualTile.DeleteDraw();
			moveTileInADirection(Action::moveDOWN);
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
	for (int i = 0; i < 4; i++)
	{
		table[actualTile.getcoordX(i)][actualTile.getcoordY(i)] = 0;
	}

	actualTile.moveTileInADirection(direction);

	for (int i = 0; i < 4; i++)
	{
		table[actualTile.getcoordX(i)][actualTile.getcoordY(i)] = 1;
	}
}

void Table::possibleMoves(int &counterTime)
{
	//Possible moves that can be effectuated on a tile ( move and rotate )
	char direction = _getch();

	if (checkIfCanMoveInADirection(direction))
	{
		actualTile.DeleteDraw();                  // delete old tile
		moveTileInADirection(direction);          // move the tile in the direction the player wanted
		actualTile.Draw();                        // draw the new tile
		if (direction == Action::moveDOWN)
		{
			counterTime = 1;
		}
	}
	// check if the player wanted to rotate the tile (right, left)
	if ((direction == Action::rotateRIGHT) || (direction == Action::rotateLEFT))
	{
		actualTile.DeleteDraw();
		rotateTileInADirection(direction);
		actualTile.Draw();
	}
}

void Table::positioningTileInTableAfterRotation()
{
	// This method is used to check and correct a tile if it goes out of boundaries of the game table after a rotation
	int index = 0;
	int ok = 1;

	while (index < 4)
	{
		if (actualTile.getcoordY(index) < 0)
		{
			// passed left boundary of the game table
			for (int j = 0; j < 4; j++)
			{
				actualTile.setcoordY(j, actualTile.getcoordY(j) + 1);
			}
			ok = 0;
		}

		if (actualTile.getcoordY(index) > numberOfColumns - 1)
		{
			// passed right boundary of the game table
			for (int j = 0; j < 4; j++)
			{
				actualTile.setcoordY(j, actualTile.getcoordY(j) - 1);
			}
			ok = 0;
		}

		if (actualTile.getcoordX(index) < 0)
		{
			// passed top boundary of the game table and there are cases where the player loses
			for (int j = 0; j < 4; j++)
			{
				actualTile.setcoordX(j, actualTile.getcoordX(j) + 1);
			}

			for (int j = 0; j < 4; j++)
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
			for (int j = 0; j < 4; j++)
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
	for (int i = 0; i < 4; i++)
	{
		table[actualTile.getcoordX(i)][actualTile.getcoordY(i)] = 0;
	}

	actualTile.rotateTileInADirection(direction);
	positioningTileInTableAfterRotation();

	for (int i = 0; i < 4; i++)
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

	int ok = 1;
	int numberOfTilesPlayed = 20;
	int counterNumberOfTilesPlayed = 0;

	while (true)
	{
		// This while will end when the player will lose and the program will end
		// checking if there is any line completed and needs to be deleted
		for (int currentLine = 0; currentLine < numberOfLines; currentLine++)
		{
			ok = 1;

			for (int currentColumn = 0; currentColumn < numberOfColumns; currentColumn++)
			{
				if (table[currentLine][currentColumn] == 0)
				{
					ok = 0;
					break;
				}
			}
			if (ok)
			{
				deleteLineFromTable(currentLine);
				score++;
			}
		}

		generateRandomTile();

		if (checkIfPlayerLost() == false)
		{
			moveTileDownAutomatically();
			counterNumberOfTilesPlayed++;
			if (counterNumberOfTilesPlayed == numberOfTilesPlayed)
			{
				speedOfTiles = speedOfTiles - 400;
			}
		}
		else {
			Drawable::MoveTo(numberOfLines + 1 + Drawable::startPositionX, 0);
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
	for (int index = -1; index <= numberOfLines; index++)
	{
		MoveTo(Drawable::startPositionX + index, Drawable::startPositionY - 1);
		cout << char(219);
		MoveTo(Drawable::startPositionX + index, Drawable::startPositionY + numberOfColumns);
		cout << char(219);
	}

	for (int index = -1; index <= numberOfColumns; index++)
	{
		Drawable::MoveTo(Drawable::startPositionX - 1, Drawable::startPositionY + index);
		cout << char(219);
		Drawable::MoveTo(Drawable::startPositionX + numberOfLines, Drawable::startPositionY + index);
		cout << char(219);
	}
}

bool Table::belongsToActualTile(int x, int y)
{
	//Checking if a piece(point/coordinate) of a tile belonds to the actual tile
	for (int currentCoordinate = 0; currentCoordinate < 4; currentCoordinate++)
	{
		if ((actualTile.getcoordX(currentCoordinate) == x) && (actualTile.getcoordY(currentCoordinate) == y))
		{
			return 0;
		}
	}

	return 1;
}

bool Table::checkIfCanMoveInADirection(char direction)
{
	for (int i = 0; i < 4; i++)
	{
		switch (direction)
		{
			// Check if the player can move left
		case Action::moveLEFT:
			if ((actualTile.getcoordY(i) - 1 < 0) ||
				((belongsToActualTile(actualTile.getcoordX(i), actualTile.getcoordY(i) - 1)) &&
				(table[actualTile.getcoordX(i)][actualTile.getcoordY(i) - 1] == 1)))
			{
				return 0;
			}
			break;
			// Check if the player can move right
		case Action::moveRIGHT:
			if ((actualTile.getcoordY(i) + 1 > numberOfColumns - 1) ||
				((belongsToActualTile(actualTile.getcoordX(i), actualTile.getcoordY(i) + 1)) &&
				(table[actualTile.getcoordX(i)][actualTile.getcoordY(i) + 1] == 1)))
			{
				return 0;
			}
			break;
			// Check if the player can move down
		case Action::moveDOWN:
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

bool Table::checkIfPlayerLost()
{
	for (int currentCoordinate = 0; currentCoordinate < 4; currentCoordinate++)
	{
		if (table[actualTile.getcoordX(currentCoordinate)][actualTile.getcoordY(currentCoordinate)] == 1)
		{
			return true;
		}
	}

	return false;
}

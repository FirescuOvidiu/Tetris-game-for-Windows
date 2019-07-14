#pragma once

#ifndef DIFFICULTY_H
#define DIFFICULTY_H

namespace Difficulty
{
	int incSpeedAfterXTilesPlayed{ 20 };
	int speedOfTiles{ 600 };

	void setDifficulty(char numberOfDifficulty)
	{
		switch (numberOfDifficulty)
		{
			//Easy
		case '1':
			incSpeedAfterXTilesPlayed = 20;
			speedOfTiles = 600;
			break;
			//Normal
		case '2':
			incSpeedAfterXTilesPlayed = 15;
			speedOfTiles = 400;
			break;
			//Hard
		case '3':
			incSpeedAfterXTilesPlayed = 10;
			speedOfTiles = 200;
			break;
			//Impossible
		case '4':
			incSpeedAfterXTilesPlayed = 5;
			speedOfTiles = 100;
			break;
		}
	}

	void increaseSpeed(int& tilesPlayed)
	{
		if ((tilesPlayed == Difficulty::incSpeedAfterXTilesPlayed)
			&& (Difficulty::speedOfTiles > 20))
		{

			Difficulty::speedOfTiles = Difficulty::speedOfTiles - 20;
			tilesPlayed = 0;
		}
	}
}

#endif // !DIFFICULTY_H

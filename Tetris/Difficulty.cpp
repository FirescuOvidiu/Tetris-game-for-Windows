#include "Difficulty.h"

int Difficulty::increaseSpeedAfterXTilesPlayed = 20;
int Difficulty::speedOfTiles = 600;

void Difficulty::setDifficulty(char numberOfDifficulty)
{
	switch (numberOfDifficulty)
	{
	//Easy
	case '1':
		increaseSpeedAfterXTilesPlayed = 20;
		speedOfTiles = 600;
		break;
	//Normal
	case '2':
		increaseSpeedAfterXTilesPlayed = 15;
		speedOfTiles = 400;
		break;
	//Hard
	case '3':
		increaseSpeedAfterXTilesPlayed = 10;
		speedOfTiles = 200;
		break;
	//Impossible
	case '4':
		increaseSpeedAfterXTilesPlayed = 5;
		speedOfTiles = 100;
		break;
	}
}

void Difficulty::increaseSpeedafterXTiles(int& counterNumberOfTilesPlayed)
{
	if ((counterNumberOfTilesPlayed == Difficulty::increaseSpeedAfterXTilesPlayed)
		&& (Difficulty::speedOfTiles > 20))
	{

		Difficulty::speedOfTiles = Difficulty::speedOfTiles - 20;
		counterNumberOfTilesPlayed = 0;
	}
}

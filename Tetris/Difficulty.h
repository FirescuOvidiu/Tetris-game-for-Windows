#pragma once

#ifndef DIFFICULTY_H
#define DEFFICULTY_H

class Difficulty
{
public:
	static int increaseSpeedAfterXTilesPlayed;
	static int speedOfTiles;

public:
	static void setDifficulty(char numberOfDifficulty);
};
#endif // !DIFFICULTY_H

#pragma once

#ifndef ACTIONS_H
#define ACTIONS_H

class Action
{
public:
	static constexpr char moveLEFT{ 'a' };
	static constexpr char moveRIGHT{ 'd' };
	static constexpr char moveDOWN{ 's' };
	static constexpr char rotateLEFT{ 'q' };
	static constexpr char rotateRIGHT{ 'e' };
};

#endif // !ACTIONS_H

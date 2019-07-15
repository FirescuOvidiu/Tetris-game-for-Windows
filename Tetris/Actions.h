#pragma once

#ifndef ACTIONS_H
#define ACTIONS_H


// Possible actions that a player can do
namespace tetris
{
	namespace Action
	{
		static constexpr char moveLEFT{ 'a' };
		static constexpr char moveRIGHT{ 'd' };
		static constexpr char moveDOWN{ 's' };
		static constexpr char rotateLEFT{ 'q' };
		static constexpr char rotateRIGHT{ 'e' };
	}
}

#endif // !ACTIONS_H

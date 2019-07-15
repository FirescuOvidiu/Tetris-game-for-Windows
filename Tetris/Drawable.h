#pragma once

#ifndef DRAWABLE_H
#define DRAWABLE_H

namespace tetris
{
	class Drawable
	{
	public:
		static int getstartX();

		static void hideCursor();
		static void MoveTo(int x, int y);

		virtual void draw() = 0;
		virtual void deleteDraw() = 0;

	protected:
		// The position where the table game will be displayed in console
		static constexpr int startX{ 10 };
		static constexpr int startY{ 25 };
	};
}
#endif // !DRAWABLE_H
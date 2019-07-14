#include "Drawable.h"
#include "Table.h"
#include <iostream>

int main()
{
	Table a;

	try {
		a.startGame();
	}
	catch (...) 
	{
		// In case player loses
		Drawable::MoveTo(Drawable::getstartPositionX() + Table::numberOfLines + 1, 0);
		std::cout << "\n" << "Good job, you made " << a.score * 1000 << " points.\n";
	}
}
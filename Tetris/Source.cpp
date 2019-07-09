#include "Table.h"

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
		cout << "\n" << "Good job, you made " << a.score * 1000 << " points.\n";
	}
}
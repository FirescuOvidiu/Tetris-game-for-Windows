#include "Table.h"

int main()
{
	Table a;

	try {
		a.start();
	}
	catch (...) 
	{
		Drawable::MoveTo(Drawable::getstartPositionX() + Table::numberOfLines + 1, 0);
		cout << "\n" << "Good job, you made " << a.getScore() * 1000 << " points.\n";
	}
}
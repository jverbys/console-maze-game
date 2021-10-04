#ifndef _MOLECULE_
#define _MOLECULE_

#include <utility>

class Molecule
{
protected:
	int x;
	int y;
	char renderChar;

public:
	Molecule(int _x, int _y, char _rChar);
	char getRenderChar();
	std::pair<int, int> getPos();
};

#endif // !_MOLECULE_

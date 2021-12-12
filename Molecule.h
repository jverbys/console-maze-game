#ifndef _MOLECULE_
#define _MOLECULE_

#include <utility>

class Molecule
{
protected:
	std::pair<int, int> pos;
	char renderChar;

public:
	Molecule(int _x, int _y, char _rChar);
	char getRenderChar();
	std::pair<int, int> getPos();
};

#endif // !_MOLECULE_

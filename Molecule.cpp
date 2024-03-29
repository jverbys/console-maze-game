#include <utility>

#include "Molecule.h"

Molecule::Molecule(int _x, int _y, char _rChar)
{
	this->pos = {_x, _y};
	this->renderChar = _rChar;
}

char Molecule::getRenderChar()
{
	return this->renderChar;
}

std::pair<int, int> Molecule::getPos()
{
	return this->pos;
}
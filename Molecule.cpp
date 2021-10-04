#include <utility>

#include "Molecule.h"

Molecule::Molecule(int _x, int _y, char _rChar)
{
	this->x = _x;
	this->y = _y;
	this->renderChar = _rChar;
}

char Molecule::getRenderChar()
{
	return this->renderChar;
}

std::pair<int, int> Molecule::getPos()
{
	return { this->x, this->y };
}
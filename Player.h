#ifndef _PLAYER_
#define _PLAYER_

#include <utility>

#include "Molecule.h"

class Player : public Molecule
{
public:
	Player(int _x, int _y, char _rChar) : Molecule(_x, _y, _rChar)
	{
		this->newX = _x;
		this->newY = _y;
	};
	void changePos(std::pair<int, int> _coords);
	void setNewPos(std::pair<int, int> _coords);
	std::pair<int, int> getNewPos();

private:
	int newX;
	int newY;
};

#endif // !_PLAYER_

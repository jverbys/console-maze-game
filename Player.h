#ifndef _PLAYER_
#define _PLAYER_

#include <utility>

#include "Molecule.h"

class Player : public Molecule
{
public:
	Player(int _x, int _y, char _rChar) : Molecule(_x, _y, _rChar)
	{
		this->newPos = { _x, _y };
	};
	void changePos(std::pair<int, int> _coords);
	void setNewMapPos(std::pair<int, int> _coords);
	std::pair<int, int> getNewPos();

private:
	std::pair<int, int> newPos;
};

#endif // !_PLAYER_

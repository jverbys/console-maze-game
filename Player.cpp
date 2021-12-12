#include <utility>

#include "Player.h"

void Player::changePos(std::pair<int, int> _coords)
{
	this->pos = this->newPos;

	this->newPos = _coords;
}

void Player::setNewMapPos(std::pair<int, int> _coords)
{
	this->pos = _coords;

	this->newPos = _coords;
}

std::pair<int, int> Player::getNewPos()
{
	return this->newPos;
}
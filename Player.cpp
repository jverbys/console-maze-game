#include <utility>

#include "Player.h"

void Player::changePos(std::pair<int, int> _coords)
{
	this->pos = { this->newX, this->newY };

	this->newX = _coords.first;
	this->newY = _coords.second;
}

void Player::setNewPos(std::pair<int, int> _coords)
{
	this->pos = { _coords.first, _coords.second };

	this->newX = _coords.first;
	this->newY = _coords.second;
}

std::pair<int, int> Player::getNewPos()
{
	return { this->newX, this->newY };
}
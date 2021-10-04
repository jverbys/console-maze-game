#ifndef _GAME_
#define _GAME_

#include <utility>
#include <vector>
#include <Windows.h>

#include "Player.h"

class Game
{
public:
	Game(int _mazeWidth, int _mazeHeight);
	void initialize();

private:
	int mazeWidth;
	int mazeHeight;
	std::vector<std::vector<int>> map;
	std::pair<int, int> randPos;
	enum 
	{
		WALL = 0,
		MAZE_END = 3
	};
	void setMap();
	void renderMap(Player& _player);
	void computeNewPos();
	void getInput(Player& _player);
	bool canMove(std::pair<int, int> _coords);
	void rerenderMap(Player _player);
	void addExit();
	bool canExit(std::pair<int, int> _coords);
	void nextLevel(Player& _player);
	void resetMap();
};

#endif // !_GAME_


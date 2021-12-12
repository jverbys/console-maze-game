#ifndef _MAZE_
#define _MAZE_

#include <vector>

class Maze
{
public:
	Maze(int _width, int _height);
	void generate(int _width, int _height);
	void regenerate(int _width, int _height);
	int getPosState(int _x, int _y);

private:
	std::vector<std::vector<int>> map;
};

#endif // !_MAZE_

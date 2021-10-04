#include <time.h>
#include <vector>
#include <array>

#include "Maze.h"

Maze::Maze(int _width, int _height)
{
    this->generate(_width, _height);
}

void Maze::generate(int _width, int _height)
{
    srand(time(NULL));

    enum {
        WALL = 0,
        PASSAGE = 1
    };

    for (int i = 0; i < _width; i++)
    {
        std::vector<int> row;
        for (int j = 0; j < _height; j++)
        {
            row.push_back(WALL);
        }
        this->map.push_back(row);
    }

    std::vector<std::array<int, 4>> frontiers;

    int x = rand() % _width;
    int y = rand() % _height;

    frontiers.push_back({ x,y,x,y });

    while (!frontiers.empty())
    {
        int randF = rand() % frontiers.size();
        std::array<int, 4> f = frontiers[randF];
        frontiers.erase(frontiers.begin() + randF);

        x = f[2];
        y = f[3];

        if (this->map[x][y] == WALL)
        {
            this->map[f[0]][f[1]] = this->map[x][y] = PASSAGE;
            if (x >= 2 && this->map[x - 2][y] == WALL)
                frontiers.push_back({ x - 1, y, x - 2, y });
            if (y >= 2 && this->map[x][y - 2] == WALL)
                frontiers.push_back({ x, y - 1, x, y - 2 });
            if (x < _width - 2 && this->map[x + 2][y] == WALL)
                frontiers.push_back({ x + 1, y, x + 2, y });
            if (y < _height - 2 && this->map[x][y + 2] == WALL)
                frontiers.push_back({ x, y + 1, x, y + 2 });
        }
    }
}

void Maze::regenerate(int _width, int _height)
{
    this->map.clear();

    this->generate(_width, _height);
}
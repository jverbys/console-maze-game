#include <iostream>
#include <utility>
#include <vector>
#include <Windows.h>

#include "Game.h"
#include "Maze.h"
#include "Player.h"

Game::Game(int _width, int _height)
{
	this->mazeWidth = _width;
	this->mazeHeight = _height;
}

void Game::initialize()
{
    this->setMap();

    this->computeNewPos();

    Player player(this->randPos.first, this->randPos.second, '$');

    this->addExit();

    this->renderMap(player);

    while (true)
    {
        this->getInput(player);
    }
}

void Game::setMap()
{
    Maze maze(this->mazeWidth, this->mazeHeight);

    std::vector<int> row;

    for (int x = 0; x < this->mazeWidth; x++)
    {
        for (int y = 0; y < this->mazeHeight; y++)
        {
            row.push_back(maze.map[x][y]);
        }
        this->map.push_back(row);
        row.clear();
    }
}

void Game::renderMap(Player& _player)
{
    for (int x = 0; x < this->mazeWidth; x++)
    {
        for (int y = 0; y < this->mazeHeight; y++)
        {
            if (this->map[x][y] == WALL)
                std::cout << "@";
            else if (x == _player.getPos().first && y == _player.getPos().second)
                std::cout << _player.getRenderChar();
            else if (this->map[x][y] == MAZE_END)
                std::cout << "E";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void Game::computeNewPos()
{
    std::vector<std::pair<int, int>> freePositions;

    for (int x = 0; x < this->mazeWidth; x++)
    {
        for (int y = 0; y < this->mazeHeight; y++)
        {
            if (this->map[x][y] == 1)
                freePositions.push_back({ x, y });
        }
    }

    int randIndex = rand() % freePositions.size();

    this->randPos = { freePositions[randIndex].first, freePositions[randIndex].second };
}

void Game::getInput(Player &_player)
{
    Sleep(75);
    if (GetKeyState('W') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
    {
        std::pair<int, int> newCoords = { _player.getNewPos().first - 1, _player.getNewPos().second };

        if (this->canMove(newCoords))
        {
            _player.changePos(newCoords);
            this->rerenderMap(_player);
            
            if (this->canExit(newCoords))
                this->nextLevel(_player);
        }
    }
    if (GetKeyState('A') & 0x8000)
    {
        std::pair<int, int> newCoords = { _player.getNewPos().first, _player.getNewPos().second - 1 };

        if (this->canMove(newCoords))
        {
            _player.changePos(newCoords);
            this->rerenderMap(_player);

            if (this->canExit(newCoords))
                this->nextLevel(_player);
        }
    }
    if (GetKeyState('S') & 0x8000)
    {
        std::pair<int, int> newCoords = { _player.getNewPos().first + 1 , _player.getNewPos().second };

        if (this->canMove(newCoords))
        {
            _player.changePos(newCoords);
            this->rerenderMap(_player);

            if (this->canExit(newCoords))
                this->nextLevel(_player);
        }
    }
    if (GetKeyState('D') & 0x8000)
    {
        std::pair<int, int> newCoords = { _player.getNewPos().first , _player.getNewPos().second + 1 };

        if (this->canMove(newCoords))
        {
            _player.changePos(newCoords);
            this->rerenderMap(_player);

            if (this->canExit(newCoords))
                this->nextLevel(_player);
        }
    }
}

bool Game::canMove(std::pair<int, int> _coords)
{
    int x = _coords.first;
    int y = _coords.second;

    if (x < 0)
        return false;
    if (x == this->mazeWidth)
        return false;
    if (y < 0)
        return false;
    if (y == this->mazeHeight)
        return false;
    if (this->map[x][y] == WALL)
        return false;

    return true;
}

void Game::rerenderMap(Player _player)
{
    COORD coord;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int x = 0; x < this->mazeWidth; x++)
    {
        for (int y = 0; y < this->mazeHeight; y++)
        {
            if (x == _player.getPos().first && y == _player.getPos().second)
            {
                coord.X = y;
                coord.Y = x;
                SetConsoleCursorPosition(hConsole, coord);

                std::cout << " ";
            }
            if (x == _player.getNewPos().first && y == _player.getNewPos().second)
            {
                coord.X = y;
                coord.Y = x;
                SetConsoleCursorPosition(hConsole, coord);

                std::cout << _player.getRenderChar();
            }
        }
    }
}

void Game::addExit()
{
    this->computeNewPos();

    for (int x = 0; x < this->mazeWidth; x++)
    {
        for (int y = 0; y < this->mazeHeight; y++)
        {
            if (x == this->randPos.first && y == this->randPos.second)
                this->map[x][y] = MAZE_END;
        }
    }
}

bool Game::canExit(std::pair<int, int> _coords)
{
    if (this->map[_coords.first][_coords.second] == MAZE_END)
        return true;

    return false;
}

void Game::nextLevel(Player& _player)
{
    this->mazeWidth += 2;
    this->mazeHeight += 4;

    this->resetMap();

    this->setMap();

    this->computeNewPos();
    _player.setNewPos(this->randPos);

    this->addExit();

    this->renderMap(_player);

    Sleep(500);
}

void Game::resetMap()
{
    this->map.clear();
    system("cls");
}
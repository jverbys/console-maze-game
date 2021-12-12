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
    // Naudojamas Randomized Prim's Algorithm

    srand(time(NULL));

    enum {
        WALL = 0,
        PASSAGE = 1
    };

    // labirintas pradedamas nuo tokio, kurio visi langeliai yra sienos
    for (int i = 0; i < _width; i++)
    {
        std::vector<int> row;
        for (int j = 0; j < _height; j++)
        {
            row.push_back(WALL);
        }
        this->map.push_back(row);
    }

    // Masyvas skirtas laikyti langelius kurie gali buti padaryti praeinamais.
    // Tai is pradziu bus atsitikinai parinktas langelis ir per pacia pirma iteracija
    // jis bus paverstas praeinamu ir prideti kiti langeliai aplink ji, kurie yra
    // per daugiau nei 1 langeli nuo jo i visas keturias puses.
    // Toliau bus taip pat dirbama su turimais 4 langeliais ir daugiau.
    std::vector<std::array<int, 4>> frontiers;

    // pasirenkam random pozicija pirmam laisvam langeliui
    int x = rand() % _width;
    int y = rand() % _height;

    // Saugosim dviguba pozicija, nes labirintas daromas juostelemis po 2 langelius
    // Pradedama nuo vieno langelio
    frontiers.push_back({ x,y,x,y });

    while (!frontiers.empty())
    {
        // Pasirenkam atsitiktini langeli is langeliu su kuriais bus dirbama
        int randF = rand() % frontiers.size();

        // Issisaugom ta langeli i atskira masyva
        std::array<int, 4> f = frontiers[randF];

        // Istrinam ta langeli is bendrom masyvo
        frontiers.erase(frontiers.begin() + randF);

        x = f[2];
        y = f[3];

        if (this->map[x][y] == WALL)
        {
            this->map[f[0]][f[1]] = this->map[x][y] = PASSAGE;

            // jei nekertamas kairys krastas
            if (x >= 2 && this->map[x - 2][y] == WALL)
                frontiers.push_back({ x - 1, y, x - 2, y });

            // jei nekertamas virsutinis krastas
            if (y >= 2 && this->map[x][y - 2] == WALL)
                frontiers.push_back({ x, y - 1, x, y - 2 });

            // jei nekertamas desinys krastas
            if (x < _width - 2 && this->map[x + 2][y] == WALL)
                frontiers.push_back({ x + 1, y, x + 2, y });

            // jei nekertamas apatinis krastas
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

int Maze::getPosState(int _x, int _y)
{
    return this->map[_x][_y];
}
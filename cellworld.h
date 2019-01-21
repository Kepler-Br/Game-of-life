#ifndef CELLWORLD_H
#define CELLWORLD_H

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include "cell.h"

class CellHash
{
public:
    size_t operator()(const Cell& c) const
    {
        return c.x * 42 + c.y;
    }
};

class CellWorld
{
    int _sizeX;
    int _sizeY;
    uint _currentGeneration;

    std::vector<Cell> getNB(const Cell& cell)
    {
        std::vector<Cell> neighbours;
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                int posX = (_sizeX + cell.x + dx) % _sizeX;
                int posY = (_sizeY + cell.y + dy) % _sizeY;
                neighbours.push_back({ posX, posY, 0 });
            }
        }
        return neighbours;
    }

    std::unordered_set<Cell, CellHash> *board;
    std::list<std::unordered_set<Cell, CellHash>> history;


public:
    CellWorld(){}

    void init(unsigned int x, unsigned int y)
    {
        _sizeX = x;
        _sizeY = y;
        _currentGeneration = 0;
        history.push_back(std::unordered_set<Cell, CellHash>());
        board = &history.back();
    }

    void put(int x, int y)
    {
        if (x < _sizeX and x >= 0)
            if (y < _sizeY and y >= 0)
                board->insert(Cell{ x, y, _currentGeneration });
    }

    void remove(int x, int y)
    {
        auto cell = board->find(Cell{ x, y, 0 });
        if (cell != board->end())
        {
            board->erase(cell);
        }
    }

    glm::vec2 worldSize()
    {
        return glm::vec2(_sizeX, _sizeY);
    }

    const std::unordered_set<Cell, CellHash>& getBoard() const
    {
        return *board;
    }

    void pop()
    {
        if(history.size() > 1)
        {
            history.pop_back();
            board = &history.back();
            _currentGeneration--;
        }
    }

    uint currentGeneration() const
    {
        return _currentGeneration;
    }

    void simStep()
    {
        std::unordered_map<Cell, int, CellHash> num_neighbours;

        // Count neighbours of each cell
        for (Cell c : *board)
        {
            for (Cell n : getNB(c))
            {
                if (num_neighbours.count(n) == 0)
                {
                    num_neighbours.emplace(n, 0);
                }
                ++num_neighbours[n]; // Note each cell counts itself as a
                                     // neighbour
            }
        }
        for (auto pair : num_neighbours)
        {
            Cell c;
            int n;
            std::tie(c, n) = pair;
            //            c = pair.first;
            //            n = pair.second;

            if (n == 3)
            {
                board->insert(Cell{ c.x, c.y, _currentGeneration });
            }
            else if (board->count(c) == 1 and n != 4)
            {
                board->erase(c);
            }
        }
        _currentGeneration++;
        history.push_back(history.back());
        board = &history.back();
//        if(history.size() > 10)
//            history.erase(history.begin());
    }
};

#endif // CELLWORLD_H

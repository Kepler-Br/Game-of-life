#ifndef CELL_H
#define CELL_H

struct Cell
{
    int x;
    int y;
    unsigned int generation;

    bool operator==(const Cell& other) const
    {
        return (x == other.x) and (y == other.y);
    }
};

#endif // CELL_H

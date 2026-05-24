#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "maze.h"

#include <vector>

// Ищет кратчайший путь по лабиринту алгоритмом A*.
class AStarPathfinder {
public:
    std::vector<Point> findPath(const Maze& maze, Point start, Point finish) const;

private:
    static int manhattanDistance(Point first, Point second);
    static int pointToIndex(Point point, int width);
    static Point indexToPoint(int index, int width);
};

#endif

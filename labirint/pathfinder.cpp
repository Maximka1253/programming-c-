#include "pathfinder.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <queue>
#include <stdexcept>
#include <utility>

using namespace std;

// Для движения по четырём направлениям подходит манхэттенское расстояние.
int AStarPathfinder::manhattanDistance(Point first, Point second) {
    return abs(first.x - second.x) + abs(first.y - second.y);
}

// Индекс нужен, чтобы хранить данные о клетках в одномерных массивах.
int AStarPathfinder::pointToIndex(Point point, int width) {
    return point.y * width + point.x;
}

Point AStarPathfinder::indexToPoint(int index, int width) {
    return {index % width, index / width};
}

vector<Point> AStarPathfinder::findPath(const Maze& maze, Point start, Point finish) const {
    const int width = maze.width();
    const int height = maze.height();
    const int total = width * height;

    // Старт и финиш должны находиться внутри изображения.
    if (!maze.isInside(start) || !maze.isInside(finish)) {
        throw out_of_range("Start or finish point is outside the image");
    }

    const int startIndex = pointToIndex(start, width);
    const int finishIndex = pointToIndex(finish, width);

    vector<int> previous(total, -1);
    vector<int> distanceFromStart(total, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> cellsToVisit;

    // В очереди лежит пара: оценка пути и индекс клетки.
    previous[startIndex] = startIndex;
    distanceFromStart[startIndex] = 0;
    cellsToVisit.push({manhattanDistance(start, finish), startIndex});

    // Движение разрешено только вверх, вниз, влево и вправо.
    const array<Point, 4> directions = {{
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    }};

    // A* всегда берёт клетку с минимальной оценкой.
    while (!cellsToVisit.empty()) {
        const int current = cellsToVisit.top().second;
        cellsToVisit.pop();

        if (current == finishIndex) {
            break;
        }

        const Point currentPoint = indexToPoint(current, width);
        for (const Point& direction : directions) {
            const Point nextPoint = currentPoint + direction;
            if (!maze.isInside(nextPoint)) {
                continue;
            }

            const int next = pointToIndex(nextPoint, width);
            const int newDistance = distanceFromStart[current] + 1;

            if (maze.isPassable(nextPoint) &&
                (distanceFromStart[next] == -1 || newDistance < distanceFromStart[next])) {
                previous[next] = current;
                distanceFromStart[next] = newDistance;

                // Оценка = пройденное расстояние + примерное расстояние до финиша.
                const int priority = distanceFromStart[next] +
                                     manhattanDistance(nextPoint, finish);
                cellsToVisit.push({priority, next});
            }
        }
    }

    if (previous[finishIndex] == -1) {
        throw runtime_error("Path was not found");
    }

    // Восстанавливаем путь от финиша к старту по массиву previous.
    vector<Point> path;
    for (int current = finishIndex; current != startIndex; current = previous[current]) {
        path.push_back(indexToPoint(current, width));
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

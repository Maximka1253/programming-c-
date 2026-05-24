#ifndef MAZE_H
#define MAZE_H

#include "bmp.h"

#include <cstdint>
#include <string>

struct Point {
    int x = 0;
    int y = 0;
};

Point operator+(Point first, Point second);
bool operator==(Point first, Point second);
bool operator!=(Point first, Point second);

struct MazeColorSettings {
    std::uint8_t markerMinimum = 120;
    double markerDominance = 1.5;
    std::uint8_t roadMinimum = 200;
};

// Определяет смысл пикселей лабиринта по цвету.
class MazeColorClassifier {
public:
    explicit MazeColorClassifier(MazeColorSettings settings = MazeColorSettings{});

    bool isStart(Pixel pixel) const;
    bool isFinish(Pixel pixel) const;
    bool isRoad(Pixel pixel) const;
    bool isPassable(Pixel pixel) const;

private:
    MazeColorSettings settings;
};

// Предметная модель лабиринта, построенная поверх изображения.
class Maze {
public:
    Maze(const BmpImage& image, MazeColorClassifier classifier);

    int width() const;
    int height() const;
    bool isInside(Point point) const;
    bool isPassable(Point point) const;
    Point start() const;
    Point finish() const;

private:
    Point findMarkerCenter(bool needStart, const std::string& name) const;

    const BmpImage& image;
    MazeColorClassifier classifier;
    Point startPoint;
    Point finishPoint;
};

#endif

#ifndef PAINTER_H
#define PAINTER_H

#include "bmp.h"
#include "maze.h"

#include <vector>

struct MazeRenderSettings {
    Pixel pathColor{0, 0, 255};
    int pathRadius = 2;
};

// Класс для рисования найденного пути поверх исходного изображения.
class MazePathPainter {
public:
    MazePathPainter(BmpImage& image, MazeRenderSettings settings);

    void drawPath(const std::vector<Point>& path);

private:
    BmpImage& image;
    MazeRenderSettings settings;
};

#endif

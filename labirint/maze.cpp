#include "maze.h"

#include <stdexcept>

using namespace std;

// Удобно складывать точку и направление движения.
Point operator+(Point first, Point second) {
    return {first.x + second.x, first.y + second.y};
}

bool operator==(Point first, Point second) {
    return first.x == second.x && first.y == second.y;
}

bool operator!=(Point first, Point second) {
    return !(first == second);
}

MazeColorClassifier::MazeColorClassifier(MazeColorSettings settings)
    : settings(settings) {
}

// Стартовый маркер считается зелёным, если зелёная компонента заметно сильнее остальных.
bool MazeColorClassifier::isStart(Pixel pixel) const {
    return pixel.g > settings.markerMinimum &&
           pixel.g > pixel.r * settings.markerDominance &&
           pixel.g > pixel.b * settings.markerDominance;
}

// Финишный маркер определяется по преобладанию красной компоненты.
bool MazeColorClassifier::isFinish(Pixel pixel) const {
    return pixel.r > settings.markerMinimum &&
           pixel.r > pixel.g * settings.markerDominance &&
           pixel.r > pixel.b * settings.markerDominance;
}

// Белые пиксели считаются проходами лабиринта.
bool MazeColorClassifier::isRoad(Pixel pixel) const {
    return pixel.r > settings.roadMinimum &&
           pixel.g > settings.roadMinimum &&
           pixel.b > settings.roadMinimum;
}

bool MazeColorClassifier::isPassable(Pixel pixel) const {
    return isRoad(pixel) || isStart(pixel) || isFinish(pixel);
}

// При создании лабиринта сразу находим старт и финиш.
Maze::Maze(const BmpImage& image, MazeColorClassifier classifier)
    : image(image),
      classifier(classifier),
      startPoint(findMarkerCenter(true, "green start")),
      finishPoint(findMarkerCenter(false, "red finish")) {
}

int Maze::width() const {
    return image.width();
}

int Maze::height() const {
    return image.height();
}

bool Maze::isInside(Point point) const {
    return image.isInside(point);
}

bool Maze::isPassable(Point point) const {
    return isInside(point) && classifier.isPassable(image.getPixel(point));
}

Point Maze::start() const {
    return startPoint;
}

Point Maze::finish() const {
    return finishPoint;
}

Point Maze::findMarkerCenter(bool needStart, const string& name) const {
    // Центр маркера считаем как среднюю координату всех пикселей нужного цвета.
    long long sumX = 0;
    long long sumY = 0;
    int count = 0;

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            const Pixel currentPixel = image.getPixel(x, y);
            const bool found = needStart
                ? classifier.isStart(currentPixel)
                : classifier.isFinish(currentPixel);
            if (found) {
                sumX += x;
                sumY += y;
                ++count;
            }
        }
    }

    if (count == 0) {
        throw runtime_error("Cannot find " + name + " marker");
    }

    return {static_cast<int>(sumX / count), static_cast<int>(sumY / count)};
}

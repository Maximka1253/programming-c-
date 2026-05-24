#include "painter.h"

using namespace std;

MazePathPainter::MazePathPainter(BmpImage& image, MazeRenderSettings settings)
    : image(image),
      settings(settings) {
}

void MazePathPainter::drawPath(const vector<Point>& path) {
    // Для каждой точки пути закрашиваем маленький круг, чтобы линия была толще.
    for (const Point& point : path) {
        for (int dy = -settings.pathRadius; dy <= settings.pathRadius; ++dy) {
            for (int dx = -settings.pathRadius; dx <= settings.pathRadius; ++dx) {
                if (dx * dx + dy * dy > settings.pathRadius * settings.pathRadius) {
                    continue;
                }

                const Point current{point.x + dx, point.y + dy};
                if (image.isInside(current)) {
                    image.setPixel(current, settings.pathColor);
                }
            }
        }
    }
}

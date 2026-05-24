#include "maze.h"
#include "painter.h"
#include "pathfinder.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

int main() {
    try {
        // Входной и выходной файлы программы.
        const std::string inputFile = "ДНК_Лабиринт.bmp";
        const std::string outputFile = "result.bmp";

        // Загружаем лабиринт из BMP-файла.
        BmpReader reader;
        BmpImage image = reader.readFromFile(inputFile);

        // Находим старт, финиш и кратчайший путь между ними.
        MazeColorClassifier classifier;
        Maze maze(image, classifier);
        AStarPathfinder pathfinder;
        const Point start = maze.start();
        const Point finish = maze.finish();
        const std::vector<Point> path = pathfinder.findPath(maze, start, finish);

        // Рисуем путь на изображении и сохраняем результат.
        MazeRenderSettings renderSettings;
        MazePathPainter painter(image, renderSettings);
        painter.drawPath(path);
        BmpWriter writer;
        writer.writeToFile(image, outputFile);

        std::cout << "Start: (" << start.x << ", " << start.y << ")\n"
                  << "Finish: (" << finish.x << ", " << finish.y << ")\n"
                  << "Path length: " << path.size() << " pixels\n"
                  << "Saved: " << outputFile << '\n';

        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}

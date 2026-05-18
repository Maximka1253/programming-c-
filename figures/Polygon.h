#ifndef POLYGON_H
#define POLYGON_H

#include <cmath>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "figures.h"

class Polygon : public Figure {
public:
    using Point = std::pair<double, double>;

    explicit Polygon(std::vector<Point> inputPoints)
        : points(std::move(inputPoints)) {
        if (points.size() < 3) {
            throw std::invalid_argument("Polygon must have at least 3 points");
        }
    }

    double area() const override {
        double sum = 0.0;

        for (std::size_t i = 0; i < points.size(); ++i) {
            const Point& current = points[i];
            const Point& next = points[(i + 1) % points.size()];
            sum += current.first * next.second - next.first * current.second;
        }

        return std::abs(sum) / 2.0;
    }

    double perimeter() const override {
        double sum = 0.0;

        for (std::size_t i = 0; i < points.size(); ++i) {
            const Point& current = points[i];
            const Point& next = points[(i + 1) % points.size()];
            const double dx = current.first - next.first;
            const double dy = current.second - next.second;
            sum += std::sqrt(dx * dx + dy * dy);
        }

        return sum;
    }

    std::string name() const override {
        return "Polygon";
    }

private:
    std::vector<Point> points;
};

#endif

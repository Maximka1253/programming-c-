#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdexcept>
#include <string>

#include "figures.h"

class Rectangle : public Figure {
public:
    Rectangle(double inputWidth, double inputHeight)
        : width(inputWidth), height(inputHeight) {
        if (inputWidth <= 0 || inputHeight <= 0) {
            throw std::invalid_argument("Стороны прямоугольника должны быть положительными");
        }
    }

    double area() const override {
        return width * height;
    }

    double perimeter() const override {
        return 2.0 * (width + height);
    }

    std::string name() const override {
        return "Прямоугольник";
    }

private:
    double width;
    double height;
};

#endif

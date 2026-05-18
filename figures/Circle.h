#ifndef CIRCLE_H
#define CIRCLE_H

#include <cmath>
#include <stdexcept>
#include <string>

#include "figures.h"

class Circle : public Figure {
public:
    explicit Circle(double inputRadius) : radius(inputRadius) {
        if (inputRadius <= 0) {
            throw std::invalid_argument("Радиус круга должен быть положительным");
        }
    }

    double area() const override {
        return M_PI * radius * radius;
    }

    double perimeter() const override {
        return 2.0 * M_PI * radius;
    }

    std::string name() const override {
        return "Круг";
    }

private:
    double radius;
};

#endif

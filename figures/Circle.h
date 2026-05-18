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
            throw std::invalid_argument("Circle radius must be positive");
        }
    }

    double area() const override {
        return pi() * radius * radius;
    }

    double perimeter() const override {
        return 2.0 * pi() * radius;
    }

    std::string name() const override {
        return "Circle";
    }

private:
    static double pi() {
        return std::acos(-1.0);
    }

    double radius;
};

#endif

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cmath>
#include <stdexcept>
#include <string>

#include "figures.h"

class Triangle : public Figure {
public:
    Triangle(double inputA, double inputB, double inputC)
        : a(inputA), b(inputB), c(inputC) {
        if (inputA <= 0 || inputB <= 0 || inputC <= 0) {
            throw std::invalid_argument("Triangle sides must be positive");
        }
        if (inputA + inputB <= inputC || inputA + inputC <= inputB ||
            inputB + inputC <= inputA) {
            throw std::invalid_argument("Triangle inequality is broken");
        }
    }

    double area() const override {
        const double halfPerimeter = perimeter() / 2.0;
        return std::sqrt(halfPerimeter * (halfPerimeter - a) *
                         (halfPerimeter - b) * (halfPerimeter - c));
    }

    double perimeter() const override {
        return a + b + c;
    }

    std::string name() const override {
        return "Triangle";
    }

private:
    double a;
    double b;
    double c;
};

#endif

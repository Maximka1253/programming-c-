#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <cmath>
#include <stdexcept>
#include <string>

#include "figures.h"

class Ellipse : public Figure {
public:
    Ellipse(double inputSemiMajorAxis, double inputSemiMinorAxis)
        : semiMajorAxis(inputSemiMajorAxis),
          semiMinorAxis(inputSemiMinorAxis) {
        if (inputSemiMajorAxis <= 0 || inputSemiMinorAxis <= 0) {
            throw std::invalid_argument("Ellipse axes must be positive");
        }
    }

    double area() const override {
        return pi() * semiMajorAxis * semiMinorAxis;
    }

    double perimeter() const override {
        const double a = semiMajorAxis;
        const double b = semiMinorAxis;
        const double h = std::pow(a - b, 2.0) / std::pow(a + b, 2.0);

        return pi() * (a + b) *
               (1.0 + (3.0 * h) / (10.0 + std::sqrt(4.0 - 3.0 * h)));
    }

    std::string name() const override {
        return "Ellipse";
    }

private:
    static double pi() {
        return std::acos(-1.0);
    }

    double semiMajorAxis;
    double semiMinorAxis;
};

#endif

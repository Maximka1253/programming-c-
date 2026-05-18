#ifndef FIGURES_H
#define FIGURES_H

#include <string>

class Figure {
public:
    virtual ~Figure() = default;

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string name() const = 0;
};

#endif

#include <iomanip>
#include <iostream>
#include <vector>

#include "Circle.h"
#include "Ellipse.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "figures.h"

using namespace std;

int main() {
    Triangle triangle(3.0, 4.0, 5.0);
    Rectangle rectangle(4.0, 6.0);
    Polygon polygon(vector<Polygon::Point>{{0.0, 0.0},
                                           {4.0, 0.0},
                                           {4.0, 3.0},
                                           {0.0, 3.0}});
    Circle circle(5.0);
    Ellipse ellipse(6.0, 3.0);

    vector<Figure*> figures;

    figures.push_back(&triangle);
    figures.push_back(&rectangle);
    figures.push_back(&polygon);
    figures.push_back(&circle);
    figures.push_back(&ellipse);

    cout << fixed << setprecision(2);

    for (const auto& figure : figures) {
        cout << figure->name() << '\n'
             << "Площадь: " << figure->area() << '\n'
             << "Периметр: " << figure->perimeter() << "\n\n";
    }

    return 0;
}

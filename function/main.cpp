#include "function.h"

#include <clocale>
#include <iostream>
#include <vector>

using namespace std;

struct Demonstration {
    Function* function;
    double x;
    double left;
    double right;
    double step;
};

// Выводит основные результаты для одной функции.
void demonstrate(const Function* function, double x, double left, double right, double step) {
    cout << function->name() << '\n'
         << "Значение f(" << x << "): " << function->value(x) << '\n'
         << "Минимум на [" << left << "; " << right << "]: " << function->minimum(left, right, step) << '\n'
         << "Максимум на [" << left << "; " << right << "]: " << function->maximum(left, right, step) << '\n'
         << "Производная f'(" << x << "): " << function->derivative(x, 0.0001) << '\n'
         << "Интеграл на [" << left << "; " << right << "]: " << function->integral(left, right, step) << "\n\n";
}

int main() {
    setlocale(LC_ALL, "");

    vector<Demonstration> demonstrations = {
        {new Parabola(1, -2, 1), 2, -3, 3, 0.01},
        {new Hiperbola(4, 1), 2, 1, 5, 0.01},
        {new Exponenta(2, 0.5, 1), 1, 0, 3, 0.01},
        {new Polinom({1, -3, 2, 1}), 2, -2, 2, 0.01}
    };

    for (const auto& demonstration : demonstrations) {
        demonstrate(demonstration.function, demonstration.x, demonstration.left, demonstration.right, demonstration.step);
    }

    for (const auto& demonstration : demonstrations) {
        delete demonstration.function;
    }

    return 0;
}

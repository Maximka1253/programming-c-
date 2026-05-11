#include "function.h"

#include <clocale>
#include <iostream>

using namespace std;

// Выводит основные результаты для одной функции.
void demonstrate(const Function& function, double x, double left, double right, double step) {
    cout << endl << function.name() << endl;

    function.printValue(x);
    cout << "Минимум [" << left << "; " << right << "] = " << function.minimum(left, right, step) << endl;
    cout << "Максимум [" << left << "; " << right << "] = " << function.maximum(left, right, step) << endl;
    cout << "Производная f'(" << x << ") = " << function.derivative(x, 0.0001) << endl;
    cout << "Интеграл [" << left << "; " << right << "] = " << function.integral(left, right, step) << endl;
}

int main() {
    setlocale(LC_ALL, "");

    // Создание объектов разных классов функций.
    Parabola parabola(1, -2, 1);
    Hiperbola hiperbola(4, 1);
    Exponenta exponenta(2, 0.5, 1);
    Polinom polinom({1, -3, 2, 1});

    // Демонстрация работы каждого объекта.
    demonstrate(parabola, 2, -3, 3, 0.01);
    demonstrate(hiperbola, 2, 1, 5, 0.01);
    demonstrate(exponenta, 1, 0, 3, 0.01);
    demonstrate(polinom, 2, -2, 2, 0.01);

    return 0;
}

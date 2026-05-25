#include "function.h"

#include <clocale>
#include <iostream>
#include <vector>

using namespace std;


// Выводит основные результаты для одной функции.
void demonstrate(const Function* function, double x, double left, double right, double step) {
    cout << function->name() << '\n'
         << "Значение f(" << x << "): " << function->value(x) << '\n'
         << "Минимум на [" << left << "; " << right << "]: " << function->minimum(left, right, step) << '\n'
         << "Максимум на [" << left << "; " << right << "]: " << function->maximum(left, right, step) << '\n'
         << "Производная f'(" << x << "): " << function->derivative(x, 0.0001) << '\n'
         << "Интеграл на [" << left << "; " << right << "]: " << function->integral(left, right, step) << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    vector<Function*> functions;
    
    functions.push_back(new Polinom({1, 0.5, 2, 5}));
    
    for (const auto& function : functions) {
        demonstrate(function, 2.0, 1.0, 5.0, 0.1);
        cout << "-----------------------------\n";
    }

    for (const auto& function : functions) {
        delete function;
    }

    return 0;
}

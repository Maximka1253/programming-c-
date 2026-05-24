#include "function.h"

#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>

Function::~Function() {}

double Function::minimum(double left, double right, double step) const {
    checkInterval(left, right, step);

    double minValue = value(left);

    // Перебираем точки интервала и ищем наименьшее значение.
    for (double x = left + step; x < right; x += step) {
        double currentValue = value(x);

        if (currentValue < minValue) {
            minValue = currentValue;
        }
    }

    double rightValue = value(right);
    if (rightValue < minValue) {
        minValue = rightValue;
    }

    return minValue;
}

double Function::maximum(double left, double right, double step) const {
    checkInterval(left, right, step);

    double maxValue = value(left);

    // Перебираем точки интервала и ищем наибольшее значение.
    for (double x = left + step; x < right; x += step) {
        double currentValue = value(x);

        if (currentValue > maxValue) {
            maxValue = currentValue;
        }
    }

    double rightValue = value(right);
    if (rightValue > maxValue) {
        maxValue = rightValue;
    }

    return maxValue;
}

double Function::derivative(double x, double h) const {
    if (h <= 0) {
        throw std::invalid_argument("Шаг h должен быть положительным");
    }

    // Приближенная производная по формуле разности.
    return (value(x + h) - value(x)) / h;
}

double Function::integral(double left, double right, double step) const {
    checkInterval(left, right, step);

    double sum = 0;

    // Приближенный интеграл методом прямоугольников.
    for (double x = left; x < right; x += step) {
        double currentStep = step;

        if (x + currentStep > right) {
            currentStep = right - x;
        }

        sum += value(x) * currentStep;
    }

    return sum;
}

void Function::checkInterval(double left, double right, double step) const {
    if (left >= right) {
        throw std::invalid_argument("Левая граница должна быть меньше правой");
    }

    if (step <= 0) {
        throw std::invalid_argument("Шаг должен быть положительным");
    }
}

Hiperbola::Hiperbola(double a, double b) {
    this->a = a;
    this->b = b;
}

double Hiperbola::value(double x) const {
    if (x == 0) {
        throw std::invalid_argument("Деление на ноль в гиперболе");
    }

    return a / x + b;
}

std::string Hiperbola::name() const {
    return "Гипербола";
}

Parabola::Parabola(double a, double b, double c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

double Parabola::value(double x) const {
    return a * x * x + b * x + c;
}

std::string Parabola::name() const {
    return "Парабола";
}

Exponenta::Exponenta(double a, double b, double c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

double Exponenta::value(double x) const {
    return a * exp(b * x) + c;
}

std::string Exponenta::name() const {
    return "Экспонента";
}

Polinom::Polinom(const std::vector<double>& coefficients) {
    this->coefficients = coefficients;
}

double Polinom::value(double x) const {
    double result = 0;
    double power = 1;

    // Вычисляем сумму a0 + a1*x + a2*x^2  и т.д.
    for (std::size_t i = 0; i < coefficients.size(); i++) {
        result += coefficients[i] * power;
        power *= x;
    }

    return result;
}

std::string Polinom::name() const {
    return "Полином";
}

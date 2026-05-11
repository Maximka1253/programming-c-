#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>

class Function {
public:
    virtual ~Function();

    virtual double value(double x) const = 0;
    virtual std::string name() const = 0;

    void printValue(double x) const;
    double minimum(double left, double right, double step) const;
    double maximum(double left, double right, double step) const;
    double derivative(double x, double h) const;
    double integral(double left, double right, double step) const;

private:
    void checkInterval(double left, double right, double step) const;
};

class Hiperbola : public Function {
private:
    double a;
    double b;

public:
    Hiperbola(double a, double b);

    double value(double x) const override;
    std::string name() const override;
};

class Parabola : public Function {
private:
    double a;
    double b;
    double c;

public:
    Parabola(double a, double b, double c);

    double value(double x) const override;
    std::string name() const override;
};

class Exponenta : public Function {
private:
    double a;
    double b;
    double c;

public:
    Exponenta(double a, double b, double c);

    double value(double x) const override;
    std::string name() const override;
};

class Polinom : public Function {
private:
    std::vector<double> coefficients;

public:
    Polinom(const std::vector<double>& coefficients);

    double value(double x) const override;
    std::string name() const override;
};

#endif

#include <iostream>
#include "rational.h"

using namespace std;

int main() {
    Rational a(1,2), b(-1,6);
    cout << "a=" << a << " b=" << b << " a+b=" << a+b << endl;
    
    cout << "a(" << a << ") *= b(" << b << ")" << endl;
    a *= b;
    
    cout << "a=" << a << " b=" << b << " a-b=" << a-b << endl;
    
    Rational c = 3;
    cout << "b=" << b << " c=" << c << " b/c=" << b/c << endl;

    Rational h(3,4);
    int k = 2;
    cout << "h=" << h << " k=" << k << endl;
    cout << "h*k=" << h * k << " k*h=" << k * h << endl;
    cout << "h/k=" << h / k << " k/h=" << k / h << endl;
    h *= k;
    cout << "после h*=k: h=" << h << endl;
    h /= k;
    cout << "после h/=k: h=" << h << endl;

    Rational e(7,8), f(5,12);
    cout << "e=" << e << " f=" << f << " e+f=?" << endl;
    cout << "Введите результат g=m/n в формате: m n" << endl;
    
    Rational g;
    cin >> g;
    
    if (e+f != g)
        cout << "Неправильно! e+f=" << e+f << endl;
    else
        cout << "Правильно!" << endl;

    cout << boolalpha;
    Rational x(1,3), y(2,5);
    cout << "x=" << x << " y=" << y << endl;
    cout << "x < y: " << (x < y) << endl;
    cout << "x > y: " << (x > y) << endl;
    cout << "x <= y: " << (x <= y) << endl;
    cout << "x >= y: " << (x >= y) << endl;

    Rational qa, qb, qc;
    cout << "Введите коэффициенты квадратного уравнения ax^2 + bx + c = 0" << endl;
    cout << "Формат для каждого коэффициента: m n (например, 3 2 для 3/2)" << endl;
    cout << "Введите a: ";
    cin >> qa;
    cout << "Введите b: ";
    cin >> qb;
    cout << "Введите c: ";
    cin >> qc;
    cout << "Решение уравнения: " << qa << "*x^2 + (" << qb << ")*x + " << qc << " = 0" << endl;
    QuadUravnenie(qa, qb, qc);

    return 0;
}

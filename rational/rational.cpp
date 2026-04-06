#include "rational.h"
#include <cmath>

using namespace std;

Rational::Rational() {
    numer = 0;
    denom = 1;
}

Rational::Rational(int number) {
    numer = number;
    denom = 1;
}

Rational::Rational(int n, int d) {
    numer = n;
    denom = d;
    simplify();
}

int Rational::gcd(int a, int b) const {
    a = abs(a);
    b = abs(b);
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

void Rational::simplify() {
    if (denom < 0) {
        numer = -numer;
        denom = -denom;
    }
    int g = gcd(numer, denom);
    if (g > 1) {
        numer /= g;
        denom /= g;
    }
}
//алгоритм евклида
Rational& Rational::operator +=(const Rational& r) {
    numer = (numer * r.denom + denom * r.numer);
    denom *= r.denom;
    simplify();
    return *this;
}

Rational Rational::operator +(const Rational &r) const {
    Rational res(*this);
    return res += r;
}

Rational Rational::operator -() const {
    return Rational(-numer, denom);
}

Rational& Rational::operator -=(const Rational& r) {
    return (*this += (-r));
}

Rational Rational::operator -(const Rational &r) const {
    Rational res(*this);
    return res -= r;
}

Rational& Rational::operator *=(const Rational& r) {
    numer *= r.numer;
    denom *= r.denom;
    simplify();
    return *this;
}

Rational Rational::operator *(const Rational &r) const {
    Rational res(*this);
    return res *= r;
}

Rational& Rational::operator /=(const Rational& r) {
    numer *= r.denom;
    denom *= r.numer;
    simplify();
    return *this;
}

Rational Rational::operator /(const Rational &r) const {
    Rational res(*this);
    return res /= r;
}

Rational& Rational::operator ++() {
    numer += denom;
    return *this;
}

Rational Rational::operator ++(int) {
    Rational r(*this);
    numer += denom;
    return r;
}

bool Rational::operator ==(const Rational& r) const {
    return (numer == r.numer) && (denom == r.denom);
}

bool Rational::operator !=(const Rational& r) const {
    return !(*this == r);
}

bool Rational::operator <(const Rational& r) const {
    return (long long)numer * r.denom < (long long)r.numer * denom;
}

bool Rational::operator >(const Rational& r) const {
    return r < *this;
}

bool Rational::operator <=(const Rational& r) const {
    return !(*this > r);
}

bool Rational::operator >=(const Rational& r) const {
    return !(*this < r);
}

Rational::operator int() const {
    return numer / denom;
}

Rational::operator double() const {
    return ((double)numer) / denom;
}

istream& operator >>(istream& in, Rational& r) {
    in >> r.numer >> r.denom;
    r.simplify();
    return in;
}

ostream& operator <<(ostream& out, const Rational& r) {
    out << r.numer << "/" << r.denom;
    return out;
}

void QuadUravnenie(Rational a, Rational b, Rational c) {
    const Rational zero(0), two(2), four(4);

    if (a == zero) {
        if (b == zero) {
            cout << (c == zero ? "Бесконечно много решений." : "Решений нет.") << endl;
            return;
        }
        cout << "Линейное уравнение, x = " << static_cast<double>((-c) / b) << endl;
        return;
    }

    const double d = static_cast<double>(b * b - four * a * c);
    if (d < 0.0) {
        cout << "Действительных корней нет." << endl;
        return;
    }

    const double denom = static_cast<double>(two * a);
    const double minusB = static_cast<double>(-b);
    if (d == 0.0) {
        cout << "Один корень: x = " << (minusB / denom) << endl;
        return;
    }

    const double sqrtD = sqrt(d);
    cout << "Два корня: x1 = " << (minusB + sqrtD) / denom
         << ", x2 = " << (minusB - sqrtD) / denom << endl;
}
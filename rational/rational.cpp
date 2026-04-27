#include "rational.h"
#include <cmath>
#include <stdexcept>

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
    if (denom == 0) {
        throw invalid_argument("Denominator cannot be zero");
    }
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

Rational& Rational::operator *=(int value) {
    numer *= value;
    simplify();
    return *this;
}

Rational Rational::operator *(int value) const {
    Rational res(*this);
    return res *= value;
}

Rational operator *(int lhs, const Rational& rhs) {
    return Rational(lhs) * rhs;
}

Rational& Rational::operator /=(const Rational& r) {
    if (r.numer == 0) {
        throw domain_error("0 не может быть знаменателем");
    }
    numer *= r.denom;
    denom *= r.numer;
    simplify();
    return *this;
}

Rational Rational::operator /(const Rational &r) const {
    Rational res(*this);
    return res /= r;
}

Rational& Rational::operator /=(int value) {
    if (value == 0) {
        throw domain_error("Division by zero integer");
    }
    denom *= value;
    simplify();
    return *this;
}

Rational Rational::operator /(int value) const {
    Rational res(*this);
    return res /= value;
}

Rational operator /(int lhs, const Rational& rhs) {
    return Rational(lhs) / rhs;
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
    int n;
    int d;
    in >> n >> d;
    if (!in) {
        return in;
    }
    if (d == 0) {
        in.setstate(ios::failbit);
        return in;
    }

    r.numer = n;
    r.denom = d;
    r.simplify();
    return in;
}

ostream& operator <<(ostream& out, const Rational& r) {
    out << r.numer << "/" << r.denom;
    return out;
}

void QuadUravnenie(Rational a, Rational b, Rational c) {
    if (a == Rational(0)) {
        if (b == Rational(0)) {
            cout << (c == Rational(0) ? "Бесконечно много решений." : "Решений нет.") << endl;
            return;
        }
        cout << "Линейное уравнение, x = " << static_cast<double>((-c) / b) << endl;
        return;
    }

    const Rational discriminant = b * b - 4 * a * c;
    if (discriminant < Rational(0)) {
        cout << "Действительных корней нет." << endl;
        return;
    }

    const double d = static_cast<double>(discriminant);
    const double denom = static_cast<double>(2 * a);
    const double minusB = static_cast<double>(-b);
    if (discriminant == Rational(0)) {
        cout << "Один корень: x = " << (minusB / denom) << endl;
        return;
    }

    const double sqrtD = sqrt(d);
    cout << "Два корня: x1 = " << (minusB + sqrtD) / denom
         << ", x2 = " << (minusB - sqrtD) / denom << endl;
}

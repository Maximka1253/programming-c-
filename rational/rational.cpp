#include "rational.h"
#include <cmath>
#include <limits>
#include <stdexcept>

using namespace std;

const long long LL_MIN = numeric_limits<long long>::min();

// Сложение с проверкой на переполнение.
long long checkedAdd(long long a, long long b) {
    long long result;
    if (__builtin_add_overflow(a, b, &result))
        throw overflow_error("Rational value is out of long long range");
    return result;
}

// Смена знака с проверкой для минимального long long.
long long checkedNeg(long long value) {
    if (value == LL_MIN)
        throw overflow_error("Rational value is out of long long range");
    return -value;
}

// Умножение с проверкой на переполнение.
long long checkedMul(long long a, long long b) {
    long long result;
    if (__builtin_mul_overflow(a, b, &result))
        throw overflow_error("Rational value is out of long long range");
    return result;
}

// Умножение на 2 несколько раз с проверкой.
long long checkedShiftLeft(long long value, int shift) {
    for (int i = 0; i < shift; ++i) value = checkedMul(value, 2);
    return value;
}

// Модуль числа без риска переполнения.
long long checkedAbs(long long value) {
    return value < 0 ? checkedNeg(value) : value;
}

// Проверяет, является ли число точным квадратом.
bool exactSquare(long long value, long long& root) {
    if (value < 0) return false;

    root = static_cast<long long>(sqrt(static_cast<long double>(value)));
    while (root <= numeric_limits<long long>::max() / root && root * root < value) ++root;
    while (root > 0 && root * root > value) --root;

    return root <= numeric_limits<long long>::max() / root && root * root == value;
}

Rational::Rational() : numer(0), denom(1) {}
Rational::Rational(int number) : numer(number), denom(1) {}
Rational::Rational(long long number) : numer(number), denom(1) {}

Rational::Rational(long long n, long long d) : numer(n), denom(d) {
    simplify();
}

Rational::Rational(double value) {
    if (!isfinite(value)) throw invalid_argument("Value must be finite");
    if (value == 0.0) {
        numer = 0;
        denom = 1;
        return;
    }

    // Представляем double как мантиссу * 2^e экспоненту.
    int exponent;
    const double mantissa = frexp(value, &exponent);
    const long long scale = 1LL << numeric_limits<double>::digits;

    long long n = llround(mantissa * scale);
    long long d = scale;

    if (exponent > 0) n = checkedShiftLeft(n, exponent);
    else if (exponent < 0) d = checkedShiftLeft(d, -exponent);

    numer = n;
    denom = d;
    simplify();
}

long long Rational::gcd(long long a, long long b) const {
    a = checkedAbs(a);
    b = checkedAbs(b);
    // Алгоритм Евклида.
    while (b) {
        a %= b; swap(a, b);
    }
    return a;
}

void Rational::simplify() {
    if (denom == 0) throw invalid_argument("Denominator cannot be zero");
    // Минус всегда храним в числителе.
    if (denom < 0) {
        numer = checkedNeg(numer);
        denom = checkedNeg(denom);
    }
    long long g = gcd(numer, denom);
    if (g > 1) {
        numer /= g;
        denom /= g;
    }
}

Rational& Rational::operator +=(const Rational& r) {
    // Сокращение знаменателей, чтобы уменьшить риск переполнения.
    const long long common = gcd(denom, r.denom);
    const long long leftDen = denom / common;
    const long long rightDen = r.denom / common;
    const long long left = checkedMul(numer, rightDen);
    const long long right = checkedMul(r.numer, leftDen);

    numer = checkedAdd(left, right);
    denom = checkedMul(leftDen, r.denom);
    simplify();
    return *this;
}

Rational Rational::operator +(const Rational &r) const {
    Rational res(*this); return res += r;
}

Rational Rational::operator -() const {
    return Rational(checkedNeg(numer), denom);
}

Rational& Rational::operator -=(const Rational& r) {
    return (*this += (-r));
}

Rational Rational::operator -(const Rational &r) const {
    Rational res(*this); return res -= r;
}

Rational& Rational::operator *=(const Rational& r) {
    long long n1 = numer;
    long long d1 = denom;
    long long n2 = r.numer;
    long long d2 = r.denom;

    // Сокращаем крест-накрест перед умножением.
    long long g = gcd(n1, d2);
    n1 /= g; d2 /= g;
    g = gcd(n2, d1);
    n2 /= g; d1 /= g;

    numer = checkedMul(n1, n2);
    denom = checkedMul(d1, d2);
    simplify();
    return *this;
}

Rational Rational::operator *(const Rational &r) const {
    Rational res(*this); return res *= r;
}

Rational& Rational::operator *=(int value) {
    numer = checkedMul(numer, value);
    simplify();
    return *this;
}

Rational Rational::operator *(int value) const {
    Rational res(*this); return res *= value;
}

Rational operator *(int lhs, const Rational& rhs) {
    return Rational(lhs) * rhs;
}

Rational& Rational::operator /=(const Rational& r) {
    if (r.numer == 0) throw domain_error("0 не может быть знаменателем");
    return *this *= Rational(r.denom, r.numer);
}

Rational Rational::operator /(const Rational &r) const {
    Rational res(*this); return res /= r;
}

Rational& Rational::operator /=(int value) {
    if (value == 0) throw domain_error("Division by zero integer");
    denom = checkedMul(denom, value);
    simplify();
    return *this;
}

Rational Rational::operator /(int value) const {
    Rational res(*this); return res /= value;
}

Rational operator /(int lhs, const Rational& rhs) {
    return Rational(lhs) / rhs;
}

Rational& Rational::operator ++() {
    numer = checkedAdd(numer, denom);
    return *this;
}

Rational Rational::operator ++(int) {
    Rational r(*this); numer = checkedAdd(numer, denom); return r;
}

bool Rational::operator ==(const Rational& r) const { return numer == r.numer && denom == r.denom; }
bool Rational::operator !=(const Rational& r) const { return !(*this == r); }

bool Rational::operator <(const Rational& r) const {
    return checkedMul(numer, r.denom) < checkedMul(r.numer, denom);
}

bool Rational::operator >(const Rational& r) const { return r < *this; }
bool Rational::operator <=(const Rational& r) const { return !(*this > r); }
bool Rational::operator >=(const Rational& r) const { return !(*this < r); }

Rational::operator int() const { return numer / denom; }
Rational::operator double() const { return static_cast<double>(numer) / denom; }

istream& operator >>(istream& in, Rational& r) {
    long long n;
    long long d;
    in >> n >> d;
    if (!in) return in;
    // Нулевой знаменатель считаем ошибкой ввода.
    if (d == 0) {
        in.setstate(ios::failbit);
        return in;
    }

    r.numer = n;
    r.denom = d;
    r.simplify();
    return in;
}

ostream& operator <<(ostream& out, const Rational& r) { return out << r.numer << "/" << r.denom; }

void QuadUravnenie(Rational a, Rational b, Rational c) {
    // Если a = 0, уравнение становится линейным.
    if (a == Rational(0)) {
        if (b == Rational(0)) {
            cout << (c == Rational(0) ? "Бесконечно много решений." : "Решений нет.") << endl;
            return;
        }
        cout << "Линейное уравнение, x = " << ((-c) / b) << endl;
        return;
    }

    const Rational discriminant = b * b - 4 * a * c;
    // Отрицательный дискриминант не дает действительных корней.
    if (discriminant < Rational(0)) {
        cout << "Действительных корней нет." << endl;
        return;
    }

    const Rational twoA = 2 * a;
    // Нулевой дискриминант дает один корень.
    if (discriminant == Rational(0)) {
        cout << "Один корень: x = " << ((-b) / twoA) << endl;
        return;
    }

    long long sqrtNumer;
    long long sqrtDenom;
    // Корень рационален, если числитель и знаменатель D - точные квадраты.
    if (exactSquare(discriminant.numer, sqrtNumer) && exactSquare(discriminant.denom, sqrtDenom)) {
        const Rational sqrtD(sqrtNumer, sqrtDenom);
        cout << "Два корня: x1 = " << ((-b + sqrtD) / twoA) << ", x2 = " << ((-b - sqrtD) / twoA) << endl;
        return;
    }

    // Точная запись через sqrt, без округления в double.
    cout << "Корни не являются рациональными." << endl;
    cout << "Точно: x1 = (" << -b << " + sqrt(" << discriminant << ")) / (" << twoA << ")" << ", x2 = (" << -b << " - sqrt(" << discriminant << ")) / (" << twoA << ")" << endl;
}

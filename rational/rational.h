#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational {
private:
    int numer;
    int denom;

    int gcd(int a, int b) const;
    void simplify();

public:
    Rational();
    Rational(int number);
    Rational(int n, int d);

    Rational& operator +=(const Rational& r);
    Rational operator +(const Rational& r) const;

    Rational operator -() const;
    Rational& operator -=(const Rational& r);
    Rational operator -(const Rational& r) const;

    Rational& operator *=(const Rational& r);
    Rational operator *(const Rational& r) const;

    Rational& operator /=(const Rational& r);
    Rational operator /(const Rational& r) const;

    Rational& operator ++();
    Rational operator ++(int);

    bool operator ==(const Rational& r) const;
    bool operator !=(const Rational& r) const;
    bool operator <(const Rational& r) const;
    bool operator >(const Rational& r) const;
    bool operator <=(const Rational& r) const;
    bool operator >=(const Rational& r) const;


    operator int() const;
    operator double() const;

    friend std::istream& operator >>(std::istream& in, Rational& r);
    friend std::ostream& operator <<(std::ostream& out, const Rational& r);
};

void QuadUravnenie(Rational a, Rational b, Rational c);

#endif
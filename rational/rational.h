#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational {
private:
    long long numer;
    long long denom;

    long long gcd(long long a, long long b) const;
    void simplify();

public:
    Rational();
    Rational(int number);
    Rational(long long number);
    Rational(long long n, long long d);
    Rational(double value);

    Rational& operator +=(const Rational& r);
    Rational operator +(const Rational& r) const;

    Rational operator -() const;
    Rational& operator -=(const Rational& r);
    Rational operator -(const Rational& r) const;

    Rational& operator *=(const Rational& r);
    Rational operator *(const Rational& r) const;
    Rational& operator *=(int value);
    Rational operator *(int value) const;
    friend Rational operator *(int lhs, const Rational& rhs);

    Rational& operator /=(const Rational& r);
    Rational operator /(const Rational& r) const;
    Rational& operator /=(int value);
    Rational operator /(int value) const;
    friend Rational operator /(int lhs, const Rational& rhs);

    Rational& operator ++();
    Rational operator ++(int);

    bool operator ==(const Rational& r) const;
    bool operator !=(const Rational& r) const;
    bool operator <(const Rational& r) const;
    bool operator >(const Rational& r) const;
    bool operator <=(const Rational& r) const;
    bool operator >=(const Rational& r) const;


    explicit operator int() const;
    explicit operator double() const;

    friend std::istream& operator >>(std::istream& in, Rational& r);
    friend std::ostream& operator <<(std::ostream& out, const Rational& r);
    friend void QuadUravnenie(Rational a, Rational b, Rational c);
};

void QuadUravnenie(Rational a, Rational b, Rational c);

#endif

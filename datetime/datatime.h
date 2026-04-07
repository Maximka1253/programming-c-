#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>

class DateTime {
private:
    int year, month, day;
    int hour, minute, second;

    static bool leapYear(int year);
    static int daysinMonth(int month, int year);

public:
    DateTime(int year = 2007, int month = 9, int day = 21,
        int hour = 0, int minute = 0, int second = 0);
    ~DateTime();

    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    int getWeekDay() const;
    std::string getWeekDayName() const;

    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);

    bool isValid() const;

    double toJulDay() const;
    static DateTime fromJulDay(double jd);

    DateTime operator+(int days) const;
    DateTime operator-(int days) const;
    int operator-(const DateTime& other) const;

    bool operator==(const DateTime& r) const;
    bool operator!=(const DateTime& r) const;
    bool operator<(const DateTime& r) const;
    bool operator>(const DateTime& r) const;
    bool operator<=(const DateTime& r) const;
    bool operator>=(const DateTime& r) const;

    friend std::istream& operator>>(std::istream& is, DateTime& dt);
    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);
};

#endif // DATETIME_H

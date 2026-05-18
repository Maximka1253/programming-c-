#ifndef DATETIME_H
#define DATETIME_H
#include <iostream>
#include <string>


class DateTime {
private:
    int year, month, day;
    int hour, minute, second;
    bool valid;

    static bool leapYear(int year);
    static int daysinMonth(int month, int year);
    static bool isValidDateTime(int year, int month, int day,
        int hour, int minute, int second);
    static void printValidationError(int year, int month, int day,
        int hour, int minute, int second);
    DateTime invalidCopy() const;

public:
    DateTime(int year = 2007, int month = 9, int day = 21,
        int hour = 0, int minute = 0, int second = 0);

    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }

    int getWeekDay() const;
    std::string getWeekDayName() const;

    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);

    bool isValid() const;

    DateTime startOfDay() const;

    double toJulDay() const;
    static DateTime fromJulDay(double jd);
    static DateTime fromYmdHms(long ymd, const std::string& hms);

    DateTime operator+(int days) const;
    DateTime operator-(int days) const;
    int operator-(const DateTime& other) const;

    bool operator==(const DateTime& r) const;
    bool operator!=(const DateTime& r) const;
    bool operator<(const DateTime& r) const;
    bool operator>(const DateTime& r) const;
    bool operator<=(const DateTime& r) const;
    bool operator>=(const DateTime& r) const;

    static DateTime getEaster(const DateTime& date);

    friend std::istream& operator>>(std::istream& is, DateTime& dt);
    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);
};

#endif // DATETIME_H
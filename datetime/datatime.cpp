#include "datatime.h"
#include <iomanip>
#include <cmath>


using namespace std;

bool DateTime::leapYear(int year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int DateTime::daysinMonth(int month, int year){
    switch (month)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return leapYear(year) ? 29:28;
        default: return -1;
    }
}

int DateTime::getWeekDay() const {
    int jdn = static_cast<int>(toJulDay() + 0.5);
    return (jdn + 1) % 7;
}

std::string DateTime::getWeekDayName() const {
    static const std::string days[] = {
        "Воскресенье",
        "Понедельник",
        "Вторник",
        "Среда",
        "Четверг",
        "Пятница",
        "Суббота"
    };
    return days[getWeekDay()];
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
    : year(year), month(1), day(1), hour(0), minute(0), second(0){
    if (month < 1 || month > 12) {
        cerr << "Месяц должен быть от 1 до 12";
        return;
    }
    int maxDay = daysinMonth(month, year);
    if (day < 1 || day > maxDay){
        cerr << "В " << year << "/" << month << " не более " << maxDay << " дней!!!" << endl;
        return; 
    }
    if (hour < 0 || hour > 23) {
        cerr << "В дне может быть только от 0 до 23 часа";
        return;
    }
    if (minute < 0 || minute > 59) {
        cerr << "В часу от 0 до 59 секунд";
        return;
    }
    if (second < 0 || second > 59) {
        cerr << "В минуте от 0 до 59 секунд";
        return;
    }
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

DateTime::~DateTime() {}

int DateTime::getYear() const {return year;}
int DateTime::getMonth() const {return month;}
int DateTime::getDay() const {return day;}
int DateTime::getHour() const {return hour;}
int DateTime::getMinute() const {return minute;}
int DateTime::getSecond() const {return second;}

void DateTime::setYear(int year) {
    this->year = year;
}

void DateTime::setMonth(int month) {
    if (month < 1 || month > 12) {
        cerr << "Месяц должен быть от 1 до 12\n";
        return;
    }

    int maxDay = daysinMonth(month, year);
    if (day > maxDay) {
        cerr << "Нельзя установить месяц " << month
             << ", потому что в нем только " << maxDay
             << " дней\n";
        return;
    }
    this->month = month;
}
void DateTime::setDay(int day) {
    int maxDay = daysinMonth(month, year);

    if (day < 1 || day > maxDay) {
        cerr << "Для " << year << "/" << month
             << " день должен быть от 1 до " << maxDay << "\n";
        return;
    }
    this->day = day;
}
void DateTime::setHour(int hour) {
    if (hour < 0 || hour > 23) {
        cerr << "Час должен быть от 0 до 23";
        return;
    }
    this->hour = hour;
}

void DateTime::setMinute(int minute) {
    if (minute < 0 || minute > 59) {
        cerr << "Минута должна быть от 0 до 59";
        return;
    }
    this->minute = minute;
}

void DateTime::setSecond(int second) {
    if (second < 0 || second > 59) {
        cerr << "Секунда должна быть от 0 до 59";
        return;
    }
    this->second = second;
}

bool DateTime::isValid() const {
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysinMonth(month, year)) return false;
    if (hour < 0 || hour > 23)   return false;
    if (minute < 0 || minute > 59) return false;
    if (second < 0 || second > 59) return false;
    return true;
}


double DateTime::toJulDay() const {
    int m14 = (month - 14) / 12;
    int jdn  = (1461 * (year + 4800 + m14)) / 4 + (367  * (month - 2 - 12 * m14)) / 12
            - (3    * ((year + 4900 + m14) / 100)) / 4 + day - 32075;

    double timeJD = (hour - 12) / 24.0 + minute / 1440.0 + second / 86400.0;
    return jdn + timeJD;
}

DateTime DateTime::fromJulDay(double jdn) {
    int int_jdn = static_cast<int>(jdn);
    double fractional_jdn = jdn - int_jdn;

    int f = int_jdn + 1401 + ((3 * (4 * int_jdn + 274277) / 146097) / 4) - 38;
    int e = f * 4 + 3;
    int g = (e % 1461) / 4;
    int h = 5 * g + 2;

    int d = (h % 153) / 5 + 1;
    int m = ((h / 153) + 2) % 12 + 1;
    int y = (e / 1461) - 4716 + (14 - m) / 12;

    int total_seconds = std::round(fractional_jdn * 86400);
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    return DateTime(y, m, d, hours, minutes, seconds);
}

DateTime DateTime::operator+(int days) const {
    return fromJulDay(toJulDay() + days);
}
DateTime DateTime::operator-(int days) const {
    return fromJulDay(toJulDay() - days);
}
int DateTime::operator-(const DateTime& other) const {
    return fabs((int)(toJulDay() - other.toJulDay()));
}
bool DateTime::operator==(const DateTime& r) const{
    return toJulDay() == r.toJulDay();
}
bool DateTime::operator!=(const DateTime& r) const {
    return toJulDay() != r.toJulDay();
}
bool DateTime::operator<(const DateTime& r) const {
    return toJulDay() < r.toJulDay();
}
bool DateTime::operator>(const DateTime& r) const {
    return toJulDay() > r.toJulDay();
}
bool DateTime::operator<=(const DateTime& r) const {
    return toJulDay() <= r.toJulDay();
}
bool DateTime::operator>=(const DateTime& r) const {
    return toJulDay() >= r.toJulDay();
}

ostream& operator<<(ostream& os, const DateTime& dt) {
    os << dt.year
       << "-" << setw(2) << setfill('0') << dt.month
       << "-" << setw(2) << setfill('0') << dt.day
       << "T" << setw(2) << setfill('0') << dt.hour
       << ":" << setw(2) << setfill('0') << dt.minute
       << ":" << setw(2) << setfill('0') << dt.second;
    return os;
}

istream& operator>>(std::istream& is, DateTime& dt) {
    int year, month, day, hour, minute, second;

    if (!(is >> year >> month >> day >> hour >> minute >> second)) {
        cerr << "Введите дату в формате: год час месяц день минута секунда" << endl;
        is.setstate(std::ios::failbit);
        return is;
    }

    DateTime tmp(year, month, day, hour, minute, second);

    if (!tmp.isValid()) {
        cerr << "Ошибка! Некорректная дата или время." << endl;
        is.setstate(std::ios::failbit);
        return is;
    }

    dt = tmp;
    return is;
}
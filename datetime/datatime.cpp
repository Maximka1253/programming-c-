#include "datatime.h"
#include <cctype>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

// Проверка корректности даты и времени.
bool DateTime::leapYear(int year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int DateTime::daysinMonth(int month, int year){
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return leapYear(year) ? 29:28;
        default: return -1;
    }
}

bool DateTime::isValidDateTime(int year, int month, int day,
        int hour, int minute, int second) {
    return month >= 1 && month <= 12 &&
           day >= 1 && day <= daysinMonth(month, year) &&
           hour >= 0 && hour <= 23 &&
           minute >= 0 && minute <= 59 &&
           second >= 0 && second <= 59;
}

void DateTime::printValidationError(int year, int month, int day,
        int hour, int minute, int second) {
    if (month < 1 || month > 12) {
        cerr << "Месяц должен быть от 1 до 12" << endl;
    } else if (day < 1 || day > daysinMonth(month, year)) {
        cerr << "В " << year << "/" << month << " не более "
             << daysinMonth(month, year) << " дней!!!" << endl;
    } else if (hour < 0 || hour > 23) {
        cerr << "В дне может быть только от 0 до 23 часа" << endl;
    } else if (minute < 0 || minute > 59) {
        cerr << "В часу от 0 до 59 минут" << endl;
    } else if (second < 0 || second > 59) {
        cerr << "В минуте от 0 до 59 секунд" << endl;
    }
}

DateTime DateTime::invalidCopy() const {
    DateTime result = *this;
    result.valid = false;
    return result;
}

// Получение дня недели.
int DateTime::getWeekDay() const {
    if (!isValid()) return -1;
    int jdn = static_cast<int>(toJulDay() + 0.5);
    return (jdn + 1) % 7;
}

std::string DateTime::getWeekDayName() const {
    static const std::string days[] = {"Воскресенье", "Понедельник", "Вторник",
        "Среда", "Четверг", "Пятница", "Суббота"};
    int weekDay = getWeekDay();
    if (weekDay < 0) return "Некорректная дата";
    return days[weekDay];
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
    : year(year), month(month), day(day), hour(hour), minute(minute), second(second), valid(false){
    valid = isValidDateTime(year, month, day, hour, minute, second);
    if (!valid) printValidationError(year, month, day, hour, minute, second);
}

// Изменение отдельных частей даты и времени.
void DateTime::setYear(int year) {
    if (month >= 1 && month <= 12 && day > daysinMonth(month, year)) {
        int maxDay = daysinMonth(month, year);
        cerr << "Нельзя установить год " << year << ", потому что в " << month << " месяце максимум " << maxDay << " дней" << endl;
        return;
    }

    this->year = year;
    valid = isValidDateTime(this->year, month, day, hour, minute, second);
}

void DateTime::setMonth(int month) {
    if (month < 1 || month > 12) {
        cerr << "Месяц должен быть от 1 до 12" << endl;
        return;
    }

    int maxDay = daysinMonth(month, year);
    if (day > maxDay) {
        cerr << "Нельзя установить месяц " << month << ", потому что в нем только " << maxDay << " дней" << endl;
        return;
    }
    this->month = month;
    valid = isValidDateTime(year, this->month, day, hour, minute, second);
}
void DateTime::setDay(int day) {
    if (month < 1 || month > 12) {
        cerr << "Нельзя установить день, пока месяц некорректен" << endl;
        return;
    }

    int maxDay = daysinMonth(month, year);

    if (day < 1 || day > maxDay) {
        cerr << "Для " << year << "/" << month
             << " день должен быть от 1 до " << maxDay << "\n";
        return;
    }
    this->day = day;
    valid = isValidDateTime(year, month, this->day, hour, minute, second);
}
void DateTime::setHour(int hour) {
    if (hour < 0 || hour > 23) {
        cerr << "Час должен быть от 0 до 23";
        return;
    }
    this->hour = hour;
    valid = isValidDateTime(year, month, day, this->hour, minute, second);
}

void DateTime::setMinute(int minute) {
    if (minute < 0 || minute > 59) {
        cerr << "Минута должна быть от 0 до 59";
        return;
    }
    this->minute = minute;
    valid = isValidDateTime(year, month, day, hour, this->minute, second);
}

void DateTime::setSecond(int second) {
    if (second < 0 || second > 59) {
        cerr << "Секунда должна быть от 0 до 59";
        return;
    }
    this->second = second;
    valid = isValidDateTime(year, month, day, hour, minute, this->second);
}

bool DateTime::isValid() const {
    return valid && isValidDateTime(year, month, day, hour, minute, second);
}

// Работа с началом суток и юлианской датой.
DateTime DateTime::startOfDay() const {
    if (!isValid()) return invalidCopy();
    return DateTime(year, month, day, 0, 0, 0);
}

double DateTime::toJulDay() const {
    if (!isValid()) {
        return std::numeric_limits<double>::quiet_NaN();
    }

    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;
    int jdn = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;

    double timeJD = (hour - 12) / 24.0 + minute / 1440.0 + second / 86400.0;
    return jdn + timeJD;
}

DateTime DateTime::fromJulDay(double jd) {
    if (!std::isfinite(jd)) {
        DateTime result;
        result.valid = false;
        return result;
    }

    jd += 0.5;

    int Z = static_cast<int>(std::floor(jd));
    double F = jd - Z;

    int a = Z + 32044;
    int b = (4 * a + 3) / 146097;
    int c = a - (146097 * b) / 4;
    int d = (4 * c + 3) / 1461;
    int e = c - (1461 * d) / 4;
    int m = (5 * e + 2) / 153;

    int day = e - (153 * m + 2) / 5 + 1;
    int month = m + 3 - 12 * (m / 10);
    int year = 100 * b + d - 4800 + (m / 10);

    int total_seconds = static_cast<int>(std::round(F * 86400));

    if (total_seconds >= 86400) {
        total_seconds -= 86400;
        day++;
        if (day > daysinMonth(month, year)) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }

    int hour = total_seconds / 3600;
    int minute = (total_seconds % 3600) / 60;
    int second = total_seconds % 60;

    return DateTime(year, month, day, hour, minute, second);
}

// Создание даты из формата файлов Moon: YYYYMMDD + HHMMSS.
DateTime DateTime::fromYmdHms(long ymd, const std::string& hms) {
    DateTime result;
    result.valid = false;

    std::string time = hms;

    while (time.length() < 6) time = "0" + time;

    if (time.length() != 6) return result;
    for (char symbol : time) {
        if (!std::isdigit(static_cast<unsigned char>(symbol))) return result;
    }

    int year = static_cast<int>(ymd / 10000);
    int month = static_cast<int>((ymd / 100) % 100);
    int day = static_cast<int>(ymd % 100);
    int hour = std::stoi(time.substr(0, 2));
    int minute = std::stoi(time.substr(2, 2));
    int second = std::stoi(time.substr(4, 2));

    if (!isValidDateTime(year, month, day, hour, minute, second)) return result;

    return DateTime(year, month, day, hour, minute, second);
}

// Арифметика и сравнение дат.
DateTime DateTime::operator+(int days) const {
    if (!isValid()) return invalidCopy();
    return fromJulDay(toJulDay() + days);
}
DateTime DateTime::operator-(int days) const {
    if (!isValid()) return invalidCopy();
    return fromJulDay(toJulDay() - days);
}
int DateTime::operator-(const DateTime& other) const {
    if (!isValid() || !other.isValid()) return 0;
    return static_cast<int>(toJulDay() - other.toJulDay());
}
bool DateTime::operator==(const DateTime& r) const {
    if (!isValid() || !r.isValid()) return false;
    return year == r.year &&
           month == r.month &&
           day == r.day &&
           hour == r.hour &&
           minute == r.minute &&
           second == r.second;
}

bool DateTime::operator!=(const DateTime& r) const {
    return !(*this == r);
}
bool DateTime::operator<(const DateTime& r) const {
    return isValid() && r.isValid() && toJulDay() < r.toJulDay();
}
bool DateTime::operator>(const DateTime& r) const {
    return isValid() && r.isValid() && toJulDay() > r.toJulDay();
}
bool DateTime::operator<=(const DateTime& r) const {
    return isValid() && r.isValid() && toJulDay() <= r.toJulDay();
}
bool DateTime::operator>=(const DateTime& r) const {
    return isValid() && r.isValid() && toJulDay() >= r.toJulDay();
}

// Расчет даты Пасхи.
DateTime DateTime::getEaster(const DateTime& date) {
    if (!date.isValid()) {
        return date.invalidCopy();
    }

    int year = date.getYear();
    int a = year % 4;
    int b = year % 7;
    int c = year % 19;
    int d = (19 * c + 15) % 30;
    int e = (2 * a + 4 * b - d + 34) % 7;

    int month = (d + e + 114) / 31;
    int day = ((d + e + 114) % 31) + 1;
    int shift = year / 100 - year / 400 - 2;

    day += shift;
    while (day > daysinMonth(month, year)) {
        day -= daysinMonth(month, year);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }

    return DateTime(year, month, day, 0, 0, 0);
}

// Ввод и вывод даты-времени.
ostream& operator<<(ostream& os, const DateTime& dt) {
    if (!dt.isValid()) {
        os << "Invalid DateTime";
        return os;
    }

    char oldFill = os.fill('0');
    os << dt.year
       << "-" << setw(2) << dt.month
       << "-" << setw(2) << dt.day
       << "T" << setw(2) << dt.hour
       << ":" << setw(2) << dt.minute
       << ":" << setw(2) << dt.second;
    os.fill(oldFill);
    return os;
}

istream& operator>>(istream& is, DateTime& dt) {
    int year, month, day, hour, minute, second;

    if (!(is >> year >> month >> day >> hour >> minute >> second)) return is;

    DateTime temp(year, month, day, hour, minute, second);
    if (!temp.isValid()) is.setstate(ios::failbit);
    else dt = temp;

    return is;
}
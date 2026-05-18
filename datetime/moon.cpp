#include "moon.h"
#include <fstream>
#include <limits>
#include <sstream>

using namespace std;

namespace {

struct MoonPoint {
    DateTime time;
    double elevation = 0.0;
};

ifstream openMoonFile(int year) {
    const string filePath = "Moon/moon" + to_string(year) + ".dat";
    return ifstream(filePath);
}

bool parseMoonLine(const string& line, MoonPoint& point) {
    if (line.empty()) return false;

    long ymd;
    string hms;
    double value1, value2, value3, value4, value5, value6;
    istringstream stream(line);

    if (!(stream >> ymd >> hms >> value1 >> value2 >> value3 >> value4 >> value5)) {
        return false;
    }

    // В файлах может быть 5 или 6 числовых колонок после даты и времени.
    const double elevation = (stream >> value6) ? value3 : value2;

    point.time = DateTime::fromYmdHms(ymd, hms);
    if (!point.time.isValid()) return false;

    point.elevation = elevation;
    return true;
}

}

Moon::Moon() : dt() {
}

Moon::Moon(const DateTime& dateTime) : dt(dateTime) {
}

MoonResult Moon::calculate() const {
    MoonResult result;
    result.date = dt;

    ifstream file = openMoonFile(dt.getYear());
    if (!file.is_open()) return result;
    result.fileOpened = true;

    string line;
    getline(file, line);

    DateTime dayBegin = dt.startOfDay();
    DateTime dayEnd = dayBegin + 1;

    double maxElevation = numeric_limits<double>::lowest();

    double prevElevation = 0;
    bool hasPrev = false;

    while (getline(file, line)) {
        MoonPoint point;

        if (!parseMoonLine(line, point)) continue;

        if (point.time >= dayEnd) break;

        if (point.time < dayBegin) {
            // Нужна последняя точка перед началом дня.
            prevElevation = point.elevation;
            hasPrev = true;
            continue;
        }

        if (hasPrev) {
            // Переход через 0 градусов означает восход или заход.
            if (prevElevation < 0 && point.elevation >= 0) {
                result.rise = point.time;
                result.hasRise = true;
            }

            if (prevElevation > 0 && point.elevation <= 0) {
                result.set = point.time;
                result.hasSet = true;
            }
        }

        if (point.elevation > maxElevation) {
            maxElevation = point.elevation;
            result.culmination = point.time;
            result.hasCulmination = true;
        }

        prevElevation = point.elevation;
        hasPrev = true;
    }

    return result;
}
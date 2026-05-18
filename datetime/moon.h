#ifndef MOON_H
#define MOON_H

#include "datatime.h"

struct MoonResult {
    DateTime date;
    DateTime rise;
    DateTime culmination;
    DateTime set;
    bool hasRise = false;
    bool hasCulmination = false;
    bool hasSet = false;
    bool fileOpened = false;
};

class Moon {
    DateTime dt;

public:
    Moon();
    explicit Moon(const DateTime& dateTime);

    MoonResult calculate() const;
};

#endif
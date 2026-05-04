#ifndef MOON_H
#define MOON_H

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include "datatime.h"

inline std::ifstream openMoonFile(int year) {
    std::string filePath = "Moon/moon" + std::to_string(year) + ".dat";
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл: " << filePath << std::endl;
    }

    return file;
}

inline long getYMD(const DateTime& dt) {
    return dt.getYear() * 10000 + dt.getMonth() * 100 + dt.getDay();
}

inline bool parseLine(const std::string& line, long& ymd, std::string& time, double& elevation) {
    if (line.empty()) return false;

    long tmpYmd;
    char hms[7];
    double c1, c2, c3, c4, c5, c6;
    int parsed = std::sscanf(line.c_str(), "%ld %6s %lf %lf %lf %lf %lf %lf",
                             &tmpYmd, hms, &c1, &c2, &c3, &c4, &c5, &c6);
    if (parsed != 7 && parsed != 8) return false;

    std::string hmsStr = hms;

    if (hmsStr.length() == 5) hmsStr = "0" + hmsStr;

    time = hmsStr.substr(0, 2) + ":" + hmsStr.substr(2, 2) + ":" + hmsStr.substr(4, 2); // разделение времени

    ymd = tmpYmd;
    elevation = (parsed == 7) ? c2 : c3;

    return true;
}

class Moon {
    DateTime dt;

public:
    Moon();
    void calculate();
    void printResults(const std::string& rise, const std::string& culm, const std::string& set);
};

inline Moon::Moon() {
    std::cout << "Введите дату: ГОД МЕСЯЦ ДЕНЬ ЧАС МИНУТА СЕКУНДА" << std::endl;

    while (!(std::cin >> dt)) {
        std::cout << "Ошибка ввода! Попробуйте снова." << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

inline void Moon::calculate() {
    std::ifstream file = openMoonFile(dt.getYear());
    if (!file.is_open()) return;

    std::string line;
    std::getline(file, line);

    long targetYmd = getYMD(dt);

    std::string riseTime = "нет", setTime = "нет", culmTime = "нет";

    double maxElevation = -1e9;
    double prevElevation = 0;
    bool hasPrev = false;

    while (std::getline(file, line)) {
        long currentYmd;
        std::string currentTime;
        double currentElevation;

        if (!parseLine(line, currentYmd, currentTime, currentElevation)) continue;

        if (currentYmd > targetYmd) break;
        if (currentYmd < targetYmd) continue;

        // Восход / заход
        if (hasPrev) {
            if (prevElevation < 0 && currentElevation >= 0)
                riseTime = currentTime;

            if (prevElevation > 0 && currentElevation <= 0)
                setTime = currentTime;
        }

        // Кульминация
        if (currentElevation > maxElevation) {
            maxElevation = currentElevation;
            culmTime = currentTime;
        }

        prevElevation = currentElevation;
        hasPrev = true;
    }

    printResults(riseTime, culmTime, setTime);
}

inline void Moon::printResults(const std::string& rise, const std::string& culm, const std::string& set) {
    std::cout << std::endl;
    std::cout << "Дата: " << dt << std::endl;
    std::cout << "Восход Луны: " << rise << std::endl;
    std::cout << "Кульминация Луны: " << culm << std::endl;
    std::cout << "Заход Луны: " << set << std::endl;
}

#endif

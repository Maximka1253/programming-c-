#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "datatime.h"

using namespace std;

ifstream openMoonFile(int year) {
    string filePath = "Moon/moon" + to_string(year) + ".dat";
    ifstream file(filePath);

    if (!file.is_open()) {
        cout << "Не удалось открыть файл: " << filePath << endl;
    }

    return file;
}

long getYMD(const DateTime& dt) {
    return dt.getYear() * 10000 + dt.getMonth() * 100 + dt.getDay();
}

bool parseLine(const string& line, long& ymd, string& time, double& elevation) {
    if (line.empty()) return false;

    long tmpYmd;
    char hms[7];
    double tempT, tempR, el, az, fi, lg;


    if (sscanf(line.c_str(), "%ld %6s %lf %lf %lf %lf %lf %lf",       //распределение строчек по переменным
               &tmpYmd, hms, &tempT, &tempR, &el, &az, &fi, &lg) != 8)
        return false;

    string hmsStr = hms;

    if (hmsStr.length() == 5) hmsStr = "0" + hmsStr;

    time = hmsStr.substr(0, 2) + ":" + hmsStr.substr(2, 2) + ":" + hmsStr.substr(4, 2); // резделение времени

    ymd = tmpYmd;
    elevation = el;

    return true;
}

class Moon {
    DateTime dt;

public:
    Moon() {
        cout << "Введите дату: ГОД МЕСЯЦ ДЕНЬ ЧАС МИНУТА СЕКУНДА" << endl;

        while (!(cin >> dt)) {
            cout << "Ошибка ввода! Попробуйте снова." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    void calculate() {
        ifstream file = openMoonFile(dt.getYear());
        if (!file.is_open()) return;

        string line;
        getline(file, line);

        long targetYmd = getYMD(dt);

        string riseTime = "нет", setTime = "нет", culmTime = "нет";

        double maxElevation = -1e9;
        double prevElevation = 0;
        bool hasPrev = false;

        while (getline(file, line)) {
            long currentYmd;
            string currentTime;
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

    void printResults(const string& rise, const string& culm, const string& set) {
        cout << endl;
        cout << "Дата: " << dt << endl;
        cout << "Восход Луны: " << rise << endl;
        cout << "Кульминация Луны: " << culm << endl;
        cout << "Заход Луны: " << set << endl;
    }
};

int main() {
    clock_t startTime = clock();

    Moon moonObj;
    moonObj.calculate();

    clock_t endTime = clock();

    double executionTime = double(endTime - startTime) / CLOCKS_PER_SEC;

    cout << endl;
    cout << "Время выполнения: " << executionTime << " сек" << endl;

    return 0;
}
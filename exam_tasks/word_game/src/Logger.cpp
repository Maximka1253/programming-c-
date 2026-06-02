#include "Logger.h"
#include <filesystem>

using namespace std;
// Логгер для записи хода игры в файл.
bool Logger::open(const string& filename) {
    filesystem::path path(filename);
    filesystem::path parent = path.parent_path();

    if (!parent.empty()) {
        filesystem::create_directories(parent);
    }

    file.open(filename.c_str());
    return file.is_open();
}

void Logger::write(const string& message) {
    if (file.is_open()) {
        file << message << "\n";
    }
}

void Logger::logStart(const vector<Player>& players, const string& startWord) {
    // Записываем начало игры.
    if (!file.is_open()) {
        return;
    }

    file << "Начало игры\n";
    file << "Стартовое слово: " << startWord << "\n";
    file << "Игроки:\n";

    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        file << "- " << players[i].getName() << "\n";
    }

    file << "\n";
    file.flush();
}

void Logger::logMove(int moveNumber, const Player& player, const Move& move, const string& result) {
    // Записываем один ход.
    if (!file.is_open()) {
        return;
    }

    file << "Номер хода: " << moveNumber << "\n";
    file << "Ход игрока: " << player.getName() << "\n";

    if (move.pass) {
        file << "Действие: пропуск\n";
    } else {
        file << "Добавленная буква: " << move.addedLetter << "\n";
        file << "Координаты: (" << move.addedPosition.row << ", " << move.addedPosition.col << ")\n";
        file << "Слово: " << move.word << "\n";
        file << "Проверка слова\n";
    }

    file << "Результат: " << result << "\n\n";
    file.flush();
}

void Logger::logEnd(const vector<Player>& players, const string& result) {
    // Записываем итоги игры.
    if (!file.is_open()) {
        return;
    }

    file << "Конец игры\n";
    file << "Итоговые очки:\n";

    for (int i = 0; i < static_cast<int>(players.size()); i++) {
        file << "- " << players[i].getName() << ": " << players[i].getScore() << "\n";
    }

    file << "Финальный результат: " << result << "\n";
    file.flush();
}

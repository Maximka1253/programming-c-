#ifndef WORD_GAME_RUSSIAN_TEXT_H
#define WORD_GAME_RUSSIAN_TEXT_H

#include <string>
#include <vector>

class RussianText {
private:
    RussianText() = delete;

public:
    static std::string normalizeRussianWord(const std::string& text);
    static std::string normalizeRussianSpelling(const std::string& text);
    static bool containsOnlyRussianLetters(const std::string& text);
    static std::vector<std::string> splitRussianLetters(const std::string& text);
    static int getRussianLetterCount(const std::string& text);
    static bool isSingleRussianLetter(const std::string& text);
};

#endif //WORD_GAME_RUSSIAN_TEXT_H

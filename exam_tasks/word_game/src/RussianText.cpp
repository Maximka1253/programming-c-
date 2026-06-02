#include "RussianText.h"

static std::string normalizeRussianLetter(const std::string& letter, bool replaceYo) {
    if (letter == "ё" || letter == "Ё") {
        return replaceYo ? "е" : "ё";
    }

    const std::string lowerLetters[] = {
        "а", "б", "в", "г", "д", "е", "ж", "з", "и", "й", "к",
        "л", "м", "н", "о", "п", "р", "с", "т", "у", "ф", "х",
        "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"
    };

    const std::string upperLetters[] = {
        "А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "Й", "К",
        "Л", "М", "Н", "О", "П", "Р", "С", "Т", "У", "Ф", "Х",
        "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я"
    };

    const int lettersCount = 32;
    for (int i = 0; i < lettersCount; i++) {
        if (letter == lowerLetters[i] || letter == upperLetters[i]) {
            return lowerLetters[i];
        }
    }

    return "";
}

std::string RussianText::normalizeRussianWord(const std::string& text) {
    std::string normalized;
    for (size_t i = 0; i < text.length(); i += 2) {
        normalized += normalizeRussianLetter(text.substr(i, 2), true);
    }

    return normalized;
}

std::string RussianText::normalizeRussianSpelling(const std::string& text) {
    std::string normalized;
    for (size_t i = 0; i < text.length(); i += 2) {
        normalized += normalizeRussianLetter(text.substr(i, 2), false);
    }

    return normalized;
}

bool RussianText::containsOnlyRussianLetters(const std::string& text) {
    if (text.empty() || text.length() % 2 != 0) {
        return false;
    }

    for (size_t i = 0; i < text.length(); i += 2) {
        if (normalizeRussianLetter(text.substr(i, 2), false).empty()) {
            return false;
        }
    }

    return true;
}

std::vector<std::string> RussianText::splitRussianLetters(const std::string& text) {
    std::vector<std::string> letters;
    for (size_t i = 0; i < text.length(); i += 2) {
        std::string letter = normalizeRussianLetter(text.substr(i, 2), true);
        if (!letter.empty()) {
            letters.push_back(letter);
        }
    }

    return letters;
}

int RussianText::getRussianLetterCount(const std::string& text) {
    return static_cast<int>(splitRussianLetters(text).size());
}

bool RussianText::isSingleRussianLetter(const std::string& text) {
    return containsOnlyRussianLetters(text) && getRussianLetterCount(text) == 1;
}

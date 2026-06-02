#include "Dictionary.h"
#include "RussianText.h"
#include <fstream>

using namespace std;

bool Dictionary::loadFromFile(const string& filename) {
    // Загружаем слова из файла.
    ifstream file(filename.c_str());

    if (!file.is_open()) {
        return false;
    }

    words.clear();
    spellings.clear();

    string word;
    while (file >> word) {
        if (RussianText::containsOnlyRussianLetters(word)) {
            words.push_back(normalize(word));
            spellings.push_back(RussianText::normalizeRussianSpelling(word));
        }
    }

    return true;
}

bool Dictionary::contains(const string& word) const {
    // Ищем слово в словаре.
    if (!RussianText::containsOnlyRussianLetters(word)) {
        return false;
    }

    string normalizedWord = normalize(word);
    string normalizedSpelling = RussianText::normalizeRussianSpelling(word);
    bool inputHasYo = normalizedSpelling.find("ё") != string::npos;

    for (int i = 0; i < static_cast<int>(words.size()); i++) {
        if (spellings[i] == normalizedSpelling) {
            return true;
        }

        if (!inputHasYo && words[i] == normalizedWord) {
            return true;
        }
    }

    return false;
}

string Dictionary::normalize(const string& word) const {
    // Приводим русское слово к единому виду: нижний регистр, ё -> е.
    return RussianText::normalizeRussianWord(word);
}

const vector<string>& Dictionary::getWords() const {
    return words;
}

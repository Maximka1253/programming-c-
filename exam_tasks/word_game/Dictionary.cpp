#include "Dictionary.h"
#include <cctype>
#include <fstream>

using namespace std;

bool Dictionary::loadFromFile(const string& filename) {
    // Загружаем слова из файла.
    ifstream file(filename.c_str());

    if (!file.is_open()) {
        return false;
    }

    words.clear();

    string word;
    while (file >> word) {
        word = normalize(word);
        if (!word.empty()) {
            words.push_back(word);
        }
    }

    return true;
}

bool Dictionary::contains(const string& word) const {
    // Ищем слово в словаре.
    string normalizedWord = normalize(word);

    for (int i = 0; i < static_cast<int>(words.size()); i++) {
        if (words[i] == normalizedWord) {
            return true;
        }
    }

    return false;
}

string Dictionary::normalize(const string& word) const {
    // Приводим слово к нижнему регистру.
    string result = "";

    for (int i = 0; i < static_cast<int>(word.length()); i++) {
        char ch = static_cast<char>(tolower(static_cast<unsigned char>(word[i])));
        result += ch;
    }

    return result;
}

const vector<string>& Dictionary::getWords() const {
    return words;
}

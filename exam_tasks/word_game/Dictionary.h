#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Dictionary {
private:
    vector<string> words;

public:
    bool loadFromFile(const string& filename);
    bool contains(const string& word) const;
    string normalize(const string& word) const;
    const vector<string>& getWords() const;
};

#endif

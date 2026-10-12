#ifndef LANGUAGEMODEL_H
#define LANGUAGEMODEL_H

#include <map>
#include <iostream>
#include <set>
#include <string>

class LanguageModel {
public:
    LanguageModel(int k, const std::string& filename);
    int k() const;
    const std::map<std::string, int>& kgramCounts() const;
    const std::map<char, int>& nextCharCounts(const std::string& kgram) const;
    const std::set<char>& alphabet() const;
    void print(std::ostream& out) const;
private:
    int k_;
    std::map<std::string, int> kgramCount_;
    std::map<std::string, std::map<char, int>> nextCharCount_;
    std::set<char> alphabet_;

    void train(const std::string& text);
};

#endif

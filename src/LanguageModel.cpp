#include "LanguageModel.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

LanguageModel::LanguageModel(int k, const std::string& filename) : k_(k) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("cannot open file '" + filename + "'");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    train(buffer.str());
}

void LanguageModel::train(const std::string& text) {
    // Alphabet: every distinct character in the text
    for (char c : text) {
        alphabet_.insert(c);
    }

    const std::size_t k = static_cast<std::size_t>(k_);

    // Slide a window of length k over the text
    for (std::size_t i = 0; i + k <= text.size(); ++i) {
        std::string kgram = text.substr(i, k);
        ++kgramCount_[kgram];

        // If there is a character after this window, count it
        if (i + k < text.size()) {
            ++nextCharCount_[kgram][text[i + k]];
        }
    }
}

int LanguageModel::k() const {
    return k_;
}

const std::map<std::string, int>& LanguageModel::kgramCounts() const {
    return kgramCount_;
}

const std::map<char, int>& LanguageModel::nextCharCounts(const std::string& kgram) const {
    static const std::map<char, int> empty;
    auto it = nextCharCount_.find(kgram);
    if (it == nextCharCount_.end()) {
        return empty;
    }
    return it->second;
}

const std::set<char>& LanguageModel::alphabet() const {
    return alphabet_;
}

void LanguageModel::print(std::ostream& out) const {
    int total = 0;
    for (const auto& entry : kgramCount_) {
        total += entry.second;
    }

    out << "k-gram counts (total " << total << "):\n";
    for (const auto& entry : kgramCount_) {
        out << "  \"" << entry.first << "\"  " << entry.second
            << "  f = " << static_cast<double>(entry.second) / total << '\n';
    }

    out << "transitions:\n";
    for (const auto& entry : nextCharCount_) {
        for (const auto& next : entry.second) {
            out << "  \"" << entry.first << "\" -> '" << next.first
                << "'  " << next.second << '\n';
        }
    }
}

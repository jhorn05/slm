#include "TextGenerator.h"

#include <vector>

TextGenerator::TextGenerator(const LanguageModel& model)
    : model_(model), rng_(std::random_device{}()) {}

std::string TextGenerator::chooseStart() {
    std::vector<std::string> kgrams;
    std::vector<int> weights;
    for (const auto& entry : model_.kgramCounts()) {
        kgrams.push_back(entry.first);
        weights.push_back(entry.second);
    }

    std::discrete_distribution<std::size_t> dist(weights.begin(), weights.end());
    return kgrams[dist(rng_)];
}

std::string TextGenerator::generate(int length) {
    std::string output = chooseStart();
    std::string current = output;
    const std::size_t target = static_cast<std::size_t>(length);

    while (output.size() < target) {
        const std::map<char, int>& counts = model_.nextCharCounts(current);
        if (counts.empty()) {
            break;
        }

        std::vector<char> chars;
        std::vector<int> weights;
        for (const auto& entry : counts) {
            chars.push_back(entry.first);
            weights.push_back(entry.second);
        }

        std::discrete_distribution<std::size_t> dist(weights.begin(), weights.end());
        char next = chars[dist(rng_)];

        output += next;
        current = current.substr(1) + next;
    }
    return output;
}


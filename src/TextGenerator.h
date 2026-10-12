#ifndef TEXTGENERATOR_H
#define TEXTGENERATOR_H

#include <random>
#include <string>

#include "LanguageModel.h"

class TextGenerator {
public:
    explicit TextGenerator(const LanguageModel& model);
    std::string generate(int length);

private:
    const LanguageModel& model_;
    std::mt19937 rng_;

    std::string chooseStart();
};

#endif

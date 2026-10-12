#ifndef TEXTGENERATOR_H
#define TEXTGENERATOR_H

#include <random>
#include <string>

#include "LanguageModel.h"

class TextGenerator {
public:
    TextGenerator(const LanguageModel& model, double alpha);
    std::string generate(int length);

private:
    const LanguageModel& model_;
    double alpha_;
    std::mt19937 rng_;

    std::string chooseStart();
};

#endif

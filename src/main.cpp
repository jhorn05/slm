#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

struct Arguments {
    double alpha = 0.0;     
    int k = 0;
    std::string filename;
    int length = 0;
};

const std::string USAGE = "usage: slm [-a pseudocount] k file length";

int parsePositiveInt(const std::string& text, const std::string& name) {
    std::size_t pos = 0;
    int value = 0;
    try {
        value = std::stoi(text, &pos);
    } catch (const std::exception&) {
        throw std::invalid_argument(name + " must be a positive integer, got '" + text + "'");
    }
    if (pos != text.size() || value <= 0) {
        throw std::invalid_argument(name + " must be a positive integer, got '" + text + "'");
    }
    return value;
}

double parseNonNegativeDouble(const std::string& text, const std::string& name) {
    std::size_t pos = 0;
    double value = 0.0;
    try {
        value = std::stod(text, &pos);
    } catch (const std::exception&) {
        throw std::invalid_argument(name + " must be a non-negative number, got '" + text + "'");
    }
    if (pos != text.size() || value < 0 || !std::isfinite(value)) {
        throw std::invalid_argument(name + " must be a non-negative number, got '" + text + "'");
    }
    return value;
}

Arguments parseArguments(int argc, char* argv[]) {
    Arguments args;
    int first = 1;

    if (argc > 1 && std::string(argv[1]) == "-a") {
        if (argc < 3) {
            throw std::invalid_argument("option -a requires a number (" + USAGE + ")");
        }
        args.alpha = parseNonNegativeDouble(argv[2], "pseudocount");
        first = 3;
    } else if (argc > 1 && argv[1][0] == '-' &&
               !std::isdigit(static_cast<unsigned char>(argv[1][1]))) {
        throw std::invalid_argument("unknown option '" + std::string(argv[1]) + "' (" + USAGE + ")");
    }

    if (argc - first != 3) {
        throw std::invalid_argument("wrong number of arguments (" + USAGE + ")");
    }

    args.k = parsePositiveInt(argv[first], "k");
    args.filename = argv[first + 1];
    args.length = parsePositiveInt(argv[first + 2], "length");

    if (args.length < args.k) {
        throw std::invalid_argument("length must be at least k");
    }
    return args;
}

int main(int argc, char* argv[]) {
    try {
        Arguments args = parseArguments(argc, argv);

        std::cout << "alpha  = " << args.alpha << '\n'
                  << "k      = " << args.k << '\n'
                  << "file   = " << args.filename << '\n'
                  << "length = " << args.length << '\n';
    } catch (const std::exception& e) {
        std::cerr << "slm: " << e.what() << '\n';
        return 1;
    }
    return 0;
}

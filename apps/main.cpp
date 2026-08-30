#include "calculator/Calculator.hpp"

#include <iostream>
#include <string>

namespace {

void PrintUsage(const char* programName) {
    std::cout << "Usage: " << programName << " <a> <op> <b>\n"
              << "  op is one of: + - * /\n"
              << "  Example: " << programName << " 4 + 5\n";
}

}  // namespace

int main(int argc, char* argv[]) {
    if (argc != 4) {
        PrintUsage(argv[0]);
        return 1;
    }

    double a = 0.0;
    double b = 0.0;
    std::string op = argv[2];

    try {
        a = std::stod(argv[1]);
        b = std::stod(argv[3]);
    } catch (const std::exception&) {
        std::cerr << "Error: '" << argv[1] << "' and '" << argv[3]
                  << "' must be numbers.\n";
        return 1;
    }

    calc::Calculator calculator;
    double result = 0.0;

    try {
        if (op == "+") {
            result = calculator.Add(a, b);
        } else if (op == "-") {
            result = calculator.Subtract(a, b);
        } else if (op == "*") {
            result = calculator.Multiply(a, b);
        } else if (op == "/") {
            result = calculator.Divide(a, b);
        } else {
            std::cerr << "Error: unknown operator '" << op << "'.\n";
            PrintUsage(argv[0]);
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    std::cout << a << " " << op << " " << b << " = " << result << "\n";
    return 0;
}
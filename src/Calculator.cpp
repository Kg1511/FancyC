#include "calculator/Calculator.hpp"

#include <stdexcept>

namespace calc {

double Calculator::Add(double a, double b) const {
    return a + b;
}

double Calculator::Subtract(double a, double b) const {
    return a - b;
}

double Calculator::Multiply(double a, double b) const {
    return a * b;
}

double Calculator::Divide(double a, double b) const {
    if (b == 0.0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}

}  // namespace calc

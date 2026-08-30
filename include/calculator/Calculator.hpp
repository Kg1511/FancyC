#pragma once

namespace calc {

// Simple stateless arithmetic operations. Public API used by consumers.
class Calculator {
public:
    double Add(double a, double b) const;
    double Subtract(double a, double b) const;
    double Multiply(double a, double b) const;

    // Throws std::invalid_argument if b == 0.
    double Divide(double a, double b) const;
};

}  // namespace calc

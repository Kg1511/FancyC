# API Reference

## `calc::Calculator`

Defined in `include/calculator/Calculator.hpp`. Stateless class providing
basic arithmetic operations. Since it holds no internal state, a single
instance is safe to reuse across multiple calls, including from multiple
threads.

### Including it in your own code

    #include "calculator/Calculator.hpp"

    calc::Calculator calculator;
    double sum = calculator.Add(2, 3);

If linking via CMake, depend on the `calculator` target:

    target_link_libraries(your_target PRIVATE calculator)

### `double Add(double a, double b) const`

Returns `a + b`.

### `double Subtract(double a, double b) const`

Returns `a - b`.

### `double Multiply(double a, double b) const`

Returns `a * b`.

### `double Divide(double a, double b) const`

Returns `a / b`.

**Throws:** `std::invalid_argument` if `b == 0`.

Example:

    try {
        double result = calculator.Divide(10, 0);
    } catch (const std::invalid_argument& e) {
        // e.what() == "Division by zero"
    }

---

## CLI application (`calculator_app`)

Defined in `apps/main.cpp`. Thin command-line wrapper around `Calculator`.

### Usage

    calculator_app <a> <op> <b>

| Argument | Description |
|---|---|
| `a` | First number |
| `op` | One of `+`, `-`, `*`, `/` |
| `b` | Second number |

### Examples

    $ calculator_app 4 + 5
    4 + 5 = 9

    $ calculator_app 10 / 3
    10 / 3 = 3.33333

    $ calculator_app 6 / 0
    Error: Division by zero

### Exit codes

| Code | Meaning |
|---|---|
| `0` | Success |
| `1` | Invalid arguments, unknown operator, non-numeric input, or a runtime error (e.g. division by zero) | 
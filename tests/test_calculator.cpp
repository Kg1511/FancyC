#include "calculator/Calculator.hpp"

#include <gtest/gtest.h>

TEST(CalculatorTest, Add) {
    calc::Calculator c;
    EXPECT_EQ(c.Add(2, 3), 5);
}

TEST(CalculatorTest, Subtract) {
    calc::Calculator c;
    EXPECT_EQ(c.Subtract(5, 3), 2);
}

TEST(CalculatorTest, Multiply) {
    calc::Calculator c;
    EXPECT_EQ(c.Multiply(4, 3), 12);
}

TEST(CalculatorTest, DivideNormal) {
    calc::Calculator c;
    EXPECT_DOUBLE_EQ(c.Divide(10, 2), 5.0);
}

TEST(CalculatorTest, DivideByZeroThrows) {
    calc::Calculator c;
    EXPECT_THROW(c.Divide(1, 0), std::invalid_argument);
}

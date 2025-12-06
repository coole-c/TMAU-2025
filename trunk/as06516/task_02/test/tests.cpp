#include <gtest/gtest.h>
#include "functions.h"
#include <cmath>

TEST(LinearModel, BasicCalculation) {
    EXPECT_DOUBLE_EQ(linear(10.0, 5.0), 0.92 * 10.0 + 0.08 * 5.0);
}

TEST(LinearModel, ZeroInputs) {
    EXPECT_DOUBLE_EQ(linear(0.0, 0.0), 0.0);
}

TEST(LinearModel, OnlyState) {
    EXPECT_DOUBLE_EQ(linear(15.5, 0.0), a * 15.5);
}

TEST(LinearModel, OnlyInput) {
    EXPECT_DOUBLE_EQ(linear(0.0, 8.3), b_lin * 8.3);
}

TEST(LinearModel, NegativeValues) {
    EXPECT_DOUBLE_EQ(linear(-5.0, -3.0), a * (-5.0) + b_lin * (-3.0));
}

TEST(LinearModel, FractionalValues) {
    double result = linear(2.75, 4.125);
    double expected = 0.92 * 2.75 + 0.08 * 4.125;
    EXPECT_NEAR(result, expected, 1e-12);
}

TEST(NonlinearModel, BasicCalculation) {
    double result = nonlinear(12.0, 8.0, 6.0, 4.0);
    double expected = a * 12.0 - b_non * 8.0 * 8.0 + c * 6.0 + d * std::sin(4.0);
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(NonlinearModel, AllZeros) {
    EXPECT_DOUBLE_EQ(nonlinear(0.0, 0.0, 0.0, 0.0), 0.0);
}

TEST(NonlinearModel, OnlyCurrentState) {
    EXPECT_DOUBLE_EQ(nonlinear(9.5, 0.0, 0.0, 0.0), a * 9.5);
}

TEST(NonlinearModel, OnlyPreviousState) {
    EXPECT_DOUBLE_EQ(nonlinear(0.0, 7.2, 0.0, 0.0), -b_non * 7.2 * 7.2);
}

TEST(NonlinearModel, OnlyInputs) {
    double result = nonlinear(0.0, 0.0, 3.0, 1.57);
    double expected = c * 3.0 + d * std::sin(1.57);
    EXPECT_NEAR(result, expected, 1e-12);
}

TEST(NonlinearModel, NegativeInputs) {
    double result = nonlinear(4.0, 2.0, 3.0, 1.0);
    double expected = a * 4.0 - b_non * 2.0 * 2.0 + c * 3.0 + d * std::sin(1.0);
    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(NonlinearModel, HighPrecision) {
    double yt = 1.234567;
    double yt1 = 9.876543;
    double ut = 2.718281;
    double ut1 = 3.141592;
    
    double result = nonlinear(yt, yt1, ut, ut1);
    double expected = a * yt - b_non * yt1 * yt1 + c * ut + d * std::sin(ut1);
    EXPECT_NEAR(result, expected, 1e-10);
}

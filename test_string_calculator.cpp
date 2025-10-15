#include <gtest/gtest.h>
#include "string_calculator.h"

TEST(AddFunctionTests, EmptyString) {
    const char* input = "";
    AddResult result = add(input);
    EXPECT_EQ(result.sum, 0);
    EXPECT_EQ(result.negative_count, 0);
}

TEST(AddFunctionTests, SingleNumber) {
    const char* input = "5";
    AddResult result = add(input);
    EXPECT_EQ(result.sum, 5);
    EXPECT_EQ(result.negative_count, 0);
}

TEST(AddFunctionTests, MultipleNumbers) {
    const char* input = "5,10,15";
    AddResult result = add(input);
    EXPECT_EQ(result.sum, 30);
    EXPECT_EQ(result.negative_count, 0);
}

TEST(AddFunctionTests, NegativeNumbers) {
    const char* input = "5,-10,15,-3";
    AddResult result = add(input);
    EXPECT_EQ(result.sum, 0);
    EXPECT_EQ(result.negative_count, 2);
    EXPECT_EQ(result.negatives[0], -10);
    EXPECT_EQ(result.negatives[1], -3);
}

// Test the case with custom delimiters.
TEST(AddFunctionTests, CustomDelimiters) {
    const char* input = "//[;]\n5;10;15";
    AddResult result = add(input);
    EXPECT_EQ(result.sum, 30);
    EXPECT_EQ(result.negative_count, 0);
}

TEST(AddFunctionTests, NumbersAbove1000) {
    const char* input = "5,1001,2000,10";
    AddResult result = add(input);
    EXPECT_EQ(result.sum, 15);  // 1001 and 2000 are ignored
    EXPECT_EQ(result.negative_count, 0);
}

TEST(AddFunctionTests, MultiCharacterDelimiters) {
    const char* input = "//[***]\n1***2***3";
    AddResult result = add(input);
    EXPECT_EQ(result.sum, 6);
    EXPECT_EQ(result.negative_count, 0);
}

TEST(AddFunctionTests, EdgeDelimiters) {
    const char* input = "//[****][%%%%]\n5****10%%%%15";
    AddResult result = add(input);
    EXPECT_EQ(result.sum, 30);
    EXPECT_EQ(result.negative_count, 0);
}

TEST(AddFunctionTests, InvalidChars) {
    const char* input = "5,$,10,a,15";
    AddResult result = add(input);
    EXPECT_EQ(result.sum, 30);
    EXPECT_EQ(result.negative_count, 0);
}

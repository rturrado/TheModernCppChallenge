#include "chapter_01_math/problem_006_abundant_numbers.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream
#include <vector>

using namespace tmcppc::problem_6;


TEST(abundant_numbers_up_to, limit_0) {
    EXPECT_TRUE(abundant_numbers_up_to(0).empty());
}

TEST(abundant_numbers_up_to, limit_30) {
    EXPECT_THAT(abundant_numbers_up_to(30), ::testing::ElementsAre(
        AbundantNumberResult{ 12, 4, { 1, 2, 3, 4, 6 } },
        AbundantNumberResult{ 18, 3, { 1, 2, 3, 6, 9 } },
        AbundantNumberResult{ 20, 2, { 1, 2, 4, 5, 10 } },
        AbundantNumberResult{ 24, 12, { 1, 2, 3, 4, 6, 8, 12 } },
        AbundantNumberResult{ 30, 12, { 1, 2, 3, 5, 6, 10, 15 } }
    ));
}

TEST(program_6_main, limit_7) {
    std::istringstream iss{ "7\n" };
    std::ostringstream oss{};
    problem_6_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Abundant numbers up to 7 [list of divisors] (and their abundance):\n"
        "\t[]\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}

TEST(program_6_main, limit_30) {
    std::istringstream iss{ "30\n" };
    std::ostringstream oss{};
    problem_6_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Abundant numbers up to 30 [list of divisors] (and their abundance):\n"
        "\t12 [1, 2, 3, 4, 6] (4)\n"
        "\t18 [1, 2, 3, 6, 9] (3)\n"
        "\t20 [1, 2, 4, 5, 10] (2)\n"
        "\t24 [1, 2, 3, 4, 6, 8, 12] (12)\n"
        "\t30 [1, 2, 3, 5, 6, 10, 15] (12)\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}

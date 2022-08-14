#include "chapter_06_algorithms_and_data_structures/problem_053_average_rating_of_movies.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cmath>  // fabs
#include <sstream>  // ostringstream

using namespace tmcppc::problem_53;


bool simple_compare_doubles(double a, double b) {
    return std::fabs(a - b) < 0.001;
}


TEST(average_rating, DISABLED_empty_ratings) {
    EXPECT_TRUE(simple_compare_doubles(average_rating(ratings{}), 0.0));
}
TEST(average_ratings, DISABLED_one_rating) {
    EXPECT_TRUE(simple_compare_doubles(average_rating(ratings{ 10 }), 10.0));
}
TEST(average_ratings, DISABLED_two_ratings) {
    EXPECT_TRUE(simple_compare_doubles(average_rating(ratings{ 10, 9 }), 9.5));
}
TEST(average_ratings, DISABLED_three_ratings) {
    EXPECT_TRUE(simple_compare_doubles(average_rating(ratings{ 10, 9, 8 }), 9.0));
}
TEST(average_ratings, DISABLED_four_ratings) {
    EXPECT_TRUE(simple_compare_doubles(average_rating(ratings{ 10, 9, 8, 7 }), 8.5));
}
TEST(average_ratings, DISABLED_five_ratings) {
    EXPECT_TRUE(simple_compare_doubles(average_rating(ratings{ 10, 9, 8, 7, 1 }), 8));  // 10 and 1 are removed
}
TEST(average_ratings, DISABLED_six_ratings) {
    EXPECT_TRUE(simple_compare_doubles(average_rating(ratings{ 10, 9, 8, 7, 6, 1 }), 7.5));  // 10 and 1 are removed
}
TEST(average_ratings, DISABLED_seven_ratings) {
    EXPECT_TRUE(simple_compare_doubles(average_rating(ratings{ 10, 9, 8, 7, 6, 5, 1 }), 7));  // 10 and 1 are removed
}
TEST(average_ratings, DISABLED_ten_ratings) {
    EXPECT_TRUE(simple_compare_doubles(average_rating(ratings{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }), 5.5));  // 10 and 1 are removed
}


TEST(problem_53_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_53_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Average rating of movies:\n"
        "\tThe Godfather: 8.3\n"
        "\tThe Godfather II: 7.7\n"
        "\tThe Godfather III: 7.4\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}

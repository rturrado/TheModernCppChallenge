#include "chapter_09_data_serialization/problem_077_printing_a_list_of_movies_to_a_pdf.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_77_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_77_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Writing PDF out to: .*/list_of_movies.pdf\n"
    ));
}

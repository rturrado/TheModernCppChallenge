#include "chapter_09_data_serialization/problem_078_creating_a_pdf_from_a_collection_of_images.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <sstream>  // ostringstream


TEST(problem_78_main, output) {
    std::ostringstream oss{};
    problem_78_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Writing PDF out to: .*/list_of_images.pdf\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}

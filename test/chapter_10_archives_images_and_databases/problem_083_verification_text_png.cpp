#include "chapter_10_archives_images_and_databases/png/png_writer_wrapper.h"
#include "chapter_10_archives_images_and_databases/problem_083_verification_text_png.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <sstream>  // ostringstream

using namespace tmcppc::png;
using namespace tmcppc::problem_83;
namespace fs = std::filesystem;


TEST(paint_verification_text, png_file_creation) {
    const auto image_file_path{ create_png_file_path(std::filesystem::temp_directory_path(), "test_paint_verification_text") };
    {
        png_writer png_writer(300, 200, 0.0, image_file_path);
        paint_verification_text(png_writer);
    }
    EXPECT_TRUE(fs::exists(image_file_path));
    EXPECT_FALSE(fs::is_empty(image_file_path));
}

TEST(problem_83_main, output) {
    std::ostringstream oss{};
    problem_83_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex("Creating .*/captcha.png...\n\n"));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}

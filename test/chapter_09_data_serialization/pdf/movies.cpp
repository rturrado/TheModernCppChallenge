#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies/samples.h"
#include "chapter_09_data_serialization/pdf/movies_doc.h"
#include "chapter_09_data_serialization/pdf/text_list_layouter.h"

#include <chrono>
#include <filesystem>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

namespace fs = std::filesystem;
using namespace std::chrono_literals;
using namespace tmcppc::movies;
using namespace tmcppc::pdf;


TEST(movies_doc, save_to_text_list_layouter_of_zero_text_lines_per_page) {
    const auto temp_file_path{ fs::temp_directory_path() / "test_pdf_doc_save_to_text_list_layouter_of_zero_text_lines_per_page.pdf" };
    movies_doc out_doc{ catalog{} };
    EXPECT_THROW(out_doc.save_to(temp_file_path, std::make_unique<text_list_layouter>(0)), std::runtime_error);
}

TEST(movies_doc, save_to_empty_list_of_movies) {
    const auto temp_file_path{ fs::temp_directory_path() / "test_pdf_doc_save_to_empty_list_of_movies.pdf" };
    movies_doc out_doc{ catalog{} };
    out_doc.save_to(temp_file_path, std::make_unique<text_list_layouter>(10));
    EXPECT_TRUE(fs::exists(temp_file_path));
    EXPECT_FALSE(fs::is_empty(temp_file_path));
}

TEST(movies_doc, save_to_list_of_2_movies) {
    const auto temp_file_path{ fs::temp_directory_path() / "test_pdf_doc_save_to_list_of_2_movies.pdf" };
    const catalog catalog_of_2_movies{ std::vector<movie>(
        samples::catalog_of_50_movies.movies.cbegin(), samples::catalog_of_50_movies.movies.cbegin() + 2) };
    movies_doc out_doc{ catalog_of_2_movies };
    out_doc.save_to(temp_file_path, std::make_unique<text_list_layouter>(10));
    EXPECT_TRUE(fs::exists(temp_file_path));
    EXPECT_FALSE(fs::is_empty(temp_file_path));
}

TEST(movies_doc, save_to_list_of_30_movies_with_10_per_page) {
    const auto temp_file_path{ fs::temp_directory_path() / "test_pdf_doc_save_to_list_of_30_movies_with_10_per_page.pdf" };
    const catalog catalog_of_30_movies{ std::vector<movie>(
        samples::catalog_of_50_movies.movies.cbegin(), samples::catalog_of_50_movies.movies.cbegin() + 30) };
    movies_doc out_doc{ catalog_of_30_movies };
    out_doc.save_to(temp_file_path, std::make_unique<text_list_layouter>(10));
    EXPECT_TRUE(fs::exists(temp_file_path));
    EXPECT_FALSE(fs::is_empty(temp_file_path));
}

TEST(movies_doc, save_to_list_of_50_movies_with_100_per_page) {
    const auto temp_file_path{ fs::temp_directory_path() / "test_pdf_doc_save_to_list_of_50_movies_with_100_per_page.pdf" };
    movies_doc out_doc{ samples::catalog_of_50_movies };
    out_doc.save_to(temp_file_path, std::make_unique<text_list_layouter>(100));
    EXPECT_TRUE(fs::exists(temp_file_path));
    EXPECT_FALSE(fs::is_empty(temp_file_path));
}

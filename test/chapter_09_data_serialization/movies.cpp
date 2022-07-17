#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies_samples.h"

#include "rtc/pretty_print.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fmt/format.h>
#include <sstream>  // ostringstream

using namespace rtc::pretty_print;
using namespace tmcppc::movies;


// Role
auto role_output{ "Tom Hanks (Forrest Gump)" };
TEST(role, print) {
    std::ostringstream oss{};
    role_sample.print(oss);
    EXPECT_EQ(oss.str(), role_output);
}
TEST(role, operator_insertion) {
    std::ostringstream oss{};
    oss << role_sample;
    EXPECT_EQ(oss.str(), role_output);
}
TEST(role, fmt_print) {
    EXPECT_EQ(fmt::format("{}", role_sample), role_output);
}

// Cast
auto cast_output{ fmt::format(
    "Cast:\n"
    "{0}Tom Hanks (Forrest Gump)\n"
    "{0}Sally Field (Mrs. Gump)\n"
    "{0}Robin Wright (Jenny Curran)\n"
    "{0}Mykelti Williamson (Bubba Blue)\n",
    default_indentation_value) };
TEST(cast, print_empty_cast) {
    std::ostringstream oss{};
    cast{}.print(oss);
    EXPECT_EQ(oss.str(), fmt::format("Cast:\n{}[]\n", default_indentation_value));
}
TEST(cast, print) {
    std::ostringstream oss{};
    cast_sample.print(oss);
    EXPECT_EQ(oss.str(), cast_output);
}
TEST(cast, operator_insertion) {
    std::ostringstream oss{};
    oss << cast_sample;
    EXPECT_EQ(oss.str(), cast_output);
}
TEST(cast, fmt_print) {
    EXPECT_EQ(fmt::format("{}", cast_sample), cast_output);
}

// Director
auto director_output{ "Robert Zemeckis" };
TEST(director, print) {
    std::ostringstream oss{};
    director_sample.print(oss);
    EXPECT_EQ(oss.str(), director_output);
}
TEST(director, operator_insertion) {
    std::ostringstream oss{};
    oss << director_sample;
    EXPECT_EQ(oss.str(), director_output);
}
TEST(director, fmt_print) {
    EXPECT_EQ(fmt::format("{}", director_sample), director_output);
}

// Directors
auto directors_output{ fmt::format(
    "Directors:\n"
    "{0}Robert Zemeckis\n",
    default_indentation_value) };
TEST(directors, print_empty_directors) {
    std::ostringstream oss{};
    directors{}.print(oss);
    EXPECT_EQ(oss.str(), fmt::format("Directors:\n{}[]\n", default_indentation_value));
}
TEST(directors, print) {
    std::ostringstream oss{};
    directors_sample.print(oss);
    EXPECT_EQ(oss.str(), directors_output);
}
TEST(directors, operator_insertion) {
    std::ostringstream oss{};
    oss << directors_sample;
    EXPECT_EQ(oss.str(), directors_output);
}
TEST(directors, fmt_print) {
    EXPECT_EQ(fmt::format("{}", directors_sample), directors_output);
}

// Writer
auto writer_output{ "Winston Groom" };
TEST(writer, print) {
    std::ostringstream oss{};
    writer_sample.print(oss);
    EXPECT_EQ(oss.str(), writer_output);
}
TEST(writer, operator_insertion) {
    std::ostringstream oss{};
    oss << writer_sample;
    EXPECT_EQ(oss.str(), writer_output);
}
TEST(writer, fmt_print) {
    EXPECT_EQ(fmt::format("{}", writer_sample), writer_output);
}

// Writers
auto writers_output{ fmt::format(
    "Writers:\n"
    "{0}Winston Groom\n"
    "{0}Eric Roth\n",
    default_indentation_value) };
TEST(writers, print_empty_writers) {
    std::ostringstream oss{};
    writers{}.print(oss);
    EXPECT_EQ(oss.str(), fmt::format("Writers:\n{}[]\n", default_indentation_value));
}
TEST(writers, print) {
    std::ostringstream oss{};
    writers_sample.print(oss);
    EXPECT_EQ(oss.str(), writers_output);
}
TEST(writers, operator_insertion) {
    std::ostringstream oss{};
    oss << writers_sample;
    EXPECT_EQ(oss.str(), writers_output);
}
TEST(writers, fmt_print) {
    EXPECT_EQ(fmt::format("{}", writers_sample), writers_output);
}

// Media file
auto media_file_without_description_output{
    fmt::format(
        "Media file:\n"
        "{0}id: 1\n"
        "{0}path: './res/db/poster.png'\n"
        "{0}description: ''\n",
        default_indentation_value
    )
};
auto media_file_output{
    fmt::format(
        "Media file:\n"
        "{0}id: 1\n"
        "{0}path: './res/db/poster.png'\n"
        "{0}description: 'Front cover'\n",
        default_indentation_value
    )
};
TEST(media_file, print_empty_description) {
    std::ostringstream oss{};
    media_file_without_description_sample.print(oss);
    EXPECT_EQ(oss.str(), media_file_without_description_output);
}
TEST(media_file, print_description) {
    std::ostringstream oss{};
    media_file_sample.print(oss);
    EXPECT_EQ(oss.str(), media_file_output);
}
TEST(media_file, operator_insertion) {
    std::ostringstream oss{};
    oss << media_file_sample;
    EXPECT_EQ(oss.str(), media_file_output);
}
TEST(media_file, fmt_print) {
    EXPECT_EQ(fmt::format("{}", media_file_sample), media_file_output);
}

// Media files
auto media_files_output{
    fmt::format(
        "Media files:\n"
        "{0}Media file:\n"
        "{0}{0}id: 1\n"
        "{0}{0}path: './res/db/poster.png'\n"
        "{0}{0}description: 'Front cover'\n"
        "{0}Media file:\n"
        "{0}{0}id: 2\n"
        "{0}{0}path: './res/db/city.jpg'\n"
        "{0}{0}description: 'Los Angeles'\n",
        default_indentation_value
    )
};
TEST(media_files, print_empty_media_files) {
    std::ostringstream oss{};
    media_files{}.print(oss);
    EXPECT_EQ(oss.str(), fmt::format("Media files:\n{}[]\n", default_indentation_value));
}
TEST(media_files, print) {
    std::ostringstream oss{};
    media_files_sample.print(oss);
    EXPECT_EQ(oss.str(), media_files_output);
}
TEST(media_files, operator_insertion) {
    std::ostringstream oss{};
    oss << media_files_sample;
    EXPECT_EQ(oss.str(), media_files_output);
}
TEST(media_files, fmt_print) {
    EXPECT_EQ(fmt::format("{}", media_files_sample), media_files_output);
}

// Movie
auto movie_output{
    fmt::format(
        "Movie:\n"
        "{0}id: 9871\n"
        "{0}title: Forrest Gump\n"
        "{0}year: 1994\n"
        "{0}length: 202\n"
        "{0}Cast:\n"
        "{0}{0}Tom Hanks (Forrest Gump)\n"
        "{0}{0}Sally Field (Mrs. Gump)\n"
        "{0}{0}Robin Wright (Jenny Curran)\n"
        "{0}{0}Mykelti Williamson (Bubba Blue)\n"
        "{0}Directors:\n"
        "{0}{0}Robert Zemeckis\n"
        "{0}Writers:\n"
        "{0}{0}Winston Groom\n"
        "{0}{0}Eric Roth\n"
        "{0}Media files:\n"
        "{0}{0}[]\n",
        default_indentation_value
    )
};
TEST(movie, print) {
    std::ostringstream oss{};
    movie_sample.print(oss);
    EXPECT_EQ(oss.str(), movie_output);
}
TEST(movie, operator_insertion) {
    std::ostringstream oss{};
    oss << movie_sample;
    EXPECT_EQ(oss.str(), movie_output);
}
TEST(movie, fmt_print) {
    EXPECT_EQ(fmt::format("{}", movie_sample), movie_output);
}

// Catalog
auto catalog_output{
    fmt::format(
        "Catalog:\n"
        "{0}Movie:\n"
        "{0}{0}id: 11001\n"
        "{0}{0}title: The Matrix\n"
        "{0}{0}year: 1999\n"
        "{0}{0}length: 196\n"
        "{0}{0}Cast:\n"
        "{0}{0}{0}Keanu Reeves (Neo)\n"
        "{0}{0}{0}Laurence Fishburne (Morpheus)\n"
        "{0}{0}{0}Carrie-Anne Moss (Trinity)\n"
        "{0}{0}{0}Hugo Weaving (Agent Smith)\n"
        "{0}{0}Directors:\n"
        "{0}{0}{0}Lana Wachowski\n"
        "{0}{0}{0}Lilly Wachowski\n"
        "{0}{0}Writers:\n"
        "{0}{0}{0}Lana Wachowski\n"
        "{0}{0}{0}Lilly Wachowski\n"
        "{0}{0}Media files:\n"
        "{0}{0}{0}[]\n"
        "{0}Movie:\n"
        "{0}{0}id: 9871\n"
        "{0}{0}title: Forrest Gump\n"
        "{0}{0}year: 1994\n"
        "{0}{0}length: 202\n"
        "{0}{0}Cast:\n"
        "{0}{0}{0}Tom Hanks (Forrest Gump)\n"
        "{0}{0}{0}Sally Field (Mrs. Gump)\n"
        "{0}{0}{0}Robin Wright (Jenny Curran)\n"
        "{0}{0}{0}Mykelti Williamson (Bubba Blue)\n"
        "{0}{0}Directors:\n"
        "{0}{0}{0}Robert Zemeckis\n"
        "{0}{0}Writers:\n"
        "{0}{0}{0}Winston Groom\n"
        "{0}{0}{0}Eric Roth\n"
        "{0}{0}Media files:\n"
        "{0}{0}{0}[]\n",
        default_indentation_value
    )
};
TEST(catalog, print) {
    std::ostringstream oss{};
    catalog_sample.print(oss);
    EXPECT_EQ(oss.str(), catalog_output);
}
TEST(catalog, operator_insertion) {
    std::ostringstream oss{};
    oss << catalog_sample;
    EXPECT_EQ(oss.str(), catalog_output);
}
TEST(catalog, fmt_print) {
    EXPECT_EQ(fmt::format("{}", catalog_sample), catalog_output);
}

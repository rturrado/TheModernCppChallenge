#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies_samples.h"
#include "chapter_10_archives_images_and_databases/file/movies.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>  // ifstream, ofstream
#include <ios>  // ios_base

using namespace tmcppc::movies;
using namespace tmcppc::movies::file;


TEST(from_file, DISABLED_cast) {
    const std::filesystem::path temp_file_path{ std::filesystem::temp_directory_path() / "test_from_console_cast.txt" };
    std::ofstream ofs{ temp_file_path, std::ios_base::out | std::ios_base::trunc };
    ofs <<
        "4\n"
        "Tom Hanks\n"
        "Forrest Gump\n"
        "Sally Field\n"
        "Mrs. Gump\n"
        "Robin Wright\n"
        "Jenny Curran\n"
        "Mykelti Williamson\n"
        "Bubba Blue\n";
        ofs.close();
    std::ifstream ifs{ temp_file_path, std::ios_base::in };
    cast c{};
    from_file(ifs, c);
    EXPECT_EQ(c, cast_sample);
}


TEST(from_file, DISABLED_writers) {
    const std::filesystem::path temp_file_path{ std::filesystem::temp_directory_path() / "test_from_console_writers.txt" };
    std::ofstream ofs{ temp_file_path, std::ios_base::out | std::ios_base::trunc };
    ofs <<
        "2\n"
        "Winston Groom\n"
        "Eric Roth\n";
    ofs.close();
    std::ifstream ifs{ temp_file_path, std::ios_base::in };
    writers ws{};
    from_file(ifs, ws);
    EXPECT_EQ(ws, writers_sample);
}


TEST(from_file, DISABLED_directors) {
    const std::filesystem::path temp_file_path{ std::filesystem::temp_directory_path() / "test_from_console_directors.txt" };
    std::ofstream ofs{ temp_file_path, std::ios_base::out | std::ios_base::trunc };
    ofs <<
        "1\n"
        "Robert Zemeckis\n";
    ofs.close();
    std::ifstream ifs{ temp_file_path, std::ios_base::in };
    directors ds{};
    from_file(ifs, ds);
    EXPECT_EQ(ds, directors_sample);
}


TEST(from_file, DISABLED_movie) {
    const std::filesystem::path temp_file_path{ std::filesystem::temp_directory_path() / "test_from_console_movie.txt" };
    std::ofstream ofs{ temp_file_path, std::ios_base::out | std::ios_base::trunc };
    ofs <<
        "Forrest Gump\n"
        "1994y\n"
        "202\n"
        "4\n"
        "Tom Hanks\n"
        "Forrest Gump\n"
        "Sally Field\n"
        "Mrs. Gump\n"
        "Robin Wright\n"
        "Jenny Curran\n"
        "Mykelti Williamson\n"
        "Bubba Blue\n"
        "1\n"
        "Robert Zemeckis\n"
        "2\n"
        "Winston Groom\n"
        "Eric Roth\n";
    ofs.close();
    std::ifstream ifs{ temp_file_path, std::ios_base::in };
    movie m{};
    from_file(ifs, m);
    EXPECT_EQ(m, movie_with_default_id_sample);
}

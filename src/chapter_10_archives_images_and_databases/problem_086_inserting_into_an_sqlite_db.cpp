#include "chapter_09_data_serialization/movies.h"
#include "chapter_10_archives_images_and_databases/console_movies.h"
#include "chapter_10_archives_images_and_databases/file_movies.h"
#include "chapter_10_archives_images_and_databases/problem_086_inserting_into_an_sqlite_db.h"
#include "chapter_10_archives_images_and_databases/sqlite_movies.h"
#include "env.h"

#include "rtc/console.h"

#include <filesystem>
#include <fmt/ostream.h>
#include <fstream>  // ifstream
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>


namespace tmcppc::problem_86 {
    // insert_movie updates movie.id
    void add_new_movie(std::istream& is, std::ostream& os, tmcppc::movies::sqlite_mcpp::database& movies_db, tmcppc::movies::movie& movie) {
        auto c{
            rtc::console::read_char(is, os,
                fmt::format("{}\nAre you sure you want to add this movie to the movies database? [y/n] ", movie),
                {'n', 'N', 'y', 'Y'}
        )};
        if (c == 'y' or c == 'Y') {
            movies_db.insert_movie(movie);
        }
    }


    void add_new_movie_from_console(std::istream& is, std::ostream& os, tmcppc::movies::sqlite_mcpp::database& movies_db) {
        fmt::print(os, "Please enter the movie data (ID will be later overwritten with DB's Movies.rowid)\n");
        tmcppc::movies::movie movie{};
        tmcppc::movies::console::from_console(is, os, movie);
        add_new_movie(is, os, movies_db, movie);
    }


    void add_new_movie_from_file(std::istream& is, std::ostream& os, tmcppc::movies::sqlite_mcpp::database& movies_db) {
        const std::filesystem::path new_movies_file_path{
            tmcppc::env::get_instance().get_resource_folder_path() / "db" / "NewMovies.txt" };
        fmt::print(os, "Adding movies from {}\n", new_movies_file_path.generic_string());
        std::ifstream ifs{ new_movies_file_path };
        try {
            std::string line{};
            std::getline(ifs, line);
            int number_of_movies{ std::stoi(line) };
            while (number_of_movies--) {
                tmcppc::movies::movie movie{};
                tmcppc::movies::file::from_file(ifs, movie);
                add_new_movie(is, os, movies_db, movie);
            }
        } catch (const std::exception& ex) {
            fmt::print(os, "Error: {}\n", ex.what());
        }
    }


    void add_new_movies(std::istream& is, std::ostream& os, tmcppc::movies::sqlite_mcpp::database& movies_db) {
        for (;;) {
            auto input_option{
                rtc::console::read_char(is, os,
                    "Choose method for adding a new movie (1 - Console, 2 - File, q - Quit): ",
                    { '1', '2', 'q'}
            )};
            switch (input_option) {
                case '1': add_new_movie_from_console(is, os, movies_db); break;
                case '2': add_new_movie_from_file(is, os, movies_db); break;
                case 'q': return;
                default: break;
            }
        }
        fmt::print(os, "\n");
    }
}  // namespace tmcppc::problem_86


void problem_86_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::problem_86;

    const auto db_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "db" / "movies.db" };

    try {
        {
            auto sqlite_db{ tmcppc::movies::sqlite_mcpp::create_movies_database(db_file_path) };
            auto movies_db{ tmcppc::movies::sqlite_mcpp::database{ sqlite_db } };

            add_new_movies(is, os, movies_db);

            fmt::print(os, "{}", movies_db);
        }

        fmt::print(os, "\n");

        tmcppc::movies::sqlite_mcpp::remove_movies_database_file(is, os, db_file_path);
    } catch (const sqlite::sqlite_exception& ex) {
        fmt::print(os, "Error: code = {}, message = '{}', operation = '{}'\n",
            ex.get_code(), ex.what(), ex.get_sql());
    } catch (const std::exception& ex) {
        fmt::print(os, "Error: {}\n", ex.what());
    }

    fmt::print(os, "\n");
}


// Inserting movies into an SQLite database transactionally
//
// Extend the program written for the previous problem so that it can add new movies to the database.
// The movies could be read from the console, or alternatively from a text file.
// The insertion of movie data into several tables in the database must be performed transactionally.
void problem_86_main() {
    problem_86_main(std::cin, std::cout);
}

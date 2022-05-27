#include "chapter_10_archives_images_and_databases/problem_079_finding_files_in_a_zip_archive.h"

#include "ZipArchive.h"
#include "ZipFile.h"

#include <algorithm>  // move
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <iterator>  // back_inserter
#include <ostream>
#include <regex>  // regex_match
#include <string>

namespace fs = std::filesystem;


std::vector<std::string> regex_search_in_zip_file(std::ostream& os, const fs::path& file_path, const std::regex& pattern) {
    try {
        if (not fs::exists(file_path)) {
            return {};
        }

        std::vector<std::string> file_paths{};

        auto archive{ ZipFile::Open(file_path.generic_string()) };
        for (auto i{ 0 }; i < archive->GetEntriesCount(); ++i) {
            auto entry{ archive->GetEntry(i) };
            if (not entry->IsDirectory()) {
                auto& entry_file_path{ entry->GetFullName() };
                if (std::regex_match(entry_file_path, pattern)) {
                    file_paths.push_back(entry_file_path);
                }
            }
        }
        return file_paths;
    } catch (const std::exception& ex) {
        fmt::print(os, "Error: {}\n", ex.what());
        return {};
    }
};


void problem_79_main(std::ostream& os) {
    const std::filesystem::path input_file_path{ std::filesystem::current_path() / "res" / "sample_folder.zip" };
    std::string pattern_str{ R"(^.*\.jpg$)" };
    fmt::print(os, "Searching for '{}' files in '{}'...\n", pattern_str, input_file_path.generic_string());
    for (auto&& f : regex_search_in_zip_file(os, input_file_path, std::regex{ pattern_str })) {
        fmt::print(os, "\t{}\n", f);
    }
    fmt::print(os, "\n");
}


// Finding files in a ZIP archive
//
// Write a program that can search for and print all the files in a ZIP archive
// whose name matches a user-provided regular expression
// (for instance, use ^.*\.jpg$ to find all files with the extension .jpg).
void problem_79_main() {
    problem_79_main(std::cout);
}

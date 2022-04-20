#pragma once

#include <filesystem>
#include <ostream>
#include <string>
#include <vector>


std::vector<std::filesystem::directory_entry> get_directory_entries_matching(
    const std::filesystem::path& path, const std::string& pattern_str);

void problem_37_main(std::ostream& os);
void problem_37_main();

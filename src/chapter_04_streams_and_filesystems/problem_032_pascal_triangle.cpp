#include "chapter_04_streams_and_filesystems/problem_032_pascal_triangle.h"

#include <exception>
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <functional>  // plus
#include <numeric>  // adjacent_difference
#include <stdexcept>  // out_of_range
#include <string>  // to_string
#include <vector>


namespace tmcppc::problem_32 {
    pascal_triangle_t pascal_triangle(size_t n) {
        if (n > 30) {
            throw std::out_of_range{ std::string{"calling pascal_triangle with n > 30, n = "} + std::to_string(n) };
        }

        pascal_triangle_t ret{};

        if (n == 0) {
            return ret;
        }

        ret.push_back({ 1 });
        if (n == 1) {
            return ret;
        }

        ret.push_back({ 1, 1 });
        if (n == 2) {
            return ret;
        }

        for (size_t i{ 2 }; i < n; ++i) {  // n > 2
            std::vector<uint32_t> row(i + 1, 1);
            std::adjacent_difference(cbegin(ret[i - 1]), cend(ret[i - 1]), begin(row), std::plus<>{});
            ret.push_back(row);
        }
        return ret;
    }
}  // namespace tmcppc::problem_32


// Pascal's triangle
//
// Write a function that prints up to 10 rows of Pascal's triangle to the console
void problem_32_main(std::ostream& os) {
    using namespace tmcppc::problem_32;

    for (auto n : { 0, 1, 2, 10, 40 }) {
        try {
            fmt::print(os, "Pascal triangle for n = {}:\n", n);
            auto ret{ pascal_triangle(static_cast<size_t>(n)) };
            fmt::print(os, "\t{}\n", ret.empty() ? "[]" : fmt::format("{}", fmt::join(ret, "\n\t")));
        } catch (const std::exception& err) {
            fmt::print(os, "\tError: {}\n", err.what());
        }
    }
    fmt::print(os, "\n");
}

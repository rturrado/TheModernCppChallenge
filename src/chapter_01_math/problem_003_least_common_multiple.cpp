#include "chapter_01_math/problem_003_least_common_multiple.h"

#include "rtc/console.h"  // read_list_of_positive_numbers

#include <algorithm>  // all_of, any_of, sort
#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>
#include <vector>


namespace tmcppc::problem_3 {
    // Note this function doesn't check for overflows
    long lcm(std::ostream& os, std::vector<int> v) {
        if (v.size() == 0) {
            fmt::print(os, "Error: calling lcm(v) with an empty list.\n");
            return -1;
        }
        if (std::ranges::any_of(v, [](int n) { return n <= 0;  })) {
            fmt::print(os, "Error: calling lcm(v) with a negative or zero value.\n");
            return -1;
        }

        // Sort the vector of numbers
        std::ranges::sort(v);

        // Take the bigger number
        // Then, find the number that is 1, 2... i times the bigger one,
        // such that it is multiple of all the other numbers in the list
        auto bigger_number = v[v.size() - 1];
        for (auto i{ 1 }; ; ++i) {
            long possible_lcm{ bigger_number * i };
            if (std::all_of(std::cbegin(v), std::prev(cend(v)),
                [&possible_lcm](int n) { return possible_lcm % n == 0; })) {
                return possible_lcm;
            }
        }
        return -1;
    };


    long lcm(std::vector<int> v) {
        return lcm(std::cerr, v);
    }
}  // namespace tmcppc::problem_3


void problem_3_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::problem_3;

    auto v{ rtc::console::read_list_of_positive_numbers(is, os,
        "Please enter 2 or more numbers (>= 1) ('quit' to finish the list): ", 2, 1) };

    fmt::print(os, "The least common multiple of {} is: {}\n\n", v, lcm(v));
}


// Least common multiple
//
// Write a program that will, given two or more positive integers, calculate and print the least common multiple of them all
void problem_3_main() {
    problem_3_main(std::cin, std::cout);
}

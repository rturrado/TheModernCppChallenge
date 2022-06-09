#pragma once

#include <iosfwd>
#include <utility>  // pair
#include <vector>


namespace tmcppc::problem_12 {
    size_t get_collatz_sequence_size(size_t n);
    std::vector<size_t> get_collatz_sequence(size_t n);

    std::pair<size_t, size_t> get_longest_collatz_sequence_v1(size_t limit);
    std::pair<size_t, size_t> get_longest_collatz_sequence_v2(size_t limit);
}  // namespace tmcppc::problem_12


void problem_12_main(std::ostream& os);
void problem_12_main();

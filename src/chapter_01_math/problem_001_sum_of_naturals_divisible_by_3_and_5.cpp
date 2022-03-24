#include "problem_001_sum_of_naturals_divisible_by_3_and_5.h"

#include "rtc/console_read.h"  // read_positive_number
#include "rtc/print.h"

#include <iostream>  // cout
#include <numeric>  // accumulate
#include <range/v3/core.hpp>
#include <range/v3/range/conversion.hpp>  // to
#include <range/v3/view/filter.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/take.hpp>
#include <vector>

using namespace rtc::print;


std::vector<size_t> naturals_divisible_by_3_and_5_up_to_limit_v1(size_t limit)
{
    std::vector<size_t> ret{};
    for (auto i{ 0u }; i <= limit; ++i)
    {
        if ((i % 3 == 0) || (i % 5 == 0))
        {
            ret.push_back(i);
        }
    }
    return ret;
}


std::vector<size_t> naturals_divisible_by_3_and_5_up_to_limit_v2(size_t limit)
{
    return ranges::views::iota(0)
        | ranges::views::take(limit + 1)
        | ranges::views::filter([](auto i) { return (i % 3 == 0) or (i % 5 == 0); })
        | ranges::to<std::vector<size_t>>();
}


// Sum of naturals divisible by 3 and 5
//
// Write a program that calculates and prints the sum of all natural numbers divisible by either 3 or 5,
// up to a given limit entered by the user
void problem_1_main()
{
    auto n{ rtc::console::read_positive_number("Please enter a number (>= 0): ", 0) };

    for (auto f : { naturals_divisible_by_3_and_5_up_to_limit_v1 , naturals_divisible_by_3_and_5_up_to_limit_v2 })
    {
        auto v{ f(n) };

        std::cout << "The sum of all natural numbers divisible by either 3 or 5 and up to " << n
            << " is:\n\t" << std::accumulate(std::cbegin(v), std::cend(v), static_cast<size_t>(0)) << " " << v << "\n\n";
    }

}

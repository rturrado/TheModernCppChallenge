#include "chapter_02_language_features/problem_019_adding_a_range_of_values_to_a_container.h"

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <iostream>  // cout
#include <list>
#include <string>
#include <vector>


void problem_19_main(std::ostream& os) {
    std::vector<int> v_int{};
    push_back_list(v_int, 10, 20, 30);
    fmt::print(os, "{}\n", v_int);

    std::vector<std::string> v_str{};
    push_back_list(v_str, "Hey", "Joe!", "Voodoo");
    fmt::print(os, "{}\n", v_str);

    std::list<float> l_float{};
    push_back_list_v2(l_float, 3.14f, 0.99f, -273.0f);
    fmt::print(os, "{}\n\n", l_float);
}


// Adding a range of values to a container
//
// Write a general-purpose function that can add any number of elements
// to the end of a container that has a method push_back(T&& value).
void problem_19_main() {
    problem_19_main(std::cout);
}

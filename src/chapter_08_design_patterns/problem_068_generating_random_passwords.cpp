#include "chapter_08_design_patterns/problem_068_generating_random_passwords.h"

#include <fmt/ostream.h>
#include <iostream>  // cout
#include <memory>  // make_unique, unique_ptr
#include <ostream>


void problem_68_main(std::ostream& os) {
    auto g{ std::make_unique<composite_password_generator>() }; std::cout << "Creating a password ";

    g->add_generator(std::make_unique<symbol_generator>(2)); std::cout << "with 2 symbols, ";
    g->add_generator(std::make_unique<contains_generator<digit_range>>(2)); std::cout << "2 digits, ";
    g->add_generator(std::make_unique<contains_generator<lowercase_range>>(2)); std::cout << "2 lowercase letters, ";
    g->add_generator(std::make_unique<contains_generator<uppercase_range>>(2)); std::cout << "and 2 uppercase letters: ";

   fmt::print(os, "{}\n\n", g->generate());
}


// Generating random passwords
//
// Write a program that can generate random passwords according to some predefined rules.
// Every password must have a configurable minimum length.
// In addition, it should be possible to include in the generation rules such as the presence of at least one digit,
// symbol, lower or uppercase character, and so on. These additional rules must be configurable and composable.
void problem_68_main() {
    problem_68_main(std::cout);
}

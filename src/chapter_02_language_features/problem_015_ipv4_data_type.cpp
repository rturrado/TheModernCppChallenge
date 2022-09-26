#include "chapter_02_language_features/ipv4.h"
#include "chapter_02_language_features/problem_015_ipv4_data_type.h"

#include "fmt/ostream.h"

#include <iostream>  // cin, cout


void problem_15_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::network;

    while (true) {
        fmt::print(os, "Please enter an IPv4 address (e.g. 127.0.0.1), or 'quit' to finish: ");

        std::string s{};
        std::getline(is, s);

        if (s == "quit") {
            break;
        }

        try {
            ipv4 address{ s };
            fmt::print(os, "\tYou've entered a valid IPv4 address: {}\n", s);
        } catch (const std::exception& ex) {
            fmt::print(os, "\tError: {}\n", ex.what());
        }
    }
    fmt::print(os, "\n");
}


// IPv4 data type
//
// Write a class that represents an IPv4 address.
// Implement the functions required to be able to read and write such addresses from or to the console.
// The user should be able to input values in dotted form, such as 127.0.0.1 or 168.192.0.100.
// This is also the form in which IPv4 addresses should be formatted to an output stream.
void problem_15_main() {
    problem_15_main(std::cin, std::cout);
}

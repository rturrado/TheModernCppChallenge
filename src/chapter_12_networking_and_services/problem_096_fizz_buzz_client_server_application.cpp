#include "chapter_12_networking_and_services/fizz_buzz.h"
#include "chapter_12_networking_and_services/problem_096_fizz_buzz_client_server_application.h"

#include <fmt/ostream.h>
#include <future>
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>

#define BOOST_ASIO_STANDALONE
#include <asio.hpp>


void problem_96_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::fizz_buzz;

    asio::io_context io{};
    asio::ip::tcp::endpoint ep{ asio::ip::make_address("127.0.0.1"), 5555 };
    server s{ os, io, ep };
    client c{ is, os, io, ep };
    auto server_future = std::async(std::launch::async, [&s]() { return s.run(); });
    auto client_future = std::async(std::launch::async, [&c]() { return c.run(); });

    client_future.get();
    server_future.get();

    fmt::print(os, "\n");
}


// Write a client-server application that can be used for playing the Fizz-Buzz game.
// The client sends numbers to the server that answers back with fizz, buzz, fizz-buzz, or the number itself, according to the game rules.
// Communication between the client and the server must be done over TCP.
// The server should run indefinitely.
// The client should run as long as the user enters numbers between 1 and 99.
//
// Fizz-Buzz is a game for children, intented to teach them arithmetic division.
// A player must say a number and another player should answer with:
//   - Fizz, if the number is divisible by 3.
//   - Buzz, if the number is divisible by 5.
//   - Fizz-buzz, if the number is divisible by both 3 and 5.
//   - The number itself in other cases.
void problem_96_main() {
    problem_96_main(std::cin, std::cout);
}

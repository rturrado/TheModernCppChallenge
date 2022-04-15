#include "chapter_02_language_features/problem_022_temperature_scales_literals.h"
#include "chapter_02_language_features/temperature/v1/temperature.h"
#include "chapter_02_language_features/temperature/v2/temperature.h"

#include <fmt/ostream.h>
#include <fmt/ranges.h>
#include <ios>  // boolalpha
#include <iostream>  // cout


void test_temperature_v1(std::ostream& os)
{
    using namespace rtc::temperature::v1;
    using namespace rtc::temperature::v1::literals;

    fmt::print(os, "{}", "Using temperature::v1:\n");

    fmt::print(os, "\t{} in Fahrenheit: {:.2f} Fahrenheit\n", 35.5_deg, to_fahrenheit(35.5_deg));
    fmt::print(os, "\t{} in Kelvin: {:.2f} Kelvin\n\n", 35.5_deg, to_kelvin(35.5_deg));

    temperature t1{ 12.3, scale::celsius };
    temperature t2{ 12.3, scale::fahrenheit };
    temperature t3{ 12.3, scale::kelvin };

    fmt::print(os, "\t{} == {}? {}. ", t1, t2, t1 == t2);
    fmt::print(os, "{} == {:.2f} Celsius\n", t2, to_celsius(t2));
    fmt::print(os, "\t{} < {}? {}. ", t1, t2, t1 < t2);
    fmt::print(os, "{} == {:.2f} Celsius\n", t2, to_celsius(t2));
    fmt::print(os, "\t{} > {}? {}. ", t1, t3, t1 > t3);
    fmt::print(os, "{} == {:.2f} Celsius\n\n", t3, to_celsius(t3));

    fmt::print(os, "\t{} + {} = {}. ", t1, t2, t1 + t2);
    fmt::print(os, "{} == {:.2f} Celsius\n", t2, to_celsius(t2));
    fmt::print(os, "\t{} - {} = {}. ", t1, t3, t1 - t3);
    fmt::print(os, "{} == {:.2f} Celsius\n\n", t3, to_celsius(t3));
}


void test_temperature_v2(std::ostream& os)
{
    using namespace rtc::temperature::v2;
    using namespace rtc::temperature::v2::literals;

    os << "Using temperature::v2:\n";

    os << "\t" << 35.5_deg << " in Fahrenheit: " << temperature_cast<long double, scale::fahrenheit>(35.5_deg) << "\n";
    os << "\t" << 35.5_deg << " in Kelvin: " << temperature_cast<long double, scale::kelvin>(35.5_deg) << "\n\n";

    temperature<float, scale::celsius> t1{ static_cast<float>(12.3) };
    temperature<float, scale::fahrenheit> t2{ static_cast<float>(12.3) };
    temperature<float, scale::kelvin> t3{ static_cast<float>(12.3) };

    // Now, we can only compare temperatures on the same scale
    os << "\t" << t1 << " == " << t2 << "? " << std::boolalpha << (t1 == temperature_cast<float, scale::celsius>(t2)) << ". ";
    os << t2 << " == " << temperature_cast<float, scale::celsius>(t2) << "\n";
    os << "\t" << t1 << " < " << t2 << "? " << std::boolalpha << (t1 < temperature_cast<float, scale::celsius>(t2)) << ". ";
    os << t2 << " == " << temperature_cast<float, scale::celsius>(t2) << "\n";
    os << "\t" << t1 << " > " << t3 << "? " << std::boolalpha << (t1 > temperature_cast<float, scale::celsius>(t3)) << ". ";
    os << t3 << " == " << temperature_cast<float, scale::celsius>(t3) << "\n\n";

    // Same for arithmetic operations
    os << "\t" << t1 << " + " << t2 << " = " << (t1 + temperature_cast<float, scale::celsius>(t2)) << ". ";
    os << t2 << " == " << temperature_cast<float, scale::celsius>(t2) << "\n";
    os << "\t" << t1 << " - " << t3 << " = " << (t1 - temperature_cast<float, scale::celsius>(t3)) << ". ";
    os << t3 << " == " << temperature_cast<float, scale::celsius>(t3) << "\n\n";
}


// Literals of various temperature scales
//
// Write a small library that enables expressing temperatures in the three most used scales,
// Celsius, Fahrenheit, and Kelvin, and converting between them.
// The library must enable you to write temperature literals in all these scales,
// such as 36.5_deg for Celsius, 97.7_f for Fahrenheit, and 309.65_K for Kelvin;
// perform operations with these values; and convert between them
void problem_22_main(std::ostream& os)
{
    test_temperature_v1(os);
    test_temperature_v2(os);
}


void problem_22_main() {
    problem_22_main(std::cout);
}

#include "chapter_02_language_features/temperature/v1/temperature.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fmt/format.h>
#include <sstream>  // ostringstream

using namespace tmcppc::temperature::v1;


TEST(temperature_v1, DISABLED_operator_insertion_invalid) {
    std::ostringstream oss{};
    temperature<float> t{ 25.0f, scale::invalid };
    oss << t;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("<invalid temperature>"));
}
TEST(temperature_v1, DISABLED_operator_insertion_celsius) {
    std::ostringstream oss{};
    temperature<float> t{ 25.0f, scale::celsius };
    oss << t;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("25.00 Celsius"));
}
TEST(temperature_v1, DISABLED_operator_insertion_fahrenheit) {
    std::ostringstream oss{};
    temperature<float> t{ 25.0f, scale::fahrenheit };
    oss << t;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("25.00 Fahrenheit"));
}
TEST(temperature_v1, DISABLED_operator_insertion_kelvin) {
    std::ostringstream oss{};
    temperature<float> t{ 25.0f, scale::kelvin };
    oss << t;
    EXPECT_THAT(oss.str(), ::testing::HasSubstr("25.00 Kelvin"));
}

TEST(temperature_v1, DISABLED_fmt_format_invalid) {
    temperature<float> t{ 25.0f, scale::invalid };
    EXPECT_EQ(fmt::format("{}", t), "<invalid temperature>");
}
TEST(temperature_v1, DISABLED_fmt_format_celsius) {
    temperature<float> t{ 25.0f, scale::celsius };
    EXPECT_EQ(fmt::format("{}", t), "25.00 Celsius");
}
TEST(temperature_v1, DISABLED_fmt_format_fahrenheit) {
    temperature<float> t{ 25.0f, scale::fahrenheit };
    EXPECT_EQ(fmt::format("{}", t), "25.00 Fahrenheit");
}
TEST(temperature_v1, DISABLED_fmt_format_kelvin) {
    temperature<float> t{ 25.0f, scale::kelvin };
    EXPECT_EQ(fmt::format("{}", t), "25.00 Kelvin");
}

TEST(temperature_v1, DISABLED_conversion_of_values) {
    double c{ 25.0 };
    double f{ 77.0 };
    double k{ 298.15 };
    EXPECT_TRUE(simple_compare_long_doubles(c, fahrenheit_to_celsius(f)));
    EXPECT_TRUE(simple_compare_long_doubles(c, kelvin_to_celsius(k)));
    EXPECT_TRUE(simple_compare_long_doubles(f, celsius_to_fahrenheit(c)));
    EXPECT_TRUE(simple_compare_long_doubles(f, kelvin_to_fahrenheit(k)));
    EXPECT_TRUE(simple_compare_long_doubles(k, celsius_to_kelvin(c)));
    EXPECT_TRUE(simple_compare_long_doubles(k, fahrenheit_to_kelvin(f)));
}
TEST(temperature_v1, DISABLED_conversion_of_temperatures) {
    temperature<double> t0{ 25.0, scale::invalid };
    temperature<double> t1{ 25.0, scale::celsius };
    temperature<double> t2{ 77.0, scale::fahrenheit };
    temperature<double> t3{ 298.15, scale::kelvin };
    EXPECT_THROW((void) to_celsius(t0), invalid_temperature_error);
    EXPECT_THROW((void) to_fahrenheit(t0), invalid_temperature_error);
    EXPECT_THROW((void) to_kelvin(t0), invalid_temperature_error);
    EXPECT_TRUE(simple_compare_long_doubles(t1.value(), to_celsius(t2)));
    EXPECT_TRUE(simple_compare_long_doubles(t1.value(), to_celsius(t3)));
    EXPECT_TRUE(simple_compare_long_doubles(t2.value(), to_fahrenheit(t1)));
    EXPECT_TRUE(simple_compare_long_doubles(t2.value(), to_fahrenheit(t3)));
    EXPECT_TRUE(simple_compare_long_doubles(t3.value(), to_kelvin(t1)));
    EXPECT_TRUE(simple_compare_long_doubles(t3.value(), to_kelvin(t2)));
}

TEST(temperature_v1, DISABLED_comparisons) {
    temperature<float> t1{ 20.0f, scale::celsius };
    temperature<float> t2{ 25.0f, scale::celsius };
    temperature<float> t3{ 77.0f, scale::fahrenheit };
    temperature<float> t4{ 298.15f, scale::kelvin };
    EXPECT_TRUE(t1 == t1);
    EXPECT_TRUE(t2 == t3);
    EXPECT_TRUE(t2 == t4);
    EXPECT_TRUE(t1 < t2);
    EXPECT_TRUE(t2 > t1);
    EXPECT_TRUE(t1 <= t2);
    EXPECT_TRUE(t2 >= t1);
    EXPECT_TRUE(t2 <= t3);
    EXPECT_TRUE(t3 >= t2);
    EXPECT_TRUE(t2 <= t4);
    EXPECT_TRUE(t4 >= t2);
}
TEST(temperature_v1, DISABLED_equality_precision) {
    temperature<float> t1{ 25.0f, scale::celsius };
    temperature<float> slightly_above_t1{ 25.01f, scale::celsius };
    temperature<float> t2{ 77.0f, scale::fahrenheit };
    temperature<float> slightly_above_t2{ 77.018f, scale::fahrenheit };
    temperature<float> t3{ 298.15f, scale::kelvin };
    temperature<float> slightly_above_t3{ 298.16f, scale::kelvin };
    EXPECT_FALSE(t1 == slightly_above_t1);
    EXPECT_FALSE(t2 == slightly_above_t2);
    EXPECT_FALSE(t3 == slightly_above_t3);
    EXPECT_FALSE(simple_compare_long_doubles(t1.value(), to_celsius(slightly_above_t2)));
    EXPECT_FALSE(simple_compare_long_doubles(t1.value(), to_celsius(slightly_above_t3)));
    EXPECT_FALSE(simple_compare_long_doubles(t2.value(), to_fahrenheit(slightly_above_t1)));
    EXPECT_FALSE(simple_compare_long_doubles(t2.value(), to_fahrenheit(slightly_above_t3)));
    EXPECT_FALSE(simple_compare_long_doubles(t3.value(), to_kelvin(slightly_above_t1)));
    EXPECT_FALSE(simple_compare_long_doubles(t3.value(), to_kelvin(slightly_above_t2)));
}

TEST(temperature_v1, DISABLED_arithmetic) {
    temperature<double> t0{ 25.0, scale::invalid };
    temperature<double> t1{ 25.0, scale::celsius };
    temperature<double> t2d{ 77.0, scale::fahrenheit };
    temperature<double> t3d{ 298.15, scale::kelvin };
    temperature<float> t2f{ 77.0f, scale::fahrenheit };
    temperature<float> t3f{ 298.15f, scale::kelvin };
    temperature<double> sum{ 50.0, scale::celsius };
    temperature<double> difference{ 0.0, scale::celsius };
    EXPECT_THROW((void) (t0 + t1), invalid_temperature_error);
    EXPECT_THROW((void) (t0 + t2d), invalid_temperature_error);
    EXPECT_THROW((void) (t0 + t3d), invalid_temperature_error);
    EXPECT_THROW((void) (t3d + t0), invalid_temperature_error);
    EXPECT_THROW((void) (t2d + t0), invalid_temperature_error);
    EXPECT_THROW((void) (t1 + t0), invalid_temperature_error);
    EXPECT_THROW((void) (t0 - t1), invalid_temperature_error);
    EXPECT_THROW((void) (t0 - t2d), invalid_temperature_error);
    EXPECT_THROW((void) (t0 - t3d), invalid_temperature_error);
    EXPECT_THROW((void) (t3d - t0), invalid_temperature_error);
    EXPECT_THROW((void) (t2d - t0), invalid_temperature_error);
    EXPECT_THROW((void) (t1 - t0), invalid_temperature_error);
    EXPECT_TRUE(t1 + t2d == sum);
    EXPECT_TRUE(t1 + t3d == sum);
    EXPECT_TRUE(t1 - t2d == difference);
    EXPECT_TRUE(t1 - t3d == difference);
    EXPECT_TRUE(t1 + t2f == sum);
    EXPECT_TRUE(t1 + t3f == sum);
    EXPECT_TRUE(t1 - t2f == difference);
    EXPECT_TRUE(t1 - t3f == difference);
}

TEST(temperature_v1, DISABLED_user_defined_literals) {
    using namespace literals;
    temperature<double> t1{ 25.0, scale::celsius };
    temperature<double> t2{ 77.0, scale::fahrenheit };
    temperature<double> t3{ 298.15, scale::kelvin };
    EXPECT_TRUE(25.0_deg == t1);
    EXPECT_TRUE(77.0_f == t2);
    EXPECT_TRUE(298.15_K == t3);
}

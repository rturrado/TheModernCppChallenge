#include "chapter_01_math/problem_011_converting_numerical_values_to_roman.h"
#include "chapter_01_math/roman.h"

#include "rtc/timer.h"  // function_timer

#include "benchmark/benchmark.h"  // google benchmark
#include "fmt/chrono.h"
#include "fmt/ranges.h"

#include <chrono>  // duration, milli


// Custom benchmark
//
void cb_to_roman() {
    using namespace rtc::timer;
    using namespace tmcppc::date;

    fmt::print("[to_roman custom benchmark]\n\n");
    fmt::print("Calling to_roman() from 0 to 9999:\n");
    auto t1 = function_timer<>::duration(
        []() {
            for (int i{ 0 }; i < 10'000; ++i) {
                for (size_t j : { 99, 999, 1999 }) {
                    to_roman_v1(j);
                }
            }
        });
    fmt::print("\tv1: {}\n", std::chrono::duration<double, std::milli>(t1));

    auto t2 = function_timer<>::duration(
        []() {
            for (int i{ 0 }; i < 10'000; ++i) {
                for (size_t j : { 99, 999, 1999 }) {
                    to_roman_v2(j);
                }
            }
        });
    fmt::print("\tv2: {}\n", std::chrono::duration<double, std::milli>(t2));

    auto t3 = function_timer<>::duration(
        []() {
            for (int i{ 0 }; i < 10'000; ++i) {
                for (size_t j : { 99, 999, 1999 }) {
                    to_roman_v3(j);
                }
            }
        });
    fmt::print("\tv3: {}\n", std::chrono::duration<double, std::milli>(t3));

    auto t4 = function_timer<>::duration(
        []() {
            for (int i{ 0 }; i < 10000; ++i) {
                for (size_t j : { 99, 999, 1999 }) {
                    to_roman_v4(j);
                }
            }
        });
    fmt::print("\tv4: {}\n\n", std::chrono::duration<double, std::milli>(t4));
}


// Google benchmark
//
static void gb_to_roman_v1(benchmark::State& state) {
    while (state.KeepRunning()) {
        tmcppc::date::to_roman_v1(1000);
    }
}

static void gb_to_roman_v2(benchmark::State& state) {
    while (state.KeepRunning()) {
        tmcppc::date::to_roman_v2(1000);
    }
}

static void gb_to_roman_v3(benchmark::State& state) {
    while (state.KeepRunning()) {
        tmcppc::date::to_roman_v3(1000);
    }
}

static void gb_to_roman_v4(benchmark::State& state) {
    while (state.KeepRunning()) {
        tmcppc::date::to_roman_v4(1000);
    }
}

BENCHMARK(gb_to_roman_v1);
BENCHMARK(gb_to_roman_v2);
BENCHMARK(gb_to_roman_v3);
BENCHMARK(gb_to_roman_v4);

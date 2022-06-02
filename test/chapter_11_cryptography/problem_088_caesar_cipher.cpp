#include "chapter_11_cryptography/problem_088_caesar_cipher.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // ostringstream


TEST(problem_88_main, DISABLED_output) {
    std::ostringstream oss{};
    problem_88_main(oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Encrypting and decrypting file '.*res/sample_file.txt'\n"
        "\tOK\n"
    ));
}

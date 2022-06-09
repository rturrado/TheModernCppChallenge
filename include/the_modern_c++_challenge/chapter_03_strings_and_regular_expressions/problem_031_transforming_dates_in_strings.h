#pragma once

#include <exception>
#include <iosfwd>
#include <string>
#include <string_view>


namespace tmcppc::problem_31 {
    struct invalid_date_format_error : public std::exception {
        explicit invalid_date_format_error(const std::string& date) noexcept { message_ += "\"" + date + "\""; }
        const char* what() const noexcept { return message_.c_str(); }
    private:
        std::string message_{ "invalid date format: " };
    };

    std::string format_date_v1(const std::string& s);

    std::string format_date_v2(std::string_view s);
}  // namespace tmcppc::problem_31


void problem_31_main(std::ostream& os);
void problem_31_main();

#include "chapter_12_networking_and_services/text_translation.h"

#include "curl_easy.h"
#include "curl_header.h"

#include <fmt/format.h>
#include <ostream>
#include <regex>  // regex_match, smatch
#include <sstream>  // ostringstream
#include <string>
#include <string_view>


namespace tmcppc::text_translation {
    translator_azure::translator_azure(std::string_view key) : key_{ key } {}

    [[nodiscard]] std::string translator_azure::parse_translate_response(const std::string& response) const {
        std::string ret{};
        const std::regex pattern{ R"(<string xmlns="[^"]+">([^<]*)</string>)" };
        const std::regex error_pattern{ R"(<html><body><h1>Argument Exception</h1>.*<p>Message: ([^<]+)</p>.*)" };
        std::smatch matches{};
        if (std::regex_match(response, matches, pattern)) {
            ret = matches[1].str();
        } else if (std::regex_match(response, matches, error_pattern)) {
            return fmt::format("Error: {}", matches[1].str());
        }
        return ret;
    }

    [[nodiscard]] std::string translator_azure::translate(std::string_view text, language_code from, language_code to) const {

        std::string ret{};
        try {
            std::ostringstream oss{};
            curl::curl_ios<std::ostringstream> writer{ oss };
            curl::curl_easy easy{ writer };

            std::string url_encoded_text{ text };
            easy.escape(url_encoded_text);

            auto from_code_str{ language_code_to_string_map[from] };
            auto to_code_str{ language_code_to_string_map[to] };

            easy.add<CURLOPT_URL>(fmt::format(
                "{}/Translate?from={}&to={}&text={}", endpoint, from_code_str, to_code_str, url_encoded_text)
                .c_str());

            curl::curl_header header{};
            header.add(fmt::format("{}:{}", key_header, key_).c_str());
            easy.add<CURLOPT_HTTPHEADER>(header.get());

            easy.perform();

            ret = parse_translate_response(oss.str());
        } catch (const curl::curl_easy_exception& ex) {
            throw translation_error{ ex.what() };
        }
        return ret;
    }
}  // namespace tmcppc::text_translation

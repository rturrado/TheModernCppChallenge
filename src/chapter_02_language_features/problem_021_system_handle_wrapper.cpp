#include "chapter_02_language_features/problem_021_system_handle_wrapper.h"
#include "chapter_02_language_features/unique_hdl.h"

#include <cassert>  // assert
#include <iostream>  // cout
#include <filesystem>
#include <fmt/ostream.h>
#include <vector>
#include <stdexcept>  // runtime_error

#ifdef _WIN32
#include <windows.h>  // CreateFileW
#endif  // _WIN32


void function_that_throws() {
    throw std::runtime_error{"I'm a throwing function!\n"};
}


void test_unique_hdl(std::wostream& wos) {
#ifdef _WIN32
    auto file_path{ std::filesystem::current_path() / "res" / "sample_file.txt" };

    using handle = tmcppc::unique_hdl<tmcppc::HANDLE, tmcppc::handle_traits>;

    handle file_hdl{
        CreateFileW(
            file_path.wstring().c_str(),
            GENERIC_READ,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
    )};

    if (!file_hdl) {
        fmt::print(wos, L"Error in unique_hdl constructor: {}\n", GetLastError());
        return;
    }
    fmt::print(wos, L"Opened: {}\n", file_path.generic_wstring());

    auto another_file_hdl{ std::move(file_hdl) };
    assert(another_file_hdl and another_file_hdl.get());

    std::vector<char> buffer(1024);
    DWORD bytesRead = 0;
    if (!ReadFile(
            another_file_hdl.get(),
            buffer.data(),
            static_cast<DWORD>(buffer.size()),
            &bytesRead,
            nullptr)) {
        fmt::print(wos, L"Error in ReadFile: {}\n", GetLastError());
    }
    else {
        fmt::print(wos, L"Read {} bytes from file\n", bytesRead);
    }

    function_that_throws();
#else
    fmt::print(wos, L"Error: Unimplemented.\n");
#endif  // _WIN32
}


// System handle wrapper
//
// Consider an operating system handle, such as a file handle.
// Write a wrapper that handles the acquisition and release of the handle,
// as well as other operations such as verifying the validity of the handle
// and moving handle ownership from one object to another.
void problem_21_main(std::wostream& wos) {
    try {
        test_unique_hdl(wos);
    }
    catch (const std::runtime_error& ex) {
        wos << L"Error: " << ex.what() << L"\n";
    }
    fmt::print(wos, L"\n");
}

void problem_21_main() {
    problem_21_main(std::wcout);
}

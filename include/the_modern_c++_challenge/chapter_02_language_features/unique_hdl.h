#pragma once

#ifdef _WIN32
#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#endif  // _WIN32


namespace tmcppc::data_structures {
    using HANDLE = void*;


    // From Windows with C++ - C++ and the Windows API
    // https://docs.microsoft.com/en-us/archive/msdn-magazine/2011/july/msdn-magazine-windows-with-c-c-and-the-windows-api
    //
    // In C++, a traits class is commonly used to provide information about a given type.
    // In this way I can write a single class template for handles and
    // provide different traits classes for the different types of handles in the Windows API.
    // A handle's traits class also needs to define how a handle is released
    // so that the handle class template can automatically release it if needed.
    struct handle_traits {
        static HANDLE invalid() noexcept {
#ifdef _WIN32
            return INVALID_HANDLE_VALUE;
#else
            return nullptr;
#endif  // _WIN32
        }
        static void close([[maybe_unused]] HANDLE hdl) noexcept {
#ifdef _WIN32
            if (hdl != INVALID_HANDLE_VALUE) {
                CloseHandle(hdl);
            }
#endif  // _WIN32
        }
    };


    template <typename Type, typename Traits>
    class unique_hdl {
    public:
        explicit unique_hdl(Type hdl = Traits::invalid()) noexcept : hdl_{ hdl } {}

        // I've deleted the copy constructor and copy assignment operator.
        // This prevents the compiler from automatically generating them, as they're rarely appropriate for handles.
        unique_hdl(const unique_hdl& other) noexcept = delete;
        unique_hdl& operator=(const unique_hdl& other) noexcept = delete;

        unique_hdl(unique_hdl&& other) noexcept : hdl_{ other.release() } {}
        [[nodiscard]] unique_hdl& operator=(unique_hdl&& other) noexcept { reset(other.release()); return *this; }

        ~unique_hdl() noexcept { close(); }

        [[nodiscard]] explicit operator bool() noexcept { return hdl_ != Traits::invalid(); }

        // The way a unique_handle owns a handle is analogous to the way
        // the standard unique_ptr class template owns an object and manages that object through a pointer.
        // It then makes sense to provide the familiar get, reset and release member functions
        // to manage the underlying handle.
        [[nodiscard]] Type get() const noexcept { return hdl_; }

        [[nodiscard]] bool reset(Type hdl = Traits::invalid()) noexcept {
            if (hdl_ != hdl) {
                close();
                hdl_ = hdl;
            }
            return static_cast<bool>(*this);
        }

        [[nodiscard]] Type release() noexcept {
            auto tmp_hdl{ hdl_ };
            hdl_ = Traits::invalid();
            return tmp_hdl;
        }

    private:
        void close() noexcept { Traits::close(hdl_); }

        Type hdl_{ Traits::invalid() };
    };
}  // namespace tmcppc::data_structures

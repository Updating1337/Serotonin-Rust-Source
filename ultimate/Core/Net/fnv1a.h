#pragma once
#include <cstdint>
#include <string>

// todo - dex; check arg type for macros?

// compile-time hash.
#define HASHH( str )                                     \
    []() {                                              \
        constexpr uint32_t out{ FNV1a::get( str ) };    \
                                                        \
        return out;                                     \
    }()

// compile-time const hash.
#define CONST_HASH( str ) FNV1a::get( str )

class FNV1a {
private:
    // fnv1a constants.
    enum : uint32_t {
        PRIME = 0x1000193u,
        BASIS = 0x811C9DC5u
    };

    // compile-time strlen.
    // todo - dex; move this?
    static inline constexpr size_t ct_strlen(const char* str, bool include_nullchar = false) {
        size_t out{};

        // count number of characters.
        while (str[++out] != '\0');

        // add one for null character if desired.
        if (include_nullchar)
            ++out;

        return out;
    }

    static inline constexpr size_t wct_strlen(const wchar_t* str, bool include_nullchar = false) {
        size_t out{};

        // count number of characters.
        while (str[++out] != '\0');

        // add one for null character if desired.
        if (include_nullchar)
            ++out;

        return out;
    }

public:
    // hash data ( compile-time or run-time ).
    static inline constexpr uint32_t get(const uint8_t* data, const size_t len) {
        uint32_t out{ BASIS };

        for (size_t i{}; i < len; ++i)
            out = (out ^ data[i]) * PRIME;

        return out;
    }

    // hash c-style string ( compile-time or run-time ).
    static inline constexpr uint32_t get(const char* str) {
        uint32_t out{ BASIS };
        size_t   len{ ct_strlen(str) };

        for (size_t i{}; i < len; ++i)
            out = (out ^ str[i]) * PRIME;

        return out;
    }
    
    // hash c-style string ( compile-time or run-time ).
    static inline constexpr uint32_t get(const wchar_t* str) {
        uint32_t out{ BASIS };
        size_t   len{ wct_strlen(str) };

        for (size_t i{}; i < len; ++i)
            out = (out ^ str[i]) * PRIME;

        return out;
    }

    // hash c++-style string ( run-time only ).
    static inline uint32_t get(const std::string& str) {
        return get((uint8_t*)str.c_str(), str.size());
    }
};
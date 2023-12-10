#pragma once
#include <cstdint>
#include "../Utils/lazy.hpp"

#include "crt.hpp"

#include <map>
#include <unordered_map>
namespace memory {
    template <typename ptr_t = uintptr_t>
    struct address_base_t {
        ptr_t m_ptr{};
    public:
        address_base_t() = default;
        address_base_t(ptr_t ptr) : m_ptr(ptr) {};
        address_base_t(ptr_t* ptr) : m_ptr(ptr_t(ptr)) {};
        address_base_t(void* ptr) : m_ptr(ptr_t(ptr)) {};
        address_base_t(void** ptr) : m_ptr(ptr_t(ptr)) {};
        address_base_t(const void* ptr) : m_ptr(ptr_t(ptr)) {};

        template <typename t>
        address_base_t(t ptr) : m_ptr(ptr_t(ptr)) {};

        ~address_base_t() = default;

        __forceinline operator ptr_t() const {
            return m_ptr;
        }

        __forceinline operator void* () {
            return reinterpret_cast<void*>(m_ptr);
        }

        __forceinline operator void** () {
            return reinterpret_cast<void**>(m_ptr);
        }

        __forceinline ptr_t get_inner() const {
            return m_ptr;
        }

        __forceinline void clear() {
            m_ptr = ptr_t(0);
        }

        __forceinline bool is_valid() const {
            return m_ptr >= 0x10000 && m_ptr < 0xf000000000000;
        }

        template <typename t = address_base_t<ptr_t>>
        __forceinline bool compare(t in) const {
            return m_ptr == ptr_t(in);
        }

        __forceinline auto& self_get(uint8_t in = 1) {
            m_ptr = get<ptr_t>(in);
            return *this;
        }

        __forceinline auto& self_offset(ptrdiff_t offset) {
            if (!m_ptr)
                return *this;

            m_ptr += offset;
            return *this;
        }

        __forceinline auto& self_align_up(ptrdiff_t factor) {
            m_ptr = align_up(factor);
            return *this;
        }

        __forceinline auto& self_align_down(ptrdiff_t factor) {
            m_ptr = align_down(factor);
            return *this;
        }

        template <typename t = address_base_t<ptr_t>>
        __forceinline auto& self_jmp(ptrdiff_t offset = 0x1) {
            m_ptr = jmp(offset);
            return *this;
        }

        __forceinline auto& self_find_opcode(uint8_t opcode, ptrdiff_t offset = 0x0) {
            m_ptr = find_opcode(opcode, offset);
            return *this;
        }

        template <typename t = address_base_t<ptr_t>>
        __forceinline auto& apply(t in) {
            m_ptr = ptr_t(in);
            return *this;
        }

        template <typename t = ptr_t>
        __forceinline t cast() const {
            return t(m_ptr);
        }

        template <typename t = address_base_t<ptr_t>>
        __forceinline t get(ptrdiff_t in = 1) const {
            if (!m_ptr)
                return t(ptr_t(0));

            auto dummy = m_ptr;
            while (in--) {
                if (dummy)
                    dummy = *reinterpret_cast<ptr_t*>(dummy);
                else
                    return t(ptr_t(0));
            }

            return t(dummy);
        }

        template <typename t = address_base_t<ptr_t>>
        __forceinline t offset(ptrdiff_t offset) const {
            if (!m_ptr)
                return t(ptr_t(0));

            return t(m_ptr + offset);
        }

        template <typename t = address_base_t<ptr_t>>
        __forceinline t align_down(ptrdiff_t factor) const {
            return t(m_ptr & ~(factor - 1));
        }

        template <typename t = address_base_t<ptr_t>>
        __forceinline t align_up(ptrdiff_t factor) const {
            return t(align_down(m_ptr - 1, factor) + factor);
        }

        template <typename t = address_base_t<ptr_t>>
        __forceinline t jmp(ptrdiff_t offset = 0x1) const {
            if (!m_ptr)
                return t(ptr_t(0));

            ptr_t base = m_ptr + offset;
            auto disp = *reinterpret_cast<int32_t*>(base);

            base += sizeof(uint32_t);
            base += disp;

            return t(base);
        }

        template <typename t = address_base_t<ptr_t>>
        __forceinline t find_opcode(uint8_t opcode, ptrdiff_t offset = 0x0, ptrdiff_t max_offset = 0x40) const {
            if (!m_ptr)
                return t(0);

            auto base = m_ptr;
            while (true) {
                if (opcode == *reinterpret_cast<uint8_t*>(base))
                    break;

                if (!max_offset--)
                    return t(0);
                base += 1;
            }

            base += offset;
            return t(base);
        }
    };

    using address_t = address_base_t<uintptr_t>;
    using address32_t = address_base_t<uint32_t>;
    using address64_t = address_base_t<uint64_t>;
} // namespace memory





inline std::unordered_map<size_t, std::string> translated_map{};

using WCTMB = int(__stdcall*)(unsigned int, unsigned long, const wchar_t*, int, char*, int, const char*, bool*);
inline std::string utf16_to_utf8(std::wstring utf16_string) {
    auto hash = Hash(utf16_string.c_str(), false);
    auto find = translated_map.find(hash);
    if (find != translated_map.end())
        return translated_map[hash];

    static memory::address_t _WideCharToMultiByte = 0;

    if (!_WideCharToMultiByte.is_valid())
        _WideCharToMultiByte = LI_FN(WideCharToMultiByte).cached();

    auto len = _WideCharToMultiByte.cast<WCTMB>()(65001, 0, utf16_string.c_str(), int(utf16_string.length()), NULL, 0, NULL, NULL);
    if (len) {
        std::string converted(len, '\0');
        _WideCharToMultiByte.cast<WCTMB>()(65001, 0, utf16_string.c_str(), int(utf16_string.length()), converted.data(), len, 0, 0);
        translated_map.emplace(hash, converted);
        return converted;
    }
    return {};
}


inline std::unordered_map<size_t, std::wstring> translated_map2{};

using MBTWC = int(__stdcall*)(unsigned int, unsigned long, const char*, int, wchar_t*, int);
inline std::wstring utf8_to_utf16(std::string utf8_string) {
    auto hash = std::hash<std::string>{}(utf8_string);
    auto find = translated_map2.find(hash);
    if (find != translated_map2.end())
        return translated_map2[hash];

    static memory::address_t _MultiByteToWideChar = 0;

    if (!_MultiByteToWideChar.is_valid())
        _MultiByteToWideChar = LI_FN(MultiByteToWideChar).cached();

    auto len = _MultiByteToWideChar.cast<MBTWC>()(65001, 0, utf8_string.c_str(), int(utf8_string.length()), NULL, 0);
    if (len) {
        std::wstring converted(len, L'\0');
        _MultiByteToWideChar.cast<MBTWC>()(65001, 0, utf8_string.c_str(), int(utf8_string.length()), &converted[0], len);
        translated_map2.emplace(hash, converted);
        return converted;
    }
    return {};
}


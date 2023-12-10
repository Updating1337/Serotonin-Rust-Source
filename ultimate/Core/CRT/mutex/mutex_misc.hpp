#pragma once
#include <cstdint>
#include <intrin.h>
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

namespace rb {

    inline void* current_thread_id() noexcept {
        constexpr auto tib_self_offset = 6 * sizeof(void*);
        return *(reinterpret_cast<std::uintptr_t**>(
#ifdef _M_X64
                     __readgsqword(tib_self_offset)
#elif _M_IX86
                      __readfsdword(tib_self_offset)
#elif _M_ARM
                      _MoveFromCoprocessor(15, 0, 13, 0, 2)
#elif _M_ARM64
                      __getReg(18)
#else
    #error "architecture unsupported"
#endif
                         ) +
                 9);
    }

    inline void yield_processor() noexcept {
        _mm_pause();
    }

    inline void memory_barrier() noexcept {
        _ReadWriteBarrier();
    }

} // namespace rb

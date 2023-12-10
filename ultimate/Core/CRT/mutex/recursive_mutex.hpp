#pragma once
#include "mutex_misc.hpp"
#include <cstdint>

namespace rb {

    /// \brief Adapter type that turns any lock into a recursive one.
    /// \tparam Lock The lock type.
    /// \tparam RecursionCounter The type used to store the number of recursive entries.
    /// \note try_lock implementation is possible but a bit tedious.
    template <class Lock, class RecursionCounter = std::uint32_t>
    class recursive_lock_adapter {
        Lock _lock;
        void* _thread_id = nullptr;
        RecursionCounter _counter = 0;
    public:
        using counter_type = RecursionCounter;
        using lock_type = Lock;

        constexpr recursive_lock_adapter() noexcept = default;

        constexpr lock_type& get() noexcept {
            return _lock;
        }
        constexpr const lock_type& get() const noexcept {
            return _lock;
        }

        void lock() noexcept(noexcept(_lock.lock())) {
            const auto tid = current_thread_id();
            if (_thread_id != tid) {
                _lock.lock();
                _thread_id = tid;
            }
            ++_counter;
        }

        bool try_lock() noexcept(noexcept(_lock.lock())) {
            bool try_lock_result = false;
            const auto tid = current_thread_id();
            if (_thread_id != tid) {
                try_lock_result = _lock.try_lock();

                if (try_lock_result)
                    _thread_id = tid;
            }

            if (try_lock_result)
                ++_counter;

            return try_lock_result;
        }

        void unlock() noexcept(noexcept(_lock.unlock())) {
            if (--_counter == 0) {
                _thread_id = nullptr;
                _lock.unlock();
            }
        }
    };

} // namespace rb
#pragma once
#include "mutex_misc.hpp"
#include "recursive_mutex.hpp"
#include "scoped_mutex.hpp"
#include <atomic>

#include <Windows.h>

namespace rb {

    class smutex {
        std::atomic<bool> locked{false};
        std::size_t lock_cnt = 0;
        std::size_t unlock_cnt = 0;
    public:
        void lock();
        bool try_lock();
        void unlock();
        smutex(){};
    };

    using recursive_smutex = recursive_lock_adapter<smutex>;

} // namespace rb
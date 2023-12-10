#include "..\crt.hpp"
#include "smutex.hpp"
#include <Windows.h>

//forward declaration
float system_time();

namespace rb {

#pragma optimize(off, "")
    void smutex::lock() {
        lock_cnt++;

        float timeout = 0.2f;
        if (lock_cnt - unlock_cnt > 1 && locked)
            timeout = 0.5f;

        auto enter_time = system_time();
        auto check_timedout = [&]() {
            return system_time() - enter_time > timeout;
        };

        for (;;) {
            if (check_timedout()) {
                // #ifdef _DEBUG
                //  Shouldn't happen

                // #endif
                unlock();
            }

            while (locked.load(std::memory_order_relaxed)) {
                yield_processor();

                if (check_timedout())
                    unlock();
            }

            if (try_lock())
                break;
        }
    }

    bool smutex::try_lock() {
        return locked.exchange(true, std::memory_order_acquire) == false;
    }

    void smutex::unlock() {
        unlock_cnt++;
        locked.store(false, std::memory_order_release);
    }
#pragma optimize(off, "")

} // namespace rb
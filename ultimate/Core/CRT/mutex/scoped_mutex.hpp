#pragma once

namespace rb {

    template <class Mtx>
    class scoped_mutex {
        Mtx& mtx;
    public:
        scoped_mutex(Mtx& _mtx): mtx(_mtx) {
            mtx.lock();
        }
        ~scoped_mutex() {
            mtx.unlock();
        }
    };

} // namespace rb
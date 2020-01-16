/*===========================================================================
     _____        _____        _____        _____
 ___|    _|__  __|_    |__  __|__   |__  __| __  |__  ______
|    \  /  | ||    \      ||     |     ||  |/ /     ||___   |
|     \/   | ||     \     ||     \     ||     \     ||___   |
|__/\__/|__|_||__|\__\  __||__|\__\  __||__|\__\  __||______|
    |_____|      |_____|      |_____|      |_____|

--[Mark3 Realtime Platform]--------------------------------------------------

Copyright (c) 2012 - 2018 m0slevin, all rights reserved.
See license.txt for more information
=========================================================================== */

#include "kernel_safe_guard.h"
#include "mark3.h"

namespace  {
using namespace Mark3;
static KernelSafeGuard kernelGuard;
}

namespace Mark3 {
    KernelSafeGuard& KernelSafeGuard::instance() {
        return kernelGuard;
    }

    void KernelSafeGuard::lock() {
        if (Kernel::IsStarted()) {
            CriticalSection::Enter();
        }
    }

    void KernelSafeGuard::release() {
        if (Kernel::IsStarted()) {
            CriticalSection::Exit();
        }
    }
} // namespace Mark3

extern "C" {
bool __cxa_guard_acquire() {
    KernelSafeGuard::instance().lock();
    return true;
}
bool __cxa_guard_release() {
    KernelSafeGuard::instance().release();
    return true;
}
}

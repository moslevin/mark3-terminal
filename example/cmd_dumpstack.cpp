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

#include "cmd_dumpstack.h"

#include "cmd.h"
#include "shell_env.h"
#include "stdio.h"
#include "stdlib.h"
#include "getopt.h"

namespace dumpstack {
using namespace Mark3;

void usage() {
    printf ("dumpstack -t <thread id>\n");
}

int main(int argc, const char** argv) {
    auto opt = int{};
    auto tid = uint8_t{255};
    auto foundTid = false;

    while ((opt = getopt(argc, (char* const*)argv, "t:")) != -1) {
        switch (opt) {
        case 't': {
            tid = static_cast<uint8_t>(atoi(optarg));
            foundTid = true;
        } break;
        case '?':
        default : {
            printf("unknown option\n");
            usage();
            return -1;
        }
        }
    }
    if (!foundTid) {
        usage();
        return -1;
    }

    Thread* target = nullptr;
    {
        auto cg = CriticalGuard{};
        auto* threadList = ThreadListList::GetHead();
        while ((threadList != nullptr) && (target == nullptr)) {
            auto* thread = threadList->GetHead();
            // Thread-lists are circular linked lists; iterate until we hit the head of the list
            auto* start = thread;
            do {
                if (thread->GetID() == tid) {
                    target = thread;
                    break;
                }
                if (thread->GetNext() == thread) {
                    break;
                }
            } while ((thread != start) && (target == nullptr));

            threadList = threadList->GetNext();
        }
    }

    if (target == nullptr) {
        printf("invalid thread ID=%d\n", tid);
        return -1;
    }

    printf("Register Dump %d:\n", tid);

    K_WORD* stack = nullptr;
#if AVR
    //!! ToDo -- implement for other targets
    if (target == Scheduler::GetCurrentThread()) {
        // Dump actual register contents if this is the current thread (not very accurate)
        printf("SP:\t%02X%02X\n", *((volatile K_WORD*)(0x5E)), *((volatile K_WORD*)(0x5D)));

        printf("RAMPZ:\t%02X\n", *((volatile K_WORD*)(0x5B)));

        printf("Z:\t%02X%02X\n", *((volatile K_WORD*)(0x1F)), *((volatile K_WORD*)(0x1E)));
        printf("Y:\t%02X%02X\n", *((volatile K_WORD*)(0x1D)), *((volatile K_WORD*)(0x1C)));
        printf("X:\t%02X%02X\n", *((volatile K_WORD*)(0x1B)), *((volatile K_WORD*)(0x1A)));

        for (auto i = int{31}; i >= 0; i--) {
            printf("R%d:\t%02X\n", i, *((volatile K_WORD*)(0x1F - ((uint8_t)i))));
        }
        printf("SREG:\t%02X\n", *((volatile K_WORD*)(0x5F)));
    } else {
        // Pull the context from the stack frame.
        stack = target->GetStackTop();
        printf("SP:\t%04X\n", (K_ADDR)stack);
        stack++;
        printf("RAMPZ:\t%02X\n", *stack++);

        printf("Z:\t%02X%02X\n", *stack, *(stack + 1));
        printf("Y:\t%02X%02X\n", *(stack + 2), *(stack + 3));
        printf("X:\t%02X%02X\n", *(stack + 4), *(stack + 5));

        for (auto i = int{31}; i >= 0; i--) {
            printf("R%d:\t%02X\n", i, *stack++);
        }
        printf("SREG:\t%02X\n", *stack++);
    }
#endif
    printf("\nDumping Stack for Thread %d:\n", tid);
    stack = target->GetStack() + (target->GetStackSize() / sizeof(K_WORD));
    auto stackWords = target->GetStackSize();

    for (auto i = (unsigned int){}; i < ((stackWords / sizeof(K_WORD)) + 15); i+= 16) {
        for (auto j = 0; (j < 16) && (stack != target->GetStack()); j++) {
            if (j == 0) {
                printf("0x%x: ", (unsigned int)stack);
            }
            printf("%02X ", (unsigned int)*stack);
            stack--;
        }
        printf("\n");
    }

    return 0;
}
} // namespace dumpstack

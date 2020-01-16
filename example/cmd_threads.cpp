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

#include "cmd_threads.h"

#include "cmd.h"
#include "shell_env.h"
#include "stdio.h"
#include "getopt.h"

namespace  {
using namespace Mark3;

typedef struct {
    const char* name;
    uint8_t id;
    ThreadState state;
    PORT_PRIO_TYPE prio;
    uint16_t stack;
    uint16_t slack;
} threadInfo_t;

constexpr auto maxThreadInfo = 10;
threadInfo_t threadInfo[maxThreadInfo];

} // anonymous namespace

//---------------------------------------------------------------------------
namespace threads {
using namespace Mark3;

int main(int argc, const char** argv)   {
    int threadIdx = 0;
    {
        auto cg = CriticalGuard{};
        auto* threadList = ThreadListList::GetHead();

        while ((threadList != nullptr) && (threadIdx < maxThreadInfo)) {
            auto* thread = threadList->GetHead();
            // Thread-lists are circular linked lists; iterate until we hit the head of the list
            auto* start = thread;
            do {
                threadInfo[threadIdx].name = thread->GetName();
                threadInfo[threadIdx].id = thread->GetID();
                threadInfo[threadIdx].prio = thread->GetPriority();
                threadInfo[threadIdx].state = thread->GetState();
                threadInfo[threadIdx].stack = thread->GetStackSize();
                threadInfo[threadIdx].slack = thread->GetStackSlack();
                threadIdx++;
                if (thread->GetNext() == thread) {
                    break;
                }
            } while ((thread != start) && (threadIdx < maxThreadInfo));

            threadList = threadList->GetNext();
        }
    }

    printf("tid\tname\tstate\tprio\tstack\tmargin\n");
    for (auto i = 0; i < threadIdx; i++) {
        printf("%d\t%s\t%u\t%u\t%u\t%u\n",
               threadInfo[i].id,
               threadInfo[i].name,
               (unsigned int)threadInfo[i].state,
               (unsigned int)threadInfo[i].prio,
               (unsigned int)threadInfo[i].stack,
               (unsigned int)threadInfo[i].slack
               );
    }

    return 0;
}
} // namespace argprint

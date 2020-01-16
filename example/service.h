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
#pragma once

#include "ll.h"
#include <stdint.h>

namespace Mark3 {

enum class ServiceState : uint8_t
{
    Stopped,
    Starting,
    Running,
    Stopping,
//--
    Count
};

enum class ServicePriority : uint8_t
{
    Idle,
    Lowest,
    Lower,
    Low,
    Normal,
    High,
    Higher,
    Highest,
//
    Count
};

using ServiceStart = int (*)(void*);
using ServiceStop = int (*)(void*);

class Service : public TypedLinkListNode<Service> {
public:
    Service(ServicePriority priority_,
            ServiceStart start_,
            ServiceStop stop_,
            const char* name_,
            void* context_);

    int start();

    int stop();

    int restart();

    const char* name();

    ServiceState state();

    ServicePriority priority();

private:
    ServiceState     m_state;
    ServicePriority  m_prio;
    ServiceStart     m_startFn;
    ServiceStop      m_stopFn;
    const char*      m_name;
    void*            m_context;
};

class ServiceManager : public TypedDoubleLinkList<Service> {
public:
    static ServiceManager& instance();

    Service* byName(const char* name_);

    void startAll();

    void stopAll();
};

} // namespace Mark3;

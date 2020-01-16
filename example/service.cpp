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

#include "service.h"
#include "string.h"

#include <stdint.h>
#include <stdio.h>

namespace {
using namespace Mark3;
ServiceManager serviceManager;
} // anonymous namespace

namespace Mark3 {

ServiceManager& ServiceManager::instance() {
    return serviceManager;
}

Service* ServiceManager::byName(const char* name_) {
    auto* node = GetHead();
    while (node) {
        if (0 == strcmp(name_, node->name())) {
            return node;
        }
        node = node->GetNext();
    }
    return nullptr;
}

void ServiceManager::startAll() {
    for (auto i = uint8_t{}; i < static_cast<uint8_t>(ServicePriority::Count); i++) {
        auto* node = GetHead();
        while (node) {
            if (static_cast<uint8_t>(node->priority()) == i) {
                auto rc = node->start();
                if (rc != 0) {
                    printf("Service %s: start failed %d\n", node->name(), rc);
                }
            }
            node = node->GetNext();
        }
    }
}

void ServiceManager::stopAll() {
    for (auto i = static_cast<uint8_t>(ServicePriority::Count); i != 0 ; i--) {
        auto* node = GetHead();
        while (node) {
            if (static_cast<uint8_t>(node->priority()) == (i - 1)) {
                auto rc = node->stop();
                if (rc != 0) {
                    printf("Service %s: stop failed %d\n", node->name(), rc);
                }
            }
            node = node->GetNext();
        }
    }
}


Service::Service(ServicePriority priority_,
        ServiceStart start_,
        ServiceStop stop_,
        const char* name_,
        void* context_)
    : m_state{ServiceState::Stopped}
    , m_prio{priority_}
    , m_startFn{start_}
    , m_stopFn{stop_}
    , m_name{name_}
    , m_context{context_}
{
    ServiceManager::instance().Add(this);
}

int Service::start() {
    if (m_state == ServiceState::Stopped) {
        m_state = ServiceState::Starting;
        auto rc = m_startFn(m_context);
        if (rc == 0) {
            m_state = ServiceState::Running;
        } else {
            m_state = ServiceState::Stopped;
        }
        return rc;
    }

    return -1;
}

int Service::stop() {
    if (m_state == ServiceState::Running) {
        m_state = ServiceState::Stopping;
        auto rc = m_stopFn(m_context);
        m_state = ServiceState::Stopped;
        return rc;
    }

    return -1;
}

int Service::restart() {
    if (m_state == ServiceState::Running) {
        stop();
    }
    return start();
}

const char* Service::name() {
    return m_name;
}

ServiceState Service::state() {
    return m_state;
}

ServicePriority Service::priority() {
    return m_prio;
}


} // namespace Mark3;

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
#include "node_dev.h"

namespace Mark3 {

DevNode::DevNode(const char* name_, DirNode* parent_, Driver* driver_)
    : m_parent{parent_}
    , m_driver{driver_}
{
    if (m_parent) {
        m_parent->add(this);
    }
    name(name_);
    type(PathNodeType::Dev);
}

DirNode* DevNode::parent() {
    return m_parent;
}

Driver* DevNode::driver() {
    return m_driver;
}

} // namespace Mark3

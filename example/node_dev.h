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

#include "path_node.h"
#include "node_dir.h"
#include "driver.h"

namespace Mark3 {
class DevNode : public IPathNode
{
public:
    DevNode(const char* name_, DirNode* parent_, Driver* driver_);

    DirNode* parent();

    Driver* driver();

private:

    DirNode* m_parent;
    Driver* m_driver;
};
} // namespace Mark3

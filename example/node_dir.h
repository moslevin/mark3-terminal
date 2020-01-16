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
#include "string.h"

namespace Mark3 {

class DirNode : public IPathNode
{
public:
    DirNode(const char* name_, DirNode* parent_);

    DirNode* handlePath(const char* path_);

    DirNode* parent();

    void add(IPathNode* child_);

    void remove(IPathNode* child_);

    IPathNode* children();

private:
    TypedDoubleLinkList<IPathNode> m_children;
    DirNode* m_parent;
};
} // namespace Mark3

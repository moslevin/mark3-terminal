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

#include "node_dir.h"

namespace Mark3 {

DirNode::DirNode(const char* name_, DirNode* parent_)
    : m_parent{parent_}
{
    if (m_parent) {
        m_parent->add(this);
    }
    type(PathNodeType::Directory);
    name(name_);
}

DirNode* DirNode::handlePath(const char* path_) {
    // Find the next delimiter in the path -- either forward slash or \0
    // printf("check subdir: %s, path: %s\n", m_name, path_);
    auto terminal = false;

    // Trim leading '/'
    if (*path_ == '/') {
        path_++;
    }
    const auto* nextDelimiter = strchr(path_, '/');
    if (!nextDelimiter) {
        nextDelimiter = strchr(path_, '\0');
        terminal = true;
    }
    // no next delimiter, or path_ + 1 == nextDelimiter, indicating it's the end
    if (!nextDelimiter) {
        return this;
    }
    auto numChars = (nextDelimiter - (path_));
    if (!numChars) {
        return this;
    }

    // There's a path beyond this -- see if there's a match
    auto* node = m_children.GetHead();
    while (node) {
        if (node->type() == PathNodeType::Directory) {
            if (0 == strncmp(path_, node->name(), numChars)) {
                auto* dirNode = reinterpret_cast<DirNode*>(node);
                if (terminal) {
                    return dirNode;
                }

                auto* handler = dirNode->handlePath(path_ + numChars);
                if (handler) {
                    return handler;
                }
            }
        }
        node = node->GetNext();
    }

    // There's no match -- return nullptr
    return nullptr;
}

DirNode* DirNode::parent() {
    return m_parent;
}

void DirNode::add(IPathNode* child_) {
    m_children.Add(child_);
}

void DirNode::remove(IPathNode* child_) {
    m_children.Remove(child_);
}

IPathNode* DirNode::children() {
    return m_children.GetHead();
}

} // namespace Mark3

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
#include "file_props.h"

#include <stddef.h>
#include <stdint.h>

namespace Mark3 {

size_t FileProperties::size() {
    return m_size;
}

void FileProperties::size(size_t size_) {
    m_size = size_;
}

uint16_t FileProperties::user() {
    return m_uid;
}

void FileProperties::user(uint16_t user_) {
    m_uid = user_;
}

uint16_t FileProperties::group() {
    return m_gid;
}

void FileProperties::group(uint16_t group_) {
    m_gid = group_;
}

uint16_t FileProperties::perms() {
    return m_perms;
}

void FileProperties::perms(uint16_t perms_) {
    m_perms = perms_;
}

const char* FileProperties::name() {
    return m_name;
}

void FileProperties::name(const char* name_) {
    m_name = name_;
}

PathNodeType FileProperties::type() {
    return m_type;
}

void FileProperties::type(PathNodeType type_) {
    m_type = type_;
}

} // namespace Mark3

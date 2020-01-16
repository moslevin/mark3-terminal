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
#include <stdint.h>
#include <stddef.h>


namespace Mark3 {
enum class PathNodeType : uint8_t {
    Directory,
    File,
    Sys,
    Link,
    Dev,
//--
    Count
};

class FileProperties
{
public:
    size_t size();

    void size(size_t size_);

    uint16_t user();

    void user(uint16_t user_);

    uint16_t group();

    void group(uint16_t group_);

    uint16_t perms();

    void perms(uint16_t perms_);

    const char* name();

    void name(const char* name_);

    PathNodeType type();

    void type(PathNodeType type_);

private:
    const char* m_name;
    size_t m_size;
    uint16_t m_uid;
    uint16_t m_gid;
    uint16_t m_perms;
    PathNodeType m_type;
};
} // namespace Mark3

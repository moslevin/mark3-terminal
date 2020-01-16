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
#include "m3shell.h"
#include "shell_env.h"

namespace Mark3 {

class Command : public TypedLinkListNode<Command>
{
public:
    Command(const char* name_, Entrypoint_t entrypoint_);

    int run(int argc_, const char** argv_);

    void registerHandler();

    const char* name();

    CommandHandler* getHandler();

private:

    static void actionWrapper(TerminalIO* pclTerminal_, const char* szArgs_, void* pvContext_);

    CommandHandler m_handler;
    const char* m_name;
    Entrypoint_t m_entrypoint;
};

} // namespace Mark3

/*===========================================================================
     _____        _____        _____        _____
 ___|    _|__  __|_    |__  __|__   |__  __| __  |__  ______
|    \  /  | ||    \      ||     |     ||  |/ /     ||___   |
|     \/   | ||     \     ||     \     ||     \     ||___   |
|__/\__/|__|_||__|\__\  __||__|\__\  __||__|\__\  __||______|
    |_____|      |_____|      |_____|      |_____|

--[Mark3 Realtime Platform]--------------------------------------------------

Copyright (c) 2012 - 2019 m0slevin, all rights reserved.
See license.txt for more information
=========================================================================== */

#include "command_handler.h"
namespace Mark3
{
//---------------------------------------------------------------------------
CommandHandler::CommandHandler(const char* szName_, command_action pfHandler_, void* pvContext_)
{
    Set(szName_, pfHandler_, pvContext_);
}

//---------------------------------------------------------------------------
CommandHandler::CommandHandler()
{
    Set(0, 0, nullptr);
}

//---------------------------------------------------------------------------
void CommandHandler::Set(const char* szName_, command_action pfHandler_, void* pvContext_)
{
    m_szCommandName = szName_;
    m_pfHandler     = pfHandler_;
    m_pvContext     = pvContext_;
}

//---------------------------------------------------------------------------
const char* CommandHandler::Name()
{
    return m_szCommandName;
}

//---------------------------------------------------------------------------
void CommandHandler::Execute(TerminalIO* pclTerminalIO_, const char* szArgs_)
{
    if (m_pfHandler != 0) {
        m_pfHandler(pclTerminalIO_, szArgs_, m_pvContext);
    }
}
} // namespace Mark3

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

#include "mark3.h"
#include "driver.h"

#include "terminal_io.h"
namespace Mark3
{
//---------------------------------------------------------------------------
TerminalIO::TerminalIO()
{
    Init();
}

//---------------------------------------------------------------------------
bool TerminalIO::WriteByte(uint8_t u8Byte_)
{
    while (m_pclDriver->Write(&u8Byte_, 1) == 0u) { Thread::Sleep(5); }
    return true;
}

//---------------------------------------------------------------------------
bool TerminalIO::ReadByte(uint8_t* u8Byte_)
{
    while (m_pclDriver->Read(u8Byte_, 1) == 0u) { Thread::Sleep(5); }
    return true;
}
} // namespace Mark3

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

#include "cmd.h"
#include "getopt.h"
#include "string.h"
#include "m3shell.h"

namespace  {
using namespace Mark3;
constexpr auto maxArgs = 16;
constexpr auto whitespace = " \r\n\t";

} // anonymous namespace

namespace Mark3 {

Command::Command(const char* name_,
          Entrypoint_t entrypoint_)
    : m_name{name_}
    , m_entrypoint{entrypoint_}
{
    m_handler.Set(m_name, actionWrapper, this);
}

int Command::run(int argc_, const char** argv_) {
    return m_entrypoint(argc_, argv_);
}

void Command::registerHandler() {
    m_handler.Set(m_name, actionWrapper, this);
}

const char* Command::name() {
    return m_name;
}

CommandHandler* Command::getHandler() {
    return &m_handler;
}

void Command::actionWrapper(TerminalIO* pclTerminal_, const char* szArgs_, void* pvContext_)
{
    const char* argv[maxArgs];
    auto argc = int{};
    auto* cmd = reinterpret_cast<Command*>(pvContext_);

    argv[argc++] = (char*)cmd->name();
    for (auto* token = strtok((char*)szArgs_, whitespace);
         token && (argc < maxArgs);
         token = strtok(nullptr, whitespace)) {
        argv[argc++] = token;
    }

    // reset getopt externs.
    optind = 1;
    optopt = 0;
    optreset = 0;
    optarg = nullptr;

    cmd->run(argc, argv);
}

} // namespace Mark3

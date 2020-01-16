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

#include "cmd_testpattern.h"

#include "cmd.h"
#include "shell_env.h"
#include "stdio.h"
#include "getopt.h"

//---------------------------------------------------------------------------
namespace testpattern {
using namespace Mark3;

int main(int /*argc*/, const char** /*argv*/) {
    // Generate an SMPTE-like test-card in the console.
    auto t = TerminalIO{};
    auto* drv = DriverList::FindByPath("uart");

    t.SetDriver(drv);
    t.ClearScreen();
    for (auto i = 0; i < 19; i++) {
        for (auto j = 0; j < 7; j++) {
            switch (j) {
            case 0: t.SetBackColor(TerminalColor::White); break;
            case 1: t.SetBackColor(TerminalColor::Yellow); break;
            case 2: t.SetBackColor(TerminalColor::Cyan); break;
            case 3: t.SetBackColor(TerminalColor::Green); break;
            case 4: t.SetBackColor(TerminalColor::Magenta); break;
            case 5: t.SetBackColor(TerminalColor::Red); break;
            case 6: t.SetBackColor(TerminalColor::Blue); break;
            }

            for (auto k = 0; k < 11; k++) {
                t.WriteByte(' ');
            }
        }
        t.WriteByte('\n');
    }

    for (auto i = 0; i < 2; i++) {
        for (auto j = 0; j < 7; j++) {
            switch (j) {
            case 0: t.SetBackColor(TerminalColor::Blue); break;
            case 1: t.SetBackColor(TerminalColor::Black); break;
            case 2: t.SetBackColor(TerminalColor::Magenta); break;
            case 3: t.SetBackColor(TerminalColor::Black); break;
            case 4: t.SetBackColor(TerminalColor::Cyan); break;
            case 5: t.SetBackColor(TerminalColor::Black); break;
            case 6: t.SetBackColor(TerminalColor::White); break;
            }

            for (auto k = 0; k < 11; k++) {
                t.WriteByte(' ');
            }
        }
        t.WriteByte('\n');
    }

    for (auto i = 0; i < 3; i++) {
        for (auto j = 0; j < 2; j++) {
            switch (j) {
            case 0: t.SetBackColor(TerminalColor::White); break;
            case 1: t.SetBackColor(TerminalColor::Black); break;
            }

            for (auto k = 0; k < 38; k++) {
                t.WriteByte(' ');
            }
        }
        t.WriteByte('\n');
    }
    Thread::Sleep(1000);

    return 0;
}
} // namespace testpattern

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

#include "cmd_ls.h"

#include "cmd.h"
#include "shell_env.h"
#include "stdio.h"
#include "getopt.h"

//---------------------------------------------------------------------------
namespace ls {
using namespace Mark3;

int main(int /*argc*/, const char** /*argv*/) {
    auto* node = envPwd->children();

    while (node) {
        auto perms = node->perms();
        printf("-");
        for (auto i = 0; i < 3; i ++) {
            printf("%c", (perms & 0x400) ? 'r' : '-');
            printf("%c", (perms & 0x200) ? 'w' : '-');
            printf("%c", (perms & 0x100) ? 'x' : '-');
            perms <<= 3;
        }
        printf("\t%d:%d\t%d\t%s\n", node->user(), node->group(), node->size(), node->name());

        node = node->GetNext();
    }

    return 0;
}
} // namespace ls

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

#include "cmd_pwd.h"

#include "cmd.h"
#include "shell_env.h"
#include "stdio.h"
#include "getopt.h"

//---------------------------------------------------------------------------
namespace pwd {
using namespace Mark3;

int main(int /*argc*/, const char** /*argv*/) {
    const char* pathv[10];
    auto pathc = 0;
    auto* node = envPwd;
    while (node && (pathc < 10)) {
        pathv[pathc++] = node->name();
        node = node->parent();
    }
    pathc--;
    printf("/");
    while (pathc) {
        printf("%s/", pathv[--pathc]);
    }
    return 0;
}
} // namespace pwd

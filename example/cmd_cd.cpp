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

#include "cmd_cd.h"

#include "cmd.h"
#include "shell_env.h"
#include "stdio.h"

namespace cd {
using namespace Mark3;

int main(int argc, const char** argv) {
    if (argc < 2) {
        printf("no path\n");
        return -1;
    }
    auto* dirNode = envPwd;
    if (argv[1][0] == '/') {
        dirNode = &rootDir;
    }
    dirNode = dirNode->handlePath(argv[1]);
    if (!dirNode) {
        printf("Invalid Directory: %s\n", argv[1]);
        return -1;
    }
    envPwd = dirNode;
    return 0;
}
} // namespace cd

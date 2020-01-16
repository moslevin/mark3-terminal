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

#include "cmd_args.h"

#include "cmd.h"
#include "shell_env.h"
#include "stdio.h"
#include "getopt.h"

//---------------------------------------------------------------------------
namespace argprint {
using namespace Mark3;

int main(int argc, const char** argv)   {
    for (auto i = 0; i < argc; i++) {
        printf("%d:%s\n", i, argv[i]);
    }
    return 0;
}
} // namespace argprint


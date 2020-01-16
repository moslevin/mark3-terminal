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

#include "cmd_readmem.h"

#include "cmd.h"
#include "shell_env.h"
#include "stdio.h"
#include "stdlib.h"
#include "getopt.h"

//---------------------------------------------------------------------------
namespace readmem {
using namespace Mark3;

void usage() {
    printf("readmem -a <address> -s <size>\n");
}

int main(int argc, const char** argv) {
    auto foundAddress = false;
    auto foundSize = false;
    auto address = (uint8_t*){nullptr};
    auto size = K_ADDR{};
    auto opt = int{};

    while ((opt = getopt(argc, (char* const*)argv, "a:s:")) != -1) {
        switch (opt) {
        case 'a': {
            auto tmp = static_cast<K_ADDR>(atoi(optarg));
            address = (uint8_t*)tmp;
            foundAddress = true;
        } break;
        case 's': {
            size = static_cast<K_ADDR>(atoi(optarg));
            foundSize = true;
        } break;
        case '?':
        default: {
            printf("unknown option\n");
            usage();
            return -1;
        }
        }
    }

    if (!foundAddress || !foundSize) {
        usage();
        return -1;
    }

    for (auto i = address; i < (address + size + 15); i+= 16) {
        for (auto j = 0; (j < 16) && ((j + i) < (address + size)); j++) {
            if (j == 0) {
                printf("0x%x: ", (unsigned int)(i + j));
            }
            printf("%02X ", (unsigned int)*(i + j));
        }
        printf("\n");
    }

    return 0;
}
} // namespace readmem

#include <mark3.h>
#include <stdint.h>

#include "terminal_io.h"
#include "m3shell.h"
#include "ll.h"
#include "m3_io.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "drvUARTplus.h"

#include "cmd.h"
#include "cmd_args.h"
#include "cmd_cd.h"
#include "cmd_dumpstack.h"
#include "cmd_ls.h"
#include "cmd_pwd.h"
#include "cmd_readmem.h"
#include "cmd_testpattern.h"
#include "cmd_threads.h"
#include "cmd_unknown.h"
#include "cmd_uptime.h"

#include "node_dev.h"
#include "node_dir.h"

namespace {
using namespace Mark3;
//---------------------------------------------------------------------------
TypedDoubleLinkList<Command> commandManager;

namespace help {
int main(int /*argc*/, const char** /*argv*/) {
    printf("available commands:\n");
    auto* node = commandManager.GetHead();
    while (node) {
        printf("\t%s\n", node->name());
        node = node->GetNext();
    }
    return 0;
}
} // namespace help

//---------------------------------------------------------------------------
Command cmdArgs{"args", argprint::main};
Command cmdCd{"cd", cd::main};
Command cmdDumpstack{"dumpstack", dumpstack::main};
Command cmdHelp{"help", help::main};
Command cmdLs{"ls", ls::main};
Command cmdPwd{"pwd", pwd::main};
Command cmdReadmem{"readmem", readmem::main};
Command cmdTestPattern{"testpattern", testpattern::main};
Command cmdThreads{"threads", threads::main};
Command cmdUnknown{"unknown", unknown::main};
Command cmdUptime{"uptime", uptime::main};

//---------------------------------------------------------------------------
uint8_t rxBuffer[32];
uint8_t txBuffer[32];
auto uart = ATMegaUARTPlus{};

DirNode devDir{"dev", &rootDir};
DirNode sysDir{"sys", &rootDir};
DirNode homeDir{"home", &rootDir};
DirNode moHomeDir{"moslevin", &homeDir};
DevNode devUart{"uart", &devDir, &uart};

auto shell = M3Shell{};

auto appThread = Thread{};
K_WORD appStack[PORT_KERNEL_DEFAULT_STACK_SIZE * 2];

auto idleThread = Thread{};
K_WORD idleStack[PORT_KERNEL_DEFAULT_STACK_SIZE];

} // anonymous namespace

//---------------------------------------------------------------------------
void registerCommands() {
    commandManager.Add(&cmdArgs);
    commandManager.Add(&cmdCd);
    commandManager.Add(&cmdDumpstack);
    commandManager.Add(&cmdHelp);
    commandManager.Add(&cmdLs);
    commandManager.Add(&cmdPwd);
    commandManager.Add(&cmdReadmem);
    commandManager.Add(&cmdTestPattern);
    commandManager.Add(&cmdThreads);
    commandManager.Add(&cmdUnknown);
    commandManager.Add(&cmdUptime);
}

//---------------------------------------------------------------------------
void appTask(void* /* arg */) {
    // open uart...
    uart.Init();
    {
        uint32_t baud = 57600;
        uart.Control(UART_OPCODE_SET_BAUDRATE, &baud, 0, 0, 0);
    }
    uart.Control(UART_OPCODE_SET_BUFFERS, rxBuffer, sizeof(rxBuffer), txBuffer, sizeof(txBuffer));
    uart.Control(UART_OPCODE_SET_BLOCKING, 0, 0, 0, 0);
    uart.Open();

    // stdin/stdout/stderr all redirect to uart...
    m3_io_set(&uart, 0);
    m3_io_set(&uart, 1);
    m3_io_set(&uart, 2);

    // attach terminal/shell to uart
    shell.Init();
    shell.SetDriver(&uart);
    shell.SetPrompt("Mark3$ ");
    shell.SetDefaultHandler(cmdUnknown.getHandler());
    registerCommands();
    auto* node = commandManager.GetHead();
    while (node) {
        shell.AddCommand(node->getHandler());
        node = node->GetNext();
    }
    while(1) {
        shell.InputLoop();
    }
}

//---------------------------------------------------------------------------

void idleTask(void* /* arg */) {    
    while (1) {
        // do nothing
    }
}

//---------------------------------------------------------------------------
int main(void)
{
    Kernel::Init();

    appThread.Init(appStack, sizeof(appStack), 1, appTask, nullptr);
    appThread.SetName("shell");
    appThread.Start();

    idleThread.Init(idleStack, sizeof(idleStack), 0, idleTask, nullptr);
    idleThread.SetName("idle");
    idleThread.Start();

    uart.SetName("uart");
    DriverList::Add(&uart);

    Kernel::Start();

    return 0;
}

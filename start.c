#include "uart.h"
#include "print.h"

void start(void) {
    uartinit();
    puts("hello\n");
    __builtin_unreachable();
}

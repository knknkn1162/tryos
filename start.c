#include "asm.h"
#include "const.h"
#include "types.h"
#include "uart.h"
#include "print.h"

int getcmd(char *buf, int nbuf) {
    puts("$ ");
    buf[0] = 0;
    gets(buf, nbuf);
    if(buf[0] == 0) return -1;
    return 0;
}

void start(void) {
    puts("hello\n");
    char buf[100];
    while(getcmd(buf, sizeof(buf)) >= 0) {
        puts("> ");
        puts(buf);
        puts("\n");
    }
    __builtin_unreachable();
}

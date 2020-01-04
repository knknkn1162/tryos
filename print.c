#include "uart.h"

void putc(char c) {
    uartputc(c);
}

void puts(const char *str) {
    int i;
    for(i = 0; str[i]; i++){
        putc(str[i]);
    }
}

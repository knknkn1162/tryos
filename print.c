#include "uart.h"

void putc(char c) {
    uartputc(c);
}

char getc(void) {
    return uartgetc();
}

void puts(const char *str) {
    int i;
    for(i = 0; str[i]; i++){
        putc(str[i]);
    }
}

char *gets(char *buf, int max) {
    int i;
    for(i = 0; i < max;) {
        char c = getc();
        if(c == 0) continue;
        buf[i++] = c;
        putc(c);
        if(c == '\n' || c == '\r') break;
    }
    buf[i] = 0;
    return buf;
}

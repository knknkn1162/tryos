#define UART0 0x10000000L
#define UART0_IRQ 10

#define UART0_BASE ((volatile unsigned char *)(UART0))
#define TRANSMIT_HOLDING_REGISTER 0 // receive holding register (for input bytes)
#define LINE_STATUS_REGISTER 5
#define TRANSMIT_HOLDING_EMPTY (1<<5)



void uartinit(void) {
    return;
}

void uartputc(char c) {
    while(!(UART0_BASE[LINE_STATUS_REGISTER] & TRANSMIT_HOLDING_EMPTY)) ;
    UART0_BASE[TRANSMIT_HOLDING_REGISTER] = c;
    return;
}

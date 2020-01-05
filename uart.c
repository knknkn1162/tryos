#define UART0 0x10000000L
#define UART0_IRQ 10

#define UART0_BASE ((volatile unsigned char *)(UART0))
// see http://www.ti.com/lit/ds/symlink/pc16550d.pdf
#define RECEIVE_HOLDING_REGISTER 0

#define TRANSMIT_HOLDING_REGISTER 0 // receive holding register (for input bytes)
#define LINE_STATUS_REGISTER 5
#define DATA_READY (0x01)
#define TRANSMIT_HOLDING_EMPTY (1<<5)

void uartputc(char c) {
    while(!(UART0_BASE[LINE_STATUS_REGISTER] & TRANSMIT_HOLDING_EMPTY)) ;
    UART0_BASE[TRANSMIT_HOLDING_REGISTER] = c;
    return;
}

char uartgetc(void) {
    if(UART0_BASE[LINE_STATUS_REGISTER] & DATA_READY) {
        return UART0_BASE[RECEIVE_HOLDING_REGISTER];
    } else {
        return 0;
    }
}

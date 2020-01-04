#define UART0 0x10000000L
#define UART0_IRQ 10

#define UART0_BASE ((volatile unsigned char *)(UART0))
#define RECEIVE_HOLDING_REGISTER 0
#define TRANSMIT_HOLDING_REGISTER 0 // receive holding register (for input bytes)
#define INTERRUPT_ENABLE_REGISTER 1
#define FIFO_CONTROL_REGISTER 2
#define INTERRUPT_STATUS_REGISTER 2
#define LINE_CONTROL_REGISTER 3
#define LSB_BAUD_RATE 0
#define MSB_BAUD_RATE 1
#define LINE_STATUS_REGISTER 5
#define TRANSMIT_HOLDING_EMPTY (1<<5)



void uartinit(void) {
    // disable interrupts.
    UART0_BASE[INTERRUPT_ENABLE_REGISTER] = 0x00;

    // special mode to set baud rate.
    UART0_BASE[LINE_CONTROL_REGISTER] = 0x80;
    // LSB for baud rate of 38.4K.
    UART0_BASE[LSB_BAUD_RATE] = 0x03;
    UART0_BASE[MSB_BAUD_RATE] = 0x00;
    // leave set-baud mode,
    UART0_BASE[LINE_CONTROL_REGISTER] = 0x03;
    // reset and enable FIFOs.
    UART0_BASE[FIFO_CONTROL_REGISTER] = 0x07;
    // enable receive interrupts.
    UART0_BASE[INTERRUPT_ENABLE_REGISTER] = 0x01;
    return;
}

void uartputc(char c) {
    while(!(UART0_BASE[LINE_STATUS_REGISTER] & TRANSMIT_HOLDING_EMPTY)) ;
    UART0_BASE[TRANSMIT_HOLDING_REGISTER] = c;
    return;
}

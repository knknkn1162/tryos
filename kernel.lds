OUTPUT_ARCH("riscv")
ENTRY(_entry)

SECTIONS {
    /* FW_TEXT_START=0x80000000 */
    . = 0x80000000;
    .text :
    {
        *(.text)
        . = ALIGN(0x1000);
    }

    . = ALIGN(0x1000);
    PROVIDE(etext = .);

    .data : {
        *(.data)
    }
    .bss : {
        *(.bss)
        PROVIDE(end = .);
    }
}

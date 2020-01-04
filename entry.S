.section .data
.globl stack0

.section .text
.globl _entry
_entry:
    la sp, stack0
    call start
_loop:
    j _loop

.comm stack0, 4096, 16

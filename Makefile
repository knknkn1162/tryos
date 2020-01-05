CC = riscv64-unknown-elf-gcc
GDB = riscv64-unknown-elf-gdb
DEBUG = -g
# medany: which means the program and its statically defined symbols must lie within any single 2 GiB address range.
# -nostdlib -fno-builtin: freestanding; ignoring waring, "conflicting types for built-in function"
CFLAGS = -nostdlib -fno-builtin $(DEBUG) -mcmodel=medany
ASFLAGS = ${CFLAGS}
LD = riscv64-unknown-elf-ld
QEMU = qemu-system-riscv64
GDB_PORT = 8889
DEBUG_OPTION = -gdb tcp::${GDB_PORT} -S
MEMORY_SIZE = 512M

.PHONY: all run clean

all: clean kernel

#(GCC) -c entry.S -o entry.o
# riscv64-unknown-elf-ld -T kernel.lds entry.o -o kernel
kernel: entry.o uart.o print.o start.o
	$(LD) -T kernel.lds $^ -o $@

run:
	make debug-run DEBUG_OPTION=""

debug-run: kernel
	$(QEMU) -machine virt -bios none -kernel $^ -m ${MEMORY_SIZE} -nographic $(DEBUG_OPTION)

debug:
	$(GDB) -ex "target remote localhost:$(GDB_PORT)" kernel
clean:
	$(RM) *.o kernel

# tryOS

This is tiny OS base on xv6-riscv

# Reference

+ https://gist.github.com/knknkn1162/60c46e896bfdbd8d6e5b3fdc3d865a7d

# TODO

1. M-mode onlyでもある程度動作できるようにする

+ puts < printf
+ diskのread/write

2. U-modeを加える。

3. S-modeを加えて、pagingを有効にする

# 0x80000000 にブレークポイントを貼りたい。

```sh
qemu-system-riscv64 -machine virt -bios none -kernel kernel -m 3G -nographic -gdb tcp::8889 -S
# other terminal..
$ riscv64-unknown-elf-gdb -ex "target remote localhost:8889" kernel -ex "b _entry" -ex "c"
$ b _entry
Breakpoint 1 at 0x80000000: file entry.S, line 7.
$ c
```

0x1000 -> 0x8000_0000 にとぶ。詳しくは、https://github.com/qemu/qemu/blob/v4.1.0/hw/riscv/virt.c#L53-L68 を参照にすると良い。

# entrypointをきちんと仕掛ける

```
# Makefile
kernel: entry.o $(OBJS)
	$(LD) -T kernel.lds $^ -o $@
```

のように、entrypointのファイルを最初にlinkさせるようにする。

```sh
# riscv64-unknown-elf-objdump -d kernel

kernel:     file format elf64-littleriscv


Disassembly of section .text:

0000000080000000 <_entry>:
    80000000:	00001117          	auipc	sp,0x1
    80000004:	00010113          	mv	sp,sp
    80000008:	01a000ef          	jal	ra,80000022 <_start>

000000008000000c <_loop>:
    8000000c:	a001                	j	8000000c <_loop>

000000008000000e <_main>:
```

で確認できる

# ベアメタル上での作業なので、built-in functionに関するcompile warningを消したい

`-nostdlib -fno-builtin`をつけると良い。https://ja.wikipedia.org/wiki/%E3%83%95%E3%83%AA%E3%83%BC%E3%82%B9%E3%82%BF%E3%83%B3%E3%83%87%E3%82%A3%E3%83%B3%E3%82%B0%E7%92%B0%E5%A2%83 を参考にすること。

```
print.c:3:6: warning: conflicting types for built-in function 'putc'; expected 'int(int,  void *)' [-Wbuiltin-declaration-mismatch]
    3 | void putc(char c) {
      |      ^~~~
print.c:2:1: note: 'putc' is declared in header '<stdio.h>'
    1 | #include "uart.h"
  +++ |+#include <stdio.h>
    2 |
```

OUTPUT=bin/oskrnl.elf

CC=clang-14
CUSTOM_CCFLAGS?=-g -O2 -pipe -Wall -Wextra
override INCLUDE_CCFLAGS=-Isrc/klibc -Isrc -Isrc/mm
override CCFLAGS=$(INCLUDE_CCFLAGS) -mgeneral-regs-only \
	-std=c11 -ffreestanding -fno-stack-protector \
	-fno-stack-check -fno-lto -fno-pie -fno-pic -m64 \
	-march=x86-64 -mabi=sysv -mno-80387 -mno-red-zone -mcmodel=kernel $(CUSTOM_CCFLAGS)

AS=nasm
CUSTOM_ASFLAGS?=-F dwarf -g
override ASFLAGS=-f elf64 $(CUSTOM_ASFLAGS)

LD=ld
CUSTOM_LDFLAGS?=
override LDFLAGS=-nostdlib -static -m elf_x86_64 -z max-page-size=0x1000 \
	-T linker.ld

CCFILES=boot.c mm/phys.c cpu/gdt.c klibc/string.c cpu/idt/idt.c cpu/idt/idt_handlers.c print.c \
		klibc/stdio.c
ASFILES=cpu/gdt.s

CCSOURCES=$(addprefix src/,$(CCFILES))
ASSOURCES=$(addprefix src/,$(ASFILES))

CCBUILD=$(addsuffix .obj,$(addprefix bin/,$(CCFILES)))
ASBUILD=$(addsuffix .obj,$(addprefix bin/,$(ASFILES)))

all: $(OUTPUT)

bin/%.c.obj: src/%.c
	mkdir -p bin/$(dir $(subst src/,,$^))
	$(CC) $^ $(CCFLAGS) -c -o $@

bin/%.s.obj: src/%.s
	mkdir -p bin/$(dir $(subst src/,,$^))
	$(AS) $(ASFLAGS) $^ -o $@

$(OUTPUT): $(ASBUILD) $(CCBUILD)
	$(LD) $(LDFLAGS) $^ -o $@

clean:
	echo $(CCBUILD)
	rm -rf bin/
	mkdir -p bin/

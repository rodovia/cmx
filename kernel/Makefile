OUTPUT=bin/oskrnl.elf
TARGET_ARCH?=x86_64
ARCH_CCFLAGS=-m64 -mno-red-zone -march=x86-64
ARCH_ASFLAGS=-f elf64
ARCH_LDFLAGS=-m elf_x86_64

ifeq ($(TARGET_ARCH),i386)
ARCH_CCFLAGS=-m32 -march=i386
ARCH_ASFLAGS=-f elf32
ARCH_LDFLAGS=-m elf_i386
endif

CC=clang-14
CUSTOM_CCFLAGS?=-g -O2 -pipe -Wall -Wextra
override INCLUDE_CCFLAGS=-Isrc/klibc -Isrc -Isrc/mm
override CCFLAGS=$(INCLUDE_CCFLAGS) $(ARCH_CCFLAGS) \
	-mgeneral-regs-only -std=c11 -ffreestanding -fno-stack-protector \
	-fno-stack-check -fno-lto -fno-pie -fno-pic \
	-mabi=sysv -mno-80387 -mcmodel=kernel $(CUSTOM_CCFLAGS)

AS=nasm
CUSTOM_ASFLAGS?=-F dwarf -g
override ASFLAGS=$(ARCH_ASFLAGS) $(CUSTOM_ASFLAGS)

LD=ld
CUSTOM_LDFLAGS?=
override LDFLAGS=-nostdlib -static $(ARCH_LDFLAGS) \
	-T linker.ld

CCFILES=boot.c mm/physical/phys.c cpu/gdt.c klibc/string.c cpu/idt/idt.c cpu/idt/idt_handlers.c print.c \
		klibc/stdio.c mm/physical/bucket/malloc.c mm/physical/bucket/bck.c
ASFILES=cpu/gdt.s

CCSOURCES=$(addprefix src/,$(CCFILES))
ASSOURCES=$(addprefix src/,$(ASFILES))

CCBUILD=$(addsuffix .obj,$(addprefix bin/,$(CCFILES)))
ASBUILD=$(addsuffix .obj,$(addprefix bin/,$(ASFILES)))

all: $(OUTPUT)

bin/%.c.obj: src/%.c
	echo $(TARGET_ARCH)
	mkdir -p bin/$(dir $(subst src/,,$^))
	$(CC) $^ $(CCFLAGS) -c -o $@

bin/%.s.obj: src/%.s
	mkdir -p bin/$(dir $(subst src/,,$^))
	$(AS) $(ASFLAGS) $^ -o $@

$(OUTPUT): $(ASBUILD) $(CCBUILD)
	$(LD) $(LDFLAGS) $^ -o $@

clean:
	rm -rf bin/
	mkdir -p bin/

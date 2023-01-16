KE_OUTPUT=kernel/bin/oskrnl.elf
TARGET_ARCH?=x86_64
ISO_OUTPUT=cmx-$(TARGET_ARCH).iso

all: $(KE_OUTPUT) iso/$(ISO_OUTPUT)
.PHONY: $(KE_OUTPUT)

$(KE_OUTPUT):
	make -C kernel TARGET_ARCH=$(TARGET_ARCH)

iso/$(ISO_OUTPUT): $(KE_OUTPUT)
	mkdir -p iso/root
	cp -v $(KE_OUTPUT) limine.cfg limine/limine.sys \
	limine/limine-cd.bin limine/limine-cd-efi.bin iso/root/
	xorriso -as mkisofs -b limine-cd.bin \
			-no-emul-boot -boot-load-size 4 -boot-info-table \
			--efi-boot limine-cd-efi.bin \
			-efi-boot-part --efi-boot-image --protective-msdos-label \
			iso/root/ -o iso/$(ISO_OUTPUT)
	./limine/limine-deploy iso/$(ISO_OUTPUT)

clean:
	rm -rf iso/
	make -C kernel clean

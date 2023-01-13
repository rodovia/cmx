;gdtr dw 0
;     dq 0

global GdtSet1
GdtSet1:
    lgdt  [rdi]
    mov ax, 0x30
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    pop rdi
    mov rax, 0x28
    push rax
    push rdi
    retfq

global GdtReload
GdtReload:
   ; Reload CS register:
    PUSH  0x28               ; Push code segment to stack, 0x08 is a stand-in for your code segment
    lea rax, [rel .reload_CS] ; Load address of .reload_CS into RAX
    push rax                  ; Push this value to the stack
    retfq                     ; Perform a far return, RETFQ or LRETQ depending on syntax
.reload_CS:
   ; Reload data segment registers
    mov   AX, 0x30 ; 0x10 is a stand-in for your data segment
    mov   DS, AX
    mov   ES, AX
    mov   FS, AX
    mov   GS, AX
    mov   SS, AX
    ret

global GdtTssReload
GdtTssReload:
    mov ax, 0x48
    ltr ax
    ret

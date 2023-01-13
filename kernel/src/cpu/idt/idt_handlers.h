#pragma once

#include "idt.h"

void _isr0(interrupt_frame_t* frame);
void _isr1(interrupt_frame_t* frame);
void _isr2(interrupt_frame_t* frame);
void _isr3(interrupt_frame_t* frame);
void _isr4(interrupt_frame_t* frame);
void _isr5(interrupt_frame_t* frame);
void _isr6(interrupt_frame_t* frame);
void _isr7(interrupt_frame_t* frame);
void _isr8(interrupt_frame_t* frame, uword_t error);
void _isr9(interrupt_frame_t* frame);
void _isr10(interrupt_frame_t* frame, uword_t error);
void _isr11(interrupt_frame_t* frame, uword_t error);
void _isr12(interrupt_frame_t* frame, uword_t error);
void _isr13(interrupt_frame_t* frame, uword_t error);
void _isr14(interrupt_frame_t* frame, uword_t error);
void _isr15(interrupt_frame_t* frame);
void _isr16(interrupt_frame_t* frame);
void _isr17(interrupt_frame_t* frame, uword_t error);
void _isr18(interrupt_frame_t* frame);
void _isr19(interrupt_frame_t* frame);
void _isr20(interrupt_frame_t* frame);
void _isr21(interrupt_frame_t* frame, uword_t error);
void _isr22(interrupt_frame_t* frame);
void _isr23(interrupt_frame_t* frame);
void _isr24(interrupt_frame_t* frame);
void _isr25(interrupt_frame_t* frame);
void _isr26(interrupt_frame_t* frame);
void _isr27(interrupt_frame_t* frame);
void _isr28(interrupt_frame_t* frame);
void _isr29(interrupt_frame_t* frame, uword_t error);
void _isr30(interrupt_frame_t* frame, uword_t error);
void _isr31(interrupt_frame_t* frame);

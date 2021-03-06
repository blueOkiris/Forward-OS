;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;
;    This file is part of Forward OS.                                           ;
;                                                                               ;
;    Forward OS is free software: you can redistribute it and/or modify         ;
;    it under the terms of the GNU General Public License as published by       ;
;    the Free Software Foundation, either version 3 of the License, or          ;
;    (at your option) any later version.                                        ;
;                                                                               ;
;    Batch Interpret is distributed in the hope that it will be useful,         ;
;    but WITHOUT ANY WARRANTY; without even the implied warranty of             ;
;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              ;
;    GNU General Public License for more details.                               ;
;                                                                               ;
;    You should have received a copy of the GNU General Public License          ;
;    along with Batch Interpret. If not, see <http://www.gnu.org/licenses/>.    ;
; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; ;

; 32 Bit OS
bits 32

; Initiallizer to set up external functions
section .text
align 4
	align 4
	dd 0x1BADB002
	dd 0x00
	dd - (0x1BADB002 + 0x00)
global start
global read_port
global write_port
global load_idt
global keyboard_handler
global halt

extern main

; Sets up OS and then calls main function
start:
	cli
	mov esp, stack_space
	
	call main
	hlt

; Global asm function for IO ports for use in c
read_port:
	mov edx, [esp + 4]
	in al, dx
	ret
write_port:
	mov edx, [esp + 4]
	mov al, [esp + 4 + 4]
	out dx, al
	ret

; Global cpu halt function to be called from system.c
halt:
	hlt
	ret

; Functions for gdt
global gdt_flush
extern gp
gdt_flush:
    lgdt [gp]
	mov ax, 0x10
	mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2
flush2:
    ret

; Functions for idt
global idt_load
extern idtp
idt_load:
    lidt [idtp]
    ret

; Isr function calls
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31
isr0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_stub
isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub
isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub
isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_stub
isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_stub
isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_stub
isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_stub
isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub
isr8:
    cli
    push byte 8
    jmp isr_common_stub
isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_stub
isr10:
    cli
    push byte 10
    jmp isr_common_stub
isr11:
    cli
    push byte 11
    jmp isr_common_stub
isr12:
    cli
    push byte 12
    jmp isr_common_stub
isr13:
    cli
    push byte 13
    jmp isr_common_stub
isr14:
    cli
    push byte 14
    jmp isr_common_stub
isr15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_stub
isr16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_stub
isr17:
    cli
    push byte 0
    push byte 17
    jmp isr_common_stub
isr18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_stub
isr19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_stub
isr20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_stub
isr21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_stub
isr22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_stub
isr23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_stub
isr24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_stub
isr25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_stub
isr26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_stub
isr27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_stub
isr28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_stub
isr29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_stub
isr30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_stub
isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub
extern fault_handler
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, fault_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

; IRQ function calls
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15
irq0:
    cli
    push byte 0
    push byte 32
    jmp irq_common_stub
irq1:
    cli
    push byte 0
    push byte 33
    jmp irq_common_stub
irq2:
    cli
    push byte 0
    push byte 34
    jmp irq_common_stub
irq3:
    cli
    push byte 0
    push byte 35
    jmp irq_common_stub
irq4:
    cli
    push byte 0
    push byte 36
    jmp irq_common_stub
irq5:
    cli
    push byte 0
    push byte 37
    jmp irq_common_stub
irq6:
    cli
    push byte 0
    push byte 38
    jmp irq_common_stub
irq7:
    cli
    push byte 0
    push byte 39
    jmp irq_common_stub
irq8:
    cli
    push byte 0
    push byte 40
    jmp irq_common_stub
irq9:
    cli
    push byte 0
    push byte 41
    jmp irq_common_stub
irq10:
    cli
    push byte 0
    push byte 42
    jmp irq_common_stub
irq11:
    cli
    push byte 0
    push byte 43
    jmp irq_common_stub
irq12:
    cli
    push byte 0
    push byte 44
    jmp irq_common_stub
irq13:
    cli
    push byte 0
    push byte 45
    jmp irq_common_stub
irq14:
    cli
    push byte 0
    push byte 46
    jmp irq_common_stub
irq15:
    cli
    push byte 0
    push byte 47
    jmp irq_common_stub
extern irq_handler
irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp

    push eax
    mov eax, irq_handler
    call eax
    pop eax

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

; Start data for stack
section .bss
resb 16384
stack_space:

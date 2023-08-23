bits 64

section .text
    extern ISR_ExceptionHandler

exceptionHandler:
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp

    mov ax, 0x10          ; load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call ISR_ExceptionHandler

    pop rbx             ; restore kernel data segment
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    add rdi, 0x08

    sti
    iret

%macro EXCEPTION 1
  global exception%1
  exception%1:
    cli
    push byte 0
    push %1
    jmp exceptionHandler
%endmacro

EXCEPTION 0
EXCEPTION 1
EXCEPTION 2
EXCEPTION 3
EXCEPTION 4
EXCEPTION 5
EXCEPTION 6
EXCEPTION 7
EXCEPTION 8
EXCEPTION 9
EXCEPTION 10
EXCEPTION 11
EXCEPTION 12
EXCEPTION 13
EXCEPTION 14
EXCEPTION 15
EXCEPTION 16
EXCEPTION 17
EXCEPTION 18
EXCEPTION 19
EXCEPTION 20
EXCEPTION 21
EXCEPTION 22
EXCEPTION 23
EXCEPTION 24
EXCEPTION 25
EXCEPTION 26
EXCEPTION 27
EXCEPTION 28
EXCEPTION 29
EXCEPTION 30
EXCEPTION 31
EXCEPTION 128
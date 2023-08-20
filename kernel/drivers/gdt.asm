global install_gdt
global reloadSegments
extern gdt_ptr

install_gdt:
   lgdt [gdt_ptr]

   ret

reloadSegments:
    ; Reload CS register
    call reload_CS
    retf

reload_CS:
    ; Reload data segment registers
    mov ax, 0x10  ; Load data segment selector (replace with actual data segment index)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
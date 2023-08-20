global install_gdt
extern gdt_ptr

install_gdt:
   lgdt [gdt_ptr]

   mov ax, 0x10
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax

   push 0x08
   push .flush
   retfq

.flush:
   ret
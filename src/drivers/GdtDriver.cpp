#include <drivers/GdtDriver.hpp>
#include <def.h>

extern "C" {
    #include <string.h>
}

#ifdef DEBUG
    #include <Logger.hpp>
#endif

GDT_ENTRY gdt[NO_GDT_DECRIPTORS];
GDT_PTR gdt_ptr;

void gdtDriver::set_gate(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    GDT_ENTRY* entry = &gdt[index];
    
    entry->base_low = base & 0xFFFF;
    entry->base_middle = (base >> 16) & 0xFF;
    entry->base_high = (base >> 24) & 0xFF;

    entry->limit_low = limit & 0xFFFF;
    entry->gran = (limit >> 16) & 0x0F;

    entry->gran |= gran & 0xF0;
    entry->access = access;
}

gdtDriver::gdtDriver() { }

void gdtDriver::init() {
    // setup gdt_ptr
    gdt_ptr.limit = sizeof (gdt) -1;
    gdt_ptr.base = (uint64_t)gdt;

    // setup gdt
    
    this->set_gate(0, 0, 0, 0, 0); // null segment
    this->set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // kernel code segment
    this->set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // kernel data segment
    this->set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // user code segment
    this->set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // user data segment

    // install gdt
    asm volatile("lgdt %0" : : "m"(gdt_ptr));

    asm volatile(
        "mov %0, %%ds\n\t"
        "mov %0, %%es\n\t"
        "mov %0, %%fs\n\t"
        "mov %0, %%gs\n\t"
        "mov %0, %%ss\n\t"
        "pushq $0x8\n\t"
        "pushq $0f\n\t"
        "lretq\n"
        "0:"
        :: "r"(0x10)
    );

#ifdef DEBUG
    Logger.sucess("sucessfuly inited gdt");
#endif
}

extern gdtDriver GdtDriver = gdtDriver();
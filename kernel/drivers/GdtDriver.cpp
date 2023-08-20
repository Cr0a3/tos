#include <drivers/GdtDriver.hpp>
#include <def.h>

#ifdef DEBUG
    #include <Logger.hpp>
#endif
extern "C" void install_gdt();

GDT_ENTRY gdt[256];
GDT_PTR gdt_ptr;

void gdtDriver::set_gate(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    GDT_ENTRY* current = &gdt[index];
    
    current->limit_low = limit & 0xFFFF;
    current->base_low = base & 0xFFFF;
    current->base_middle = (base >> 16) & 0xFF;
    current->access = access;

    current->gran = (limit >> 16) & 0x0F;
    current->gran = current->gran | (gran & 0xF0);

    current->base_high = (base >> 24 & 0xFF);
}

gdtDriver::gdtDriver() { }

void gdtDriver::init() {
    // setup gdt_ptr
    gdt_ptr.limit = (sizeof (gdt) * 3) -1;
    gdt_ptr.base = (uint64_t)&gdt;

    // setup gdt
    this->set_gate(0, 0, 0, 0, 0); // null segment
    this->set_gate(0x8, 0x00400000, 0x003FFFFF, 0x9a, 0xc); // kernl code segment
    this->set_gate(0x10, 0x00800000, 0x003FFFFF, 0x92, 0xc); //kernel data segment

    // install gdt
    install_gdt();

#ifdef DEBUG
    Logger.sucess("sucessfuly inited gdt");
#endif
}

extern gdtDriver GdtDriver = gdtDriver();
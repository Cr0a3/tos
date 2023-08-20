#include <drivers/GdtDriver.hpp>
#include <def.h>

extern "C" {
    #include <string.h>
}

#ifdef DEBUG
    #include <Logger.hpp>
#endif
extern "C" void install_gdt();
extern "C" void reloadSegments();

GDT_ENTRY gdt[3];
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
    gdt_ptr.limit = sizeof (gdt) -1;
    gdt_ptr.base = (uint64_t)&gdt;

    // setup gdt
    this->set_gate(0, 0, 0, 0, 0); // null segment
    this->set_gate(1, 0, 0xFFFFFFFF, 0x9a, 0xC0); // kernl code segment
    this->set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xC0); //kernel data segment

    // install gdt
    Logger.info("installing gdt");
    install_gdt();
    Logger.info("reloading segments");
    reloadSegments();
    Logger.info("reloaded segments");

#ifdef DEBUG
    Logger.sucess("sucessfuly inited gdt");
#endif
}

extern gdtDriver GdtDriver = gdtDriver();
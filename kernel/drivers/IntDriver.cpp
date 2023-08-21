#include <drivers/IntDriver.hpp>
#include <def.h>
#include <panic.hpp>

#ifdef PIC
    #include <drivers/IoDriver.hpp>
#endif

#ifdef DEBUG
    #include <Logger.hpp>
#endif

IDT idt[256];
IDT_PTR idt_ptr;

intDriver::intDriver() {}

void intDriver::set_idtEntry(int index, uint64_t base, uint16_t seg_sel, uint8_t flags) {
    IDT *entry = &idt[index];

    entry->base_low = base & 0xFFFFFFFF;
    entry->segment_selector = seg_sel;
    entry->zero = 0;
    entry->type = flags | 0x60;
    entry->base_high = (base >> 32) & 0xFFFFFFFF;
}

void intDriver::init() {
#ifdef PIC
    // init master-pic
    IoDriver.outb(0x20, 0x11); 
    IoDriver.outb(0x21, 0x20);
    IoDriver.outb(0x21, 0x04);
    IoDriver.outb(0x21, 0x01); 

    // init slave-pic
    IoDriver.outb(0xa0, 0x11); 
    IoDriver.outb(0xa1, 0x28);
    IoDriver.outb(0xa1, 0x02); 
    IoDriver.outb(0xa1, 0x01);

    // activate all irqs
    IoDriver.outb(0x21, 0x0);
    IoDriver.outb(0xa1, 0x0);
#else
    panic("interrupt system just work with pic");
#endif
    // init idt_ptr
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base_address = (uint64_t)&idt;

    //install entries
    this->set_idtEntry(0, (uint64_t)exception0, 0x08, 0x8E);
    this->set_idtEntry(1, (uint64_t)exception1, 0x08, 0x8E);
    this->set_idtEntry(2, (uint64_t)exception2, 0x08, 0x8E);
    this->set_idtEntry(3, (uint64_t)exception3, 0x08, 0x8E);
    this->set_idtEntry(4, (uint64_t)exception4, 0x08, 0x8E);
    this->set_idtEntry(5, (uint64_t)exception5, 0x08, 0x8E);
    this->set_idtEntry(6, (uint64_t)exception6, 0x08, 0x8E);
    this->set_idtEntry(7, (uint64_t)exception7, 0x08, 0x8E);
    this->set_idtEntry(8, (uint64_t)exception8, 0x08, 0x8E);
    this->set_idtEntry(9, (uint64_t)exception9, 0x08, 0x8E);
    this->set_idtEntry(10, (uint64_t)exception10, 0x08, 0x8E);
    this->set_idtEntry(11, (uint64_t)exception11, 0x08, 0x8E);
    this->set_idtEntry(12, (uint64_t)exception12, 0x08, 0x8E);
    this->set_idtEntry(13, (uint64_t)exception13, 0x08, 0x8E);
    this->set_idtEntry(14, (uint64_t)exception14, 0x08, 0x8E);
    this->set_idtEntry(15, (uint64_t)exception15, 0x08, 0x8E);
    this->set_idtEntry(16, (uint64_t)exception16, 0x08, 0x8E);
    this->set_idtEntry(17, (uint64_t)exception17, 0x08, 0x8E);
    this->set_idtEntry(18, (uint64_t)exception18, 0x08, 0x8E);
    this->set_idtEntry(19, (uint64_t)exception19, 0x08, 0x8E);
    this->set_idtEntry(20, (uint64_t)exception20, 0x08, 0x8E);
    this->set_idtEntry(21, (uint64_t)exception21, 0x08, 0x8E);
    this->set_idtEntry(22, (uint64_t)exception22, 0x08, 0x8E);
    this->set_idtEntry(23, (uint64_t)exception23, 0x08, 0x8E);
    this->set_idtEntry(24, (uint64_t)exception24, 0x08, 0x8E);
    this->set_idtEntry(25, (uint64_t)exception25, 0x08, 0x8E);
    this->set_idtEntry(26, (uint64_t)exception26, 0x08, 0x8E);
    this->set_idtEntry(27, (uint64_t)exception27, 0x08, 0x8E);
    this->set_idtEntry(28, (uint64_t)exception28, 0x08, 0x8E);
    this->set_idtEntry(29, (uint64_t)exception29, 0x08, 0x8E);
    this->set_idtEntry(30, (uint64_t)exception30, 0x08, 0x8E);
    this->set_idtEntry(31, (uint64_t)exception31, 0x08, 0x8E);
    this->set_idtEntry(128, (uint64_t)exception128, 0x08, 0x8E);

    this->set_idtEntry(32, (uint64_t)irq0, 0x08, 0x8E);
    this->set_idtEntry(33, (uint64_t)irq1, 0x08, 0x8E);
    this->set_idtEntry(34, (uint64_t)irq2, 0x08, 0x8E);
    this->set_idtEntry(35, (uint64_t)irq3, 0x08, 0x8E);
    this->set_idtEntry(36, (uint64_t)irq4, 0x08, 0x8E);
    this->set_idtEntry(37, (uint64_t)irq5, 0x08, 0x8E);
    this->set_idtEntry(38, (uint64_t)irq6, 0x08, 0x8E);
    this->set_idtEntry(39, (uint64_t)irq7, 0x08, 0x8E);
    this->set_idtEntry(40, (uint64_t)irq8, 0x08, 0x8E);
    this->set_idtEntry(41, (uint64_t)irq9, 0x08, 0x8E);
    this->set_idtEntry(42, (uint64_t)irq10, 0x08, 0x8E);
    this->set_idtEntry(43, (uint64_t)irq11, 0x08, 0x8E);
    this->set_idtEntry(44, (uint64_t)irq12, 0x08, 0x8E);
    this->set_idtEntry(45, (uint64_t)irq13, 0x08, 0x8E);
    this->set_idtEntry(46, (uint64_t)irq14, 0x08, 0x8E);
    this->set_idtEntry(47, (uint64_t)irq15, 0x08, 0x8E);

    //insall idt
    asm volatile("lidt %0" : : "m"(idt_ptr));
    asm volatile("sti");

#ifdef DEBUG
    Logger.sucess("inited interupt system");
#endif
}

extern "C" void ISR_ExceptionHandler(void) {
    panic("exception");
}

extern intDriver IntDriver = intDriver();
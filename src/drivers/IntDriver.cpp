#include <drivers/IntDriver.hpp>
#include <def.h>
#include <panic.hpp>
#include <drivers/IoDriver.hpp>

#ifdef DEBUG
    #include <Logger.hpp>
#endif

typedef struct {
    uint16_t size;
    uint64_t offset;
} __attribute__((packed)) idtr_t;

typedef struct {
    uint16_t offset;
    uint16_t segment;
    uint8_t ist;
    uint8_t flags;
    uint16_t offset2;
    uint32_t offset3;
    uint32_t reserved;
} __attribute__((packed)) entry_t;

static entry_t idt[256];

static idtr_t idtr = {
    .size = sizeof(idt) - 1,
    .offset = (uint64_t)idt
};

uint64_t g_ints[256];

intDriver::intDriver() {}

void intDriver::set_idtEntry(int index, uint64_t adr) {
    g_ints[index] = adr;
}

void intDriver::register_Handler(int num, ISR handler) {
    this->set_idtEntry(num, (uint64_t)handler);
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

    //install entries
    this->set_idtEntry(0, (uint64_t)exception0);
    this->set_idtEntry(1, (uint64_t)exception1);
    this->set_idtEntry(2, (uint64_t)exception2);
    this->set_idtEntry(3, (uint64_t)exception3);
    this->set_idtEntry(4, (uint64_t)exception4);
    this->set_idtEntry(5, (uint64_t)exception5);
    this->set_idtEntry(6, (uint64_t)exception6);
    this->set_idtEntry(7, (uint64_t)exception7);
    this->set_idtEntry(8, (uint64_t)exception8);
    this->set_idtEntry(9, (uint64_t)exception9);
    this->set_idtEntry(10, (uint64_t)exception10);
    this->set_idtEntry(11, (uint64_t)exception11);
    this->set_idtEntry(12, (uint64_t)exception12);
    this->set_idtEntry(13, (uint64_t)exception13);
    this->set_idtEntry(14, (uint64_t)exception14);
    this->set_idtEntry(15, (uint64_t)exception15);
    this->set_idtEntry(16, (uint64_t)exception16);
    this->set_idtEntry(17, (uint64_t)exception17);
    this->set_idtEntry(18, (uint64_t)exception18);
    this->set_idtEntry(19, (uint64_t)exception19);
    this->set_idtEntry(20, (uint64_t)exception20);
    this->set_idtEntry(21, (uint64_t)exception21);
    this->set_idtEntry(22, (uint64_t)exception22);
    this->set_idtEntry(23, (uint64_t)exception23);
    this->set_idtEntry(24, (uint64_t)exception24);
    this->set_idtEntry(25, (uint64_t)exception25);
    this->set_idtEntry(26, (uint64_t)exception26);
    this->set_idtEntry(27, (uint64_t)exception27);
    this->set_idtEntry(28, (uint64_t)exception28);
    this->set_idtEntry(29, (uint64_t)exception29);
    this->set_idtEntry(30, (uint64_t)exception30);
    this->set_idtEntry(31, (uint64_t)exception31);
    this->set_idtEntry(128, (uint64_t)exception128);

    this->set_idtEntry(32, (uint64_t)irq0);
    this->set_idtEntry(33, (uint64_t)irq1);
    this->set_idtEntry(34, (uint64_t)irq2);
    this->set_idtEntry(35, (uint64_t)irq3);
    this->set_idtEntry(36, (uint64_t)irq4);
    this->set_idtEntry(37, (uint64_t)irq5);
    this->set_idtEntry(38, (uint64_t)irq6);
    this->set_idtEntry(39, (uint64_t)irq7);
    this->set_idtEntry(40, (uint64_t)irq8);
    this->set_idtEntry(41, (uint64_t)irq9);
    this->set_idtEntry(42, (uint64_t)irq10);
    this->set_idtEntry(43, (uint64_t)irq11);
    this->set_idtEntry(44, (uint64_t)irq12);
    this->set_idtEntry(45, (uint64_t)irq13);
    this->set_idtEntry(46, (uint64_t)irq14);
    this->set_idtEntry(47, (uint64_t)irq15);

    //install idt
	
    for (int i = 0; i < 256; i++) {   
        idt[i].offset = g_ints[i] & 0xffff;
        idt[i].segment = 0x8;
        idt[i].ist = 0;
        idt[i].flags = 0x8E;
        idt[i].offset2 = (g_ints[i] >> 16) & 0xffff;
        idt[i].offset3 = (g_ints[i] >> 32) & 0xffffffff;
    }
    
    asm volatile( "lidt (%%rax)" : : "a"(&idtr));

#ifdef DEBUG
    Logger.sucess("inited interupt system");
#endif
}

void end_interrupt(uint8_t num) {
#ifdef PIC
    if(num >= 0x28)
        IoDriver.outb(0x20, 0x20);
    IoDriver.outb(0xa0, 0x20);
#else
    panic("interrupt system just work with pic");
#endif
}

static void IrqHandler(REGISTERS regs) {
    //handle interupt

    ISR handler = (ISR)g_ints[regs.int_no];
    handler(&regs);

    //exit interupt
    end_interrupt(regs.int_no);
}


static char *exceptions[] = {
	"Division by 0",
	"Debug",
	"NMI",
	"Breakpoint",
	"Overflow",
	"Bound Range Exceeded",
	"Invalid Opcode",
	"Device Not Available",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Invalid TSS",
	"Segment Not Present",
	"Stack-Segment Fault",
	"General Protection Fault",
	"Page Fault",
	"Unknown",
	"x87 Floating-Point Exception",
	"Alignment Check",
	"Machine Check",
	"SIMD Exception"
};

static void ExceptionHandler(REGISTERS regs) {
    if (regs.int_no < 32) {
        panic(exceptions[regs.int_no]);
        hcf();
    }
    else {
        IrqHandler(regs);
    }
}

extern "C" void ISR_irqHandler(REGISTERS regs) {
    IrqHandler(regs);
}

extern "C" void ISR_ExceptionHandler(REGISTERS regs) {
    ExceptionHandler(regs);
}

extern intDriver IntDriver = intDriver();
#pragma once

#include <stdint.h>

typedef struct {
    uint32_t base_low;   
    uint16_t segment_selector; 
    uint8_t zero;              
    uint8_t type;              
    uint32_t base_high;        
} __attribute__((packed)) IDT;

typedef struct {
    uint16_t limit;      
    uint64_t base_address;
} __attribute__((packed)) IDT_PTR;

class intDriver {
private:
    void set_idtEntry(int index, uint64_t base, uint16_t seg_sel, uint8_t flags);

public:
    intDriver();

    void init();
};

extern intDriver IntDriver;

// excpetions

extern "C" void exception0();
extern "C" void exception1();
extern "C" void exception2();
extern "C" void exception3();
extern "C" void exception4();
extern "C" void exception5();
extern "C" void exception6();
extern "C" void exception7();
extern "C" void exception8();
extern "C" void exception9();
extern "C" void exception10();
extern "C" void exception11();
extern "C" void exception12();
extern "C" void exception13();
extern "C" void exception14();
extern "C" void exception15();
extern "C" void exception16();
extern "C" void exception17();
extern "C" void exception18();
extern "C" void exception19();
extern "C" void exception20();
extern "C" void exception21();
extern "C" void exception22();
extern "C" void exception23();
extern "C" void exception24();
extern "C" void exception25();
extern "C" void exception26();
extern "C" void exception27();
extern "C" void exception28();
extern "C" void exception29();
extern "C" void exception30();
extern "C" void exception31();
extern "C" void exception128();

// irqs
extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();
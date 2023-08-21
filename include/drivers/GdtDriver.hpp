#pragma once
#include <stdint.h>
#include <drivers/driver.hpp>

#define NO_GDT_DECRIPTORS 5

typedef struct GDT_ENTRY{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t gran;
    uint8_t base_high;
} __attribute__ ((packed));

typedef struct GDT_PTR {
    uint16_t limit;
    uint64_t base;
} __attribute__ ((packed));


class gdtDriver : Driver {
private:
    void set_gate(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
public:
    gdtDriver();

    void init();
};

extern gdtDriver GdtDriver;
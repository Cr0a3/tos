extern "C" {
    #include <stdint.h>
    #include <stddef.h>
    #include <limine.h>
}

#include <drivers/ioDriver.hpp>

extern "C" {
    void main(void) {
        IoDriver.outb(0xE9, 98);
    }
}
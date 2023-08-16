#include <drivers/ioDriver.hpp>

extern "C" {
    void init(void) {
        //init
        IoDriver.outb(0xE9, 97);
    }
}
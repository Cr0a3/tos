extern "C" {
    #include <stdint.h>
    #include <stddef.h>
    #include <limine.h>
}

#include <drivers/GraphicsDriver.hpp>

extern "C" {
    void main(void) {
        GraphicsDriver.putPixel(10, 10, 0xFFFFFFFF);
    }
}
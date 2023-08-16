extern "C" {
    #include <stdint.h>
    #include <stddef.h>
    #include <limine.h>
}

#include <drivers/GraphicsDriver.hpp>
#include <panic.hpp>

extern "C" {
    void main(void) {
        for (size_t i = 0; i < 100; i++) {
            GraphicsDriver.putPixel(i, i, 0xFFFFFFFF);
        }
        panic("exit");
    }
}
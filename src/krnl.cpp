extern "C" {
    #include <stdint.h>
    #include <stddef.h>
    #include <limine.h>
}

#include <drivers/GraphicsDriver.hpp>
#include <drivers/SerialDriver.hpp>
#include <panic.hpp>

extern "C" {
    void main(void) {
        for (size_t i = 0; i < 100; i++) {
            GraphicsDriver.putPixel(i, i, 0xFFFFFFFF);
        }

        // raise division by zero error
        asm volatile("\txorl %edx, %edx");
        asm volatile("\tmovl $0x7b, %eax");
        asm volatile("\tmovl $0, %ecx");
        asm volatile("\tidivl %ecx");
    }
}
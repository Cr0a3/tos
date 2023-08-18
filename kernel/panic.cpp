#include <panic.hpp>
#include <drivers/E9Driver.hpp>

void hcf() {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

void panic(const char* str) {
    E9Driver.send( *str );
    hcf();
}
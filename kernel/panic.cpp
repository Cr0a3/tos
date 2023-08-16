#include <panic.hpp>
#include <drivers/ioDriver.hpp>

void hcf() {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

void panic_print_char(char c) {
    uint8_t ch = c;

    IoDriver.outb(0xE9, ch);
}

void panic(const char* str) {
    size_t i = 0;

    while (str[i] != '\0') {
        panic_print_char(str[i]);
        i++;
    }
    hcf();
}
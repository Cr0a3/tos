#include <panic.hpp>
#include <Logger.hpp>

void hcf() {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

void panic(char* str) {
    Logger.error(str);
    hcf();
}
#include <stdint.h>
#include <stddef.h>
#include <limine.h>

// Halt and catch fire function.
static void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}

extern void init(void);
extern void main(void);

void _entry(void) {
    init();
    main();

    hcf();
}
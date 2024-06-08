#include <stdint.h>
#include <stddef.h>
#include <limine.h>

extern void init(void);
extern void main(void);
extern void hcf();

void _entry(void) {
    init();
    main();

    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}
#include <stdint.h>
#include <stddef.h>
#include <limine.h>

extern void init(void);
extern void main(void);

void _entry(void) {
    init();
    main();
}
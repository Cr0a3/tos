#include <drivers/GraphicsDriver.hpp>

extern "C" {
    void init(void) {
        GraphicsDriver.init();
    }
}
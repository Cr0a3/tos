#include <drivers/GraphicsDriver.hpp>
#include <drivers/SerialDriver.hpp>

extern "C" {
    void init(void) {
        GraphicsDriver.init();
        SerialDriver.init();
    }
}
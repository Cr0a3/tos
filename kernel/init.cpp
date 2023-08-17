#include <drivers/GraphicsDriver.hpp>
#include <drivers/SerialDriver.hpp>
#include <drivers/AcpiDriver.hpp>

extern "C" {
    void init(void) {
        GraphicsDriver.init();
        SerialDriver.init();
        SerialDriver.send("Init acpi");
        AcpiDriver.init();
        SerialDriver.send("Init completed");
    }
}
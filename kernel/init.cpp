#include <drivers/GraphicsDriver.hpp>
#include <drivers/SerialDriver.hpp>
#include <drivers/AcpiDriver.hpp>
#include <drivers/GdtDriver.hpp>
#include <drivers/IntDriver.hpp>
#include <Logger.hpp>

extern "C" {
    void init(void) {
        GdtDriver.init();
        IntDriver.init();

        GraphicsDriver.init();
        SerialDriver.init();
        AcpiDriver.init();
        
#ifdef DEBUG
        Logger.sucess("inited everything");
#endif
    }
}
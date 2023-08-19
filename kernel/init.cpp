#include <drivers/GraphicsDriver.hpp>
#include <drivers/SerialDriver.hpp>
#include <drivers/AcpiDriver.hpp>
#include <drivers/E9Driver.hpp>
#include <Logger.hpp>

extern "C" {
    void init(void) {
        GraphicsDriver.init();
        SerialDriver.init();
        AcpiDriver.init();
        
#ifdef DEBUG
        Logger.sucess("inited everything");
#endif
    }
}
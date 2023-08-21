#include <drivers/IntDriver.hpp>
#include <def.h>

#ifdef DEBUG
    #include <Logger.hpp>
#endif

intDriver::intDriver() {}

void intDriver::init() {
#ifdef DEBUG
    Logger.sucess("inited intterupt system");
#endif
}

extern intDriver IntDriver = intDriver();
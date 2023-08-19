#pragma once

#define COM1 0x3F8
#define COM2 0x2F8

#include <drivers/driver.hpp>

class serialDriver : Driver {
    private:
    public:
        serialDriver();
        void init();

        char recive();
        void send(char data);
        void send(const char* data);

        bool transmitEmpy();
        bool recived();
};

extern serialDriver SerialDriver;
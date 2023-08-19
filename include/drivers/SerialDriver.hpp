#pragma once

#define COM1 0x3F8
#define COM2 0x2F8

#include <stdint.h>
#include <stddef.h>
#include <drivers/driver.hpp>

class serialDriver : Driver {
    private:
    public:
        serialDriver();
        void init();

        char recive(uint8_t port);
        void send(uint8_t port, char data);
        void send(uint8_t port, char* data);
        void send(uint8_t port, char* data, size_t num);

        bool transmitEmpy(uint8_t port);
        bool recived(uint8_t port);
};

extern serialDriver SerialDriver;
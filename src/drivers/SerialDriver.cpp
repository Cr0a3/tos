#include <drivers/SerialDriver.hpp>
#include <drivers/IoDriver.hpp>
#include <Logger.hpp>
#include <panic.hpp>

serialDriver::serialDriver() { }

void serialDriver::init() {
    // init com1
    IoDriver.outb(COM1 + 1, 0x00);    // Disable all interrupts
    IoDriver.outb(COM1 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    IoDriver.outb(COM1 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    IoDriver.outb(COM1 + 1, 0x00);    //                  (hi byte)
    IoDriver.outb(COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
    IoDriver.outb(COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    IoDriver.outb(COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    IoDriver.outb(COM1 + 4, 0x1E);    // Set in loopback mode, test the serial chip
    IoDriver.outb(COM1 + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if(IoDriver.inb(COM1 + 0) != 0xAE) {
#ifndef PANIC_SERRIALPORT_FAULTY
        Logger.error("faulty serial port com1");
#else
        panic("faulty serial port com1");
#endif
    }

    IoDriver.outb(COM1 + 4, 0x0F);
    
    // init com2
    IoDriver.outb(COM2 + 1, 0x00);    // Disable all interrupts
    IoDriver.outb(COM2 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    IoDriver.outb(COM2 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    IoDriver.outb(COM2 + 1, 0x00);    //                  (hi byte)
    IoDriver.outb(COM2 + 3, 0x03);    // 8 bits, no parity, one stop bit
    IoDriver.outb(COM2 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    IoDriver.outb(COM2 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    IoDriver.outb(COM2 + 4, 0x1E);    // Set in loopback mode, test the serial chip
    IoDriver.outb(COM2 + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if(IoDriver.inb(COM2 + 0) != 0xAE) {
#ifndef PANIC_SERRIALPORT_FAULTY
        Logger.error("faulty serial port com2");
#else 
        panic("faulty serial port com2");
#endif
    }

    IoDriver.outb(COM2 + 4, 0x0F);
#ifdef DEBUG
    Logger.sucess("inited serial driver");
#endif
}

char serialDriver::recive(uint8_t port) {
    return IoDriver.inb(port);
}

void serialDriver::send(uint8_t port, char data) {
    IoDriver.outb(port, data);
}

void serialDriver::send(uint8_t port, char* data) {
    size_t i = 0;
    while (data[i] != '\0') {
        this->send(port, data[i]);
        i++;
    }
}

void serialDriver::send(uint8_t port, char* data, size_t num) {
    for ( size_t i = 0; i < num; i++ ) {
        this->send(port, data[i]);
    }
}

bool transmitEmpy(uint8_t port) {
   return IoDriver.inb(port + 5) & 0x20;
}

bool recived(uint8_t port) {
   return IoDriver.inb(port + 5) & 1;
}

extern serialDriver SerialDriver = serialDriver();
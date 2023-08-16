#pragma once
#include <drivers/SerialDriver.hpp>
#include <drivers/ioDriver.hpp>
#include <panic.hpp>

serialDriver::serialDriver() { }

void serialDriver::init() {
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
        panic("faulty serial");
    }

    IoDriver.outb(COM1 + 4, 0x0F);
}

char serialDriver::recive() {
    return IoDriver.inb(COM1);
}

void serialDriver::send(char data) {
    IoDriver.outb(COM1, data);
}

bool transmitEmpy() {
   return IoDriver.inb(COM1 + 5) & 0x20;
}

bool recived() {
   return IoDriver.inb(COM1 + 5) & 1;
}

extern serialDriver SerialDriver = serialDriver();
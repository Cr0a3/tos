#pragma once
extern "C" {
    #include <limine.h>
}

class graphicsDriver {
private:
    limine_framebuffer framebuf;
public:
    graphicsDriver();

    void putPixel(int x, int y, long color);
    void init();

    uint64_t getPitch();
    uint64_t getHeight();
    uint64_t getWidth();
    uint16_t getBpp();
    uint8_t getMemory_model();
    uint8_t getRed_mask_size();
    uint8_t getRed_mask_shift();
    uint8_t getGreen_mask_size();
    uint8_t getGreen_mask_shift();
    uint8_t getBlue_mask_size();
    uint8_t getBlue_mask_shift();
};

extern graphicsDriver GraphicsDriver;
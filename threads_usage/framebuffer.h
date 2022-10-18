#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>


struct Framebuffer
{
    char* instance;
    int descriptor;
    struct fb_var_screeninfo var_info;
    struct fb_fix_screeninfo fix_info;
    long int screen_size;
};

struct Color
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct Rectangle
{
    struct Color color;
    uint16_t x1;
    uint16_t y1;
    uint16_t x2;
    uint16_t y2;
};

struct Framebuffer* initialize_framebuffer();

void draw_rectangle(struct Framebuffer* framebuffer, struct Rectangle rectangle);


#endif // FRAMEBUFFER_H

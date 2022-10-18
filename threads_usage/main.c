#include "framebuffer.h"
#include "keyboard.h"

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>


int main(int argc, char** argv) 
{
    struct Framebuffer* framebuffer = initialize_framebuffer();
    struct Keyboard* keyboard = initialize_keyboard();

    struct Rectangle rectangle;
    rectangle.x1 = 10;
    rectangle.y1 = 10;
    rectangle.x2 = 100;
    rectangle.y2 = 100;
    rectangle.color.red = 0;
    rectangle.color.green = 255;
    rectangle.color.blue = 0;

    uint16_t step = 10;
    
    struct input_event event;

    while (true)
    {
        poll(&keyboard->poll_file_descriptor, 1, -1);

        if (keyboard->poll_file_descriptor.revents & POLLIN)
        {
            read(keyboard->descriptor, &event, sizeof event);

            switch (event.code)
            {
            case KEY_LEFT:
                if (rectangle.x1 - step >= 0)
                {
                    rectangle.x1 -= step;
                    rectangle.x2 -= step;
                }
                break;
            case KEY_RIGHT:
                if (rectangle.x2 + step <= framebuffer->var_info.xres)
                {
                    rectangle.x1 += step;
                    rectangle.x2 += step;
                }
                break;
            case KEY_UP:
                if (rectangle.color.green + step <= 255 && rectangle.color.blue - step >= 0)
                {
                    rectangle.color.green += step;
                    rectangle.color.blue -= step;
                }
                break;
            case KEY_DOWN:
                if (rectangle.color.blue + step <= 255 && rectangle.color.green - step >= 0)
                {
                    rectangle.color.blue += step;
                    rectangle.color.green -= step;
                }
                break;  
            }
            
            draw_rectangle(framebuffer, rectangle);
        }
    }    

    munmap(framebuffer->instance, framebuffer->screen_size);
    close(framebuffer->descriptor);
    free(framebuffer);
    free(keyboard);

    return 0;
}
#include "framebuffer.h"


struct Framebuffer* initialize_framebuffer()
{
    struct Framebuffer* framebuffer = malloc(sizeof(struct Framebuffer));
    framebuffer->descriptor = open("/dev/fb0", O_RDWR);

    if (-1 == framebuffer->descriptor) 
    {
        perror("Error: can't open framebuffer device.\n");
        return 0;
    }

    if (ioctl(framebuffer->descriptor, FBIOGET_FSCREENINFO, &framebuffer->fix_info) == -1) 
    {
        perror("Error: can't read fixed information.\n");
        return 0;
    }

    if (ioctl(framebuffer->descriptor, FBIOGET_VSCREENINFO, &framebuffer->var_info) == -1) 
    {
        perror("Error: can't read variable information.\n");
        return 0;
    }

    framebuffer->screen_size = framebuffer->var_info.xres_virtual * framebuffer->var_info.yres_virtual *
                               framebuffer->var_info.bits_per_pixel / 8;

    framebuffer->instance = (char*)mmap(0, framebuffer->screen_size, PROT_READ | PROT_WRITE, MAP_SHARED,
                                        framebuffer->descriptor, 0);

    if (-1 == (int)*framebuffer->instance) 
    {
        perror("Error: failed to map framebuffer device to memory.\n");
        return 0;
    }

    return framebuffer;
}

void modify_rectangle(struct Framebuffer* framebuffer, struct Rectangle* rectangle, struct input_event* event)
{
    uint16_t step = 10;

    printf("modify_rectangle with event_code = %d\n", event->code);

    switch (event->code)
    {
        case KEY_UP:
            if (rectangle->color.green + step <= 255 && rectangle->color.blue - step >= 0)
            {
                rectangle->color.green += step;
                rectangle->color.blue -= step;
                printf("Working 1 on color change for rectangle with x1 = %d, GREEN = %d, BLUE = %d\n", rectangle->x1, 
                                                                                                      rectangle->color.green,
                                                                                                      rectangle->color.blue);
            }
            break;
        case KEY_DOWN:
            if (rectangle->color.blue + step <= 255 && rectangle->color.green - step >= 0)
            {
                rectangle->color.blue += step;
                rectangle->color.green -= step;
                printf("Working 2 on color change for rectangle with x1 = %d, GREEN = %d, BLUE = %d\n", rectangle->x1, 
                                                                                                      rectangle->color.green,
                                                                                                      rectangle->color.blue);
            }
            break;
    }

    // memset(framebuffer->instance, 0, framebuffer->screen_size);
}

void modify_rectangle_on_timer_expires(union sigval timer_data)
{
    struct DrawRectangleArgs* data = timer_data.sival_ptr;

    printf("Timer 1 fires! With rec.x1 = %d\n", data->rectangle->x1);

    uint16_t step = 10;

    if (data->rectangle->x2 + step <= data->framebuffer->var_info.xres)
    {
        data->rectangle->x1 += step;
        data->rectangle->x2 += step;
    }
    else
    {   
        data->rectangle->x1 = 0;
        data->rectangle->x2 = 50;
    }

    memset(data->framebuffer->instance, 0, data->framebuffer->screen_size);
}

void draw_rectangle(struct Framebuffer* framebuffer, struct Rectangle* rectangle)
{
    printf("\nDRAW RECT. X1 = %d, R = %d, G = %d, B = %d\n", rectangle->x1, rectangle->color.red, 
                                                                        rectangle->color.green, rectangle->color.blue);

    for (int x = rectangle->x1; x < rectangle->x2; ++x)
    {
        for (int y = rectangle->y1; y < rectangle->y2; ++y) 
        {   
            long int pixel_location = (x + framebuffer->var_info.xoffset) * (framebuffer->var_info.bits_per_pixel / 8) +
                                      (y + framebuffer->var_info.yoffset) * framebuffer->fix_info.line_length;
                       
            *(framebuffer->instance + pixel_location) = rectangle->color.blue;      // blue
            *(framebuffer->instance + pixel_location + 1) = rectangle->color.green; // green
            *(framebuffer->instance + pixel_location + 2) = rectangle->color.red;   // red
            *(framebuffer->instance + pixel_location + 3) = 0;                      // transparency
        }
    }
}

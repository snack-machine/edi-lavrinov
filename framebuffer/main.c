#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <sys/poll.h>
#include <sys/mman.h>
#include <sys/ioctl.h>


struct Framebuffer
{
    int s32_fb_descriptor;
    struct fb_var_screeninfo obj_fb_var_info;
    struct fb_fix_screeninfo obj_fb_fix_info;
    long int s32L_screen_size;
    char* cP_frame_buffer;
};

struct Color
{
    uint8_t u8_red;
    uint8_t u8_green;
    uint8_t u8_blue;
};


struct Framebuffer* initialize_frame_buffer()
{
    struct Framebuffer* objP_fb = malloc(sizeof(struct Framebuffer));
    objP_fb->s32_fb_descriptor = open("/dev/fb0", O_RDWR);

    if (-1 == objP_fb->s32_fb_descriptor) 
    {
        perror("Error: can't open framebuffer device.\n");
        return NULL;
    }

    if (-1 == ioctl(objP_fb->s32_fb_descriptor, FBIOGET_FSCREENINFO, &objP_fb->obj_fb_fix_info)) 
    {
        perror("Error: can't read fixed information.\n");
        return NULL;
    }

    if (-1 == ioctl(objP_fb->s32_fb_descriptor, FBIOGET_VSCREENINFO, &objP_fb->obj_fb_var_info)) 
    {
        perror("Error: can't read variable information.\n");
        return NULL;
    }

    objP_fb->s32L_screen_size = objP_fb->obj_fb_var_info.xres_virtual * objP_fb->obj_fb_var_info.yres_virtual *
                                objP_fb->obj_fb_var_info.bits_per_pixel / 8;
    objP_fb->cP_frame_buffer = (char*)mmap(0, objP_fb->s32L_screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, 
                                           objP_fb->s32_fb_descriptor, 0);

    if (-1 == (int)*objP_fb->cP_frame_buffer) 
    {
        perror("Error: failed to map framebuffer device to memory.\n");
        return NULL;
    }

    return objP_fb;
}


void draw_rectangle(struct Framebuffer* objP_fb, uint16_t u16L_begin_x, uint16_t u16L_end_x, struct Color objL_color)
{
    memset(objP_fb->cP_frame_buffer, 0, objP_fb->s32L_screen_size);

    uint16_t u16L_side_length = 100;

    for (int y = u16L_begin_x; y < u16L_end_x; ++y)
    {
        for (int x = u16L_begin_x + u16L_side_length; x < u16L_end_x + u16L_side_length; ++x) 
        {   
            long int s32L_location = (x + objP_fb->obj_fb_var_info.xoffset) * 
                                     (objP_fb->obj_fb_var_info.bits_per_pixel / 8) + 
                                     (y + objP_fb->obj_fb_var_info.yoffset) * 
                                     objP_fb->obj_fb_fix_info.line_length;
                       
            *(objP_fb->cP_frame_buffer + s32L_location) = objL_color.u8_blue;      // blue
            *(objP_fb->cP_frame_buffer + s32L_location + 1) = objL_color.u8_green; // green
            *(objP_fb->cP_frame_buffer + s32L_location + 2) = objL_color.u8_red;   // red
            *(objP_fb->cP_frame_buffer + s32L_location + 3) = 0;                   // transparency
        }
    }
}


int main(int argc, char** argv) 
{
    struct Framebuffer* objP_fb = initialize_frame_buffer();

    char* cP_keyboard_device = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    int s32L_keyboard_device_descriptor;
    s32L_keyboard_device_descriptor = open(cP_keyboard_device, O_RDONLY);

    if (0 == s32L_keyboard_device_descriptor)
    {
        printf("Error: keyboard device is invalid.\n");
        return 0;
    }


    struct pollfd objL_poll_file_descriptor;
    objL_poll_file_descriptor.fd = s32L_keyboard_device_descriptor;
    objL_poll_file_descriptor.events = POLLIN;

    struct input_event objL_event;

    uint16_t u16L_begin_x = 100;
    uint16_t u16L_end_x = 200;
    uint16_t u16L_step = 10;

    struct Color objL_color;
    objL_color.u8_red = 0;
    objL_color.u8_green = 255;
    objL_color.u8_blue = 0;


    while (true)
    {
        poll(&objL_poll_file_descriptor, 1, -1);

        if (objL_poll_file_descriptor.revents & POLLIN)
        {
            read(s32L_keyboard_device_descriptor, &objL_event, sizeof objL_event);

            switch (objL_event.code)
            {
            case KEY_LEFT:
                if (u16L_begin_x - u16L_step >= 0)
                {
                    u16L_begin_x -= u16L_step;
                    u16L_end_x -= u16L_step;
                }
                break;

            case KEY_RIGHT:
                if (u16L_begin_x + u16L_step <= objP_fb->obj_fb_var_info.xres)
                {
                    u16L_begin_x += u16L_step;    
                    u16L_end_x += u16L_step;
                }
                break;

            case KEY_UP:
                if (objL_color.u8_green + u16L_step <= 255 && objL_color.u8_blue - u16L_step >= 0)
                {
                    objL_color.u8_green += u16L_step;
                    objL_color.u8_blue -= u16L_step;
                }
                break;

            case KEY_DOWN:
                if (objL_color.u8_blue + u16L_step <= 255 && objL_color.u8_green - u16L_step >= 0)
                {
                    objL_color.u8_blue += u16L_step;
                    objL_color.u8_green -= u16L_step;
                }
                break;  
            }

            draw_rectangle(objP_fb, u16L_begin_x, u16L_end_x, objL_color);
        }
    }    

    munmap(objP_fb->cP_frame_buffer, objP_fb->s32L_screen_size);
    close(objP_fb->s32_fb_descriptor);
    free(objP_fb);

    return 0;
}

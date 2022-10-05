#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <sys/mman.h>
#include <sys/ioctl.h>


char* cP_frame_buffer;
int s32_frame_buffer_descriptor;
struct fb_var_screeninfo obj_fb_var_info;
struct fb_fix_screeninfo obj_fb_fix_info;
long int s32_screen_size;

uint8_t u8P_key_map[KEY_MAX / 8 + 1];

uint8_t u8_color_red = 0;
uint8_t u8_color_green = 255;
uint8_t u8_color_blue = 0;


bool key_is_pressed(uint8_t u8L_key)
{
    int s32L_key_byte = u8P_key_map[u8L_key / 8];
    int s32L_mask = 1 << (u8L_key % 8);

    return (s32L_key_byte & s32L_mask) != 0;
}


void initialize_frame_buffer()
{
    s32_frame_buffer_descriptor = open("/dev/fb0", O_RDWR);

    if (-1 == s32_frame_buffer_descriptor) 
    {
        perror("Error: can't open framebuffer device.\n");
        return;
    }

    if (-1 == ioctl(s32_frame_buffer_descriptor, FBIOGET_FSCREENINFO, &obj_fb_fix_info)) 
    {
        perror("Error: can't read fixed information.\n");
        return;
    }

    if (-1 == ioctl(s32_frame_buffer_descriptor, FBIOGET_VSCREENINFO, &obj_fb_var_info)) 
    {
        perror("Error: can't read variable information.\n");
        return;
    }

    s32_screen_size = obj_fb_var_info.xres_virtual * obj_fb_var_info.yres_virtual * obj_fb_var_info.bits_per_pixel / 8;
    cP_frame_buffer = (char*)mmap(0, s32_screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, s32_frame_buffer_descriptor, 0);

    if (-1 == (int)*cP_frame_buffer) 
    {
        perror("Error: failed to map framebuffer device to memory.\n");
        return;
    }
}


void draw_rectangle(uint16_t u16L_begin_x, uint16_t u16L_end_x, uint16_t u16L_side_length)
{
    memset(cP_frame_buffer, 0, s32_screen_size);

    for (int y = u16L_begin_x; y < u16L_end_x; ++y)
    {
        for (int x = u16L_begin_x + u16L_side_length; x < u16L_end_x + u16L_side_length; ++x) 
        {   
            long int s32L_location = (x + obj_fb_var_info.xoffset) * (obj_fb_var_info.bits_per_pixel / 8) + 
                       (y + obj_fb_var_info.yoffset) * obj_fb_fix_info.line_length;
                       
            *(cP_frame_buffer + s32L_location) = u8_color_blue;      // blue
            *(cP_frame_buffer + s32L_location + 1) = u8_color_green; // green
            *(cP_frame_buffer + s32L_location + 2) = u8_color_red;   // red
            *(cP_frame_buffer + s32L_location + 3) = 0;              // transparency
        }
    }
}


int main(int argc, char** argv) 
{
    initialize_frame_buffer();
 
    char* cP_keyboard_device = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    int s32L_keyboard_device_descriptor;
    s32L_keyboard_device_descriptor = open(cP_keyboard_device, O_RDONLY);

    if (0 == s32L_keyboard_device_descriptor)
    {
        printf("Error: keyboard device is invalid.\n");
        return 0;
    }


    uint16_t u16L_begin_x = 100;
    uint16_t u16L_end_x = 200;
    uint16_t u16L_side_length = 100;
    uint16_t u16L_step = 10;

    while (true)
    {
        memset(u8P_key_map, 0, sizeof(u8P_key_map));
        
        usleep(20000);
        ioctl(s32L_keyboard_device_descriptor, EVIOCGKEY(sizeof(u8P_key_map)), u8P_key_map);

        if (key_is_pressed(KEY_LEFT))
        {
            if (u16L_begin_x - u16L_step >= 0)
            {
                u16L_begin_x -= u16L_step;
                u16L_end_x -= u16L_step;
            }
        }
        else if (key_is_pressed(KEY_RIGHT))
        {
            if (u16L_begin_x + u16L_step <= obj_fb_var_info.xres)
            {
                u16L_begin_x += u16L_step;    
                u16L_end_x += u16L_step;
            }
        }
        else if (key_is_pressed(KEY_UP))
        {
            if (u8_color_green + u16L_step <= 255 && u8_color_blue - u16L_step >= 0)
            {
                u8_color_green += u16L_step;
                u8_color_blue -= u16L_step;
            }
        }
        else if (key_is_pressed(KEY_DOWN))
        {
            if (u8_color_blue + u16L_step <= 255 && u8_color_green - u16L_step >= 0)
            {
                u8_color_blue += u16L_step;
                u8_color_green -= u16L_step;
            }
        }

        draw_rectangle(u16L_begin_x, u16L_end_x, u16L_side_length);
    }    


    munmap(cP_frame_buffer, s32_screen_size);
    close(s32_frame_buffer_descriptor);

    return 0;
}

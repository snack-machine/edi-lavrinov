#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <linux/input.h>


struct Keyboard
{
    char* device;
    int descriptor;
    struct pollfd poll_file_descriptor;
};

struct Keyboard* initialize_keyboard();

#endif // KEYBOARD_H

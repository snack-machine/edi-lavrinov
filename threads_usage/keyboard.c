#include "keyboard.h"


struct Keyboard* initialize_keyboard()
{
    struct Keyboard* keyboard = malloc(sizeof(struct Keyboard));
    keyboard->device = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    keyboard->descriptor = open(keyboard->device, O_RDONLY);

    if (keyboard->descriptor == 0)
    {
        perror("Error: keyboard device is invalid.\n");
        return 0;
    }

    keyboard->poll_file_descriptor.fd = keyboard->descriptor;
    keyboard->poll_file_descriptor.events = POLLIN;

    return keyboard;
}

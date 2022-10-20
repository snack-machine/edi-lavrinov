#include "framebuffer.h"
#include "keyboard.h"

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void* draw_rectangle_wrapper(void* args)
{
    struct DrawRectangleArgs* casted_args = (struct DrawRectangleArgs*)args;

    timer_t timer = 0;
    struct sigevent signal_event = {0};
    struct itimerspec timer_specs = { .it_value.tv_sec  = 1, .it_value.tv_nsec = 0, 
                                      .it_interval.tv_sec = 1, .it_interval.tv_nsec = 0 };

    signal_event.sigev_notify = SIGEV_THREAD;
    signal_event.sigev_notify_function = &modify_rectangle_on_timer_expires;
    signal_event.sigev_value.sival_ptr = casted_args;

    if (timer_create(CLOCK_REALTIME, &signal_event, &timer) != 0)
    {
        perror("Error: can't create timer.\n");
        return 0;
    }

    timer_settime(timer, 0, &timer_specs, NULL);

    while (true)
    {
        // memset(casted_args->framebuffer->instance, 0, casted_args->framebuffer->screen_size);
        // modify_rectangle(casted_args->framebuffer, casted_args->rectangle, casted_args->event);

        pthread_mutex_lock(&mutex);
        // printf("wrapper casted_args->event = %d\n", casted_args->event->code);
        // sleep(1);

        draw_rectangle(casted_args->framebuffer, casted_args->rectangle);
        pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char** argv)
{
    pthread_mutex_init(&mutex, NULL);

    struct Framebuffer* framebuffer = initialize_framebuffer();
    struct Keyboard* keyboard = initialize_keyboard();
    struct input_event* event = malloc(sizeof(struct input_event));
    struct Rectangle* rectangles[2];

    // Initialize first rectangle
    rectangles[0] = malloc(sizeof(struct Rectangle));
    rectangles[0]->x1 = 0;
    rectangles[0]->y1 = 0;
    rectangles[0]->x2 = 50;
    rectangles[0]->y2 = 50;
    rectangles[0]->color.red = 0;
    rectangles[0]->color.green = 255;
    rectangles[0]->color.blue = 0;

    struct DrawRectangleArgs* args1 = malloc(sizeof(struct DrawRectangleArgs));
    args1->framebuffer = framebuffer;
    args1->rectangle = rectangles[0];
    args1->event = event;
    
    if (pthread_create(&rectangles[0]->thread, NULL, draw_rectangle_wrapper, args1) != 0)
    {
        perror("Failed to create thread.");
    }


    // Initialize second rectangle
    rectangles[1] = malloc(sizeof(struct Rectangle));
    rectangles[1]->x1 = 50;
    rectangles[1]->y1 = 50;
    rectangles[1]->x2 = 100;
    rectangles[1]->y2 = 100;
    rectangles[1]->color.red = 150;
    rectangles[1]->color.green = 255;
    rectangles[1]->color.blue = 0;

    struct DrawRectangleArgs* args2 = malloc(sizeof(struct DrawRectangleArgs));
    args2->framebuffer = framebuffer;
    args2->rectangle = rectangles[1];
    args2->event = event;

    if (pthread_create(&rectangles[1]->thread, NULL, draw_rectangle_wrapper, args2) != 0)
    {
        perror("Failed to create thread.");
    }

    while (true)
    {
        poll(&keyboard->poll_file_descriptor, 1, -1);

        if (keyboard->poll_file_descriptor.revents & POLLIN)
        {
            read(keyboard->descriptor, event, sizeof(struct input_event));

            // pthread_mutex_lock(&mutex);
            
            // printf("read a keyboard event [code] = %d \n", event->code);   
            // pthread_join(rectangles[0]->thread, NULL);
            // memset(framebuffer->instance, 0, framebuffer->screen_size);


            modify_rectangle(framebuffer, rectangles[0], event);
            modify_rectangle(framebuffer, rectangles[1], event);

            // pthread_mutex_unlock(&mutex);
        }
    }

    // pthread_join(rectangles[0]->thread, NULL);

    munmap(framebuffer->instance, framebuffer->screen_size);
    close(framebuffer->descriptor);

    pthread_mutex_destroy(&mutex);

    free(framebuffer);
    free(event);
    free(keyboard);

    free(rectangles[0]);
    free(rectangles[1]);
    
    return 0;
}
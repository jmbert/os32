#include <terminal.h>

#include <stdlib.h>

terminal_t create_terminal(unsigned int xPosition, unsigned int yPosition, unsigned int buffer_length)
{

    void *stdoutBuffer = malloc(sizeof(unsigned char)*buffer_length);
    fd_t stdout = new_virtual_file(stdoutBuffer, sizeof(unsigned char)*buffer_length);

    void *stdinBuffer = malloc(sizeof(unsigned char)*buffer_length);
    fd_t stdin = new_virtual_file(stdinBuffer, sizeof(unsigned char)*buffer_length);

    
    void *stderrBuffer = malloc(sizeof(unsigned char)*buffer_length);
    fd_t stderr = new_virtual_file(stderrBuffer, sizeof(unsigned char)*buffer_length);

    return (terminal_t)
    {
        .xPosition = xPosition,
        .yPosition = yPosition,
        .swap = (graphics_swap_buffer_t)
                {
                    .size = GRAPHICS_SIZE,
                    .buffer = (unsigned char *)malloc(sizeof(unsigned char)*GRAPHICS_SIZE),
                    .offset = GRAPHICS_GET_PIXEL_OFFSET(xPosition, yPosition),
                },
        .stdin = stdin,
        .stdout = stdout,
        .stderr = stderr,
    };
}
#include <io.h>
#include <vga.h>
#include<stdint.h>

#define MAX_BUFFER_SIZE 256

char shell_buffer[MAX_BUFFER_SIZE];
int buffer_idx = 0;

extern void interpret_command(char* input);

unsigned char kbd_us[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,         
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

void keyboard_handler() {
    uint8_t scancode = inb(0x60);

    if (!(scancode & 0x80)) {
        char c = kbd_us[scancode];

        if (c == '\n') {
            kprint("\n");
            shell_buffer[buffer_idx] = '\0';
            
            if (buffer_idx > 0) {
                interpret_command(shell_buffer); 
            }
            
            buffer_idx = 0;
            kprint("BareOS> ");
        } 
        else if (c == '\b') {
            if (buffer_idx > 0) {
                buffer_idx--;
                kprint_backspace();
            }
        } 
        else if (c != 0 && buffer_idx < MAX_BUFFER_SIZE - 1) {
            shell_buffer[buffer_idx++] = c;
            char str[2] = {c, '\0'};
            kprint(str);
        }
    }
}
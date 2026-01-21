#include <keyboard.h>
#include <isr.h>
#include <io.h>
#include <vga.h>
#include <shell.h>
#include <util.h>

static char key_buffer[256];

const char ascii_nomod[] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = inb(0x60);

    if (scancode & 0x80) {
        return;
    }

    if (scancode == 0x1C) { // ENTER 
        kprint("\n");
        interpret_command(key_buffer); 
        key_buffer[0] = '\0';          
    } 
    else if (scancode == 0x0E) { // BACKSPACE 
        int len = strlen(key_buffer);
        if (len > 0) {
            key_buffer[len - 1] = '\0';
            kprint_backspace(); 
        }
    } 
    else {
        char letter = ascii_nomod[scancode];
        if (letter != 0) {
            char str[2] = {letter, '\0'};
            kprint(str);
            int len = strlen(key_buffer);
            if (len < 255) {
                key_buffer[len] = letter;
                key_buffer[len + 1] = '\0';
            }
        }
    }
}

void init_keyboard() {
    register_interrupt_handler(33, keyboard_callback); 
    key_buffer[0] = '\0';
}
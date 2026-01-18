#include <io.h>
#include <vga.h>

extern int cursor_x;
extern int cursor_y;

char command_buffer[128];
int buffer_idx = 0;

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void execute_command() {
    command_buffer[buffer_idx] = '\0';
    kprint("\n"); 

    if (strcmp(command_buffer, "help") == 0) {
        kprint("Commands: help, clear, version\n");
    } 
    else if (strcmp(command_buffer, "clear") == 0) {
        clear_screen(); 
    }
    else if (strcmp(command_buffer, "version") == 0) {
        kprint("BareOS Edition v0.1\n");
        kprint("Compilation Date: 18 January 2026\n");
        kprint("Arda Gurbuz\n");
    }
    else {
        kprint("command not found\n");
    }

    buffer_idx = 0;
    kprint("BareOS> ");
}

unsigned char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

void keyboard_handler() {
    unsigned char scancode = inb(0x60);
    char *vidptr = (char*)0xb8000;

    if (scancode & 0x80) return; 

    char c = keyboard_map[scancode];

    if (c > 0) {
        if (c == '\n') {
            execute_command();
        } 
        else if (c == '\b') {
            if (buffer_idx > 0) {
                buffer_idx--;
                cursor_x--;
                int offset = (cursor_y * 80 + cursor_x) * 2;
                vidptr[offset] = ' ';
            }
        } 
        else {
            if (buffer_idx < 127) {
                command_buffer[buffer_idx++] = c;
                int offset = (cursor_y * 80 + cursor_x) * 2;
                vidptr[offset] = c;
                vidptr[offset + 1] = 0x0A; 
                cursor_x++;
            }
        }
        
        if (cursor_x >= 80) { cursor_x = 0; cursor_y++; }

        if (cursor_y >= 25) {
            scroll();
            cursor_y = 24;
        }
        update_cursor(cursor_x, cursor_y);
    }
}
#include "io.h"

int cursor_x = 0;
int cursor_y = 0;

void update_cursor(int x, int y) {
    unsigned short pos = y * 80 + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));
    
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

void enable_cursor(unsigned char cursor_start, unsigned char cursor_end) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
}

void clear_screen() {
    char *vidptr = (char*)0xb8000;
    unsigned int i = 0;

    while (i < 80 * 25 * 2) {
        vidptr[i] = ' ';       
        vidptr[i + 1] = 0x07;  
        i = i + 2;
    }

    cursor_x = 0;
    cursor_y = 0;

    update_cursor(cursor_x, cursor_y);
}

void scroll() {
    char *vidptr = (char*)0xb8000;
    for (int i = 0; i < 24 * 80 * 2; i++) {
        vidptr[i] = vidptr[i + 160];
    }

    for (int i = 24 * 80 * 2; i < 25 * 80 * 2; i += 2) {
        vidptr[i] = ' ';
        vidptr[i + 1] = 0x07;
    }
}

void kprint(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        
        if (str[i] == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            int offset = (cursor_y * 80 + cursor_x) * 2;
            char *vidptr = (char*)0xb8000;
            vidptr[offset] = str[i];
            vidptr[offset + 1] = 0x07; 
            cursor_x++;
        }

        if (cursor_x >= 80) {
            cursor_x = 0;
            cursor_y++;
        }
        if (cursor_y >= 25) {
            scroll();
            cursor_y = 24;
        }
    }
    update_cursor(cursor_x, cursor_y);
}

void kprint_int(int n) {
    if (n == 0) {
        kprint("0");
        return;
    }

    char buffer[12]; 
    int i = 0;
    
    while (n > 0) {
        buffer[i++] = (n % 10) + '0';
        n /= 10;
    }
    buffer[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }

    kprint(buffer);
}
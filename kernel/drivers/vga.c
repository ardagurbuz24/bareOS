#include <vga.h>
#include <io.h>
#include <util.h>
#include <stdint.h>

static uint16_t* const VIDEO_ADDRESS = (uint16_t*)0xB8000;
static const uint8_t DEFAULT_COLOR = 0x0F; 
static const int MAX_ROWS = 25;
static const int MAX_COLS = 80;

int get_cursor_offset() {
    outb(0x3D4, 14);
    int offset = inb(0x3D5) << 8;
    outb(0x3D4, 15);
    offset += inb(0x3D5);
    return offset * 2;
}

void set_cursor_offset(int offset) {
    offset /= 2; 
    outb(0x3D4, 14);
    outb(0x3D5, (uint8_t)(offset >> 8));
    outb(0x3D4, 15);
    outb(0x3D5, (uint8_t)(offset & 0xFF));
}


void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        VIDEO_ADDRESS[i] = (DEFAULT_COLOR << 8) | ' ';
    }
    set_cursor_offset(0);
}

void scroll() {
    for (int i = 0; i < (MAX_ROWS - 1) * MAX_COLS; i++) {
        VIDEO_ADDRESS[i] = VIDEO_ADDRESS[i + MAX_COLS];
    }

    for(int i = (MAX_ROWS - 1) * MAX_COLS; i < MAX_ROWS * MAX_COLS; i++) {
        VIDEO_ADDRESS[i] = (DEFAULT_COLOR << 8) | ' ';
    }
}

void kprint(char* message) {
    int offset = get_cursor_offset();
    int i = 0;
    while (message[i] != 0) {
        if (offset >= MAX_ROWS * MAX_COLS *2) {
            scroll();
            offset -= MAX_COLS * 2;
        }

        if (message[i] == '\n') {
            offset = (offset / 160 + 1) * 160;
        } else {
            VIDEO_ADDRESS[offset / 2] = (DEFAULT_COLOR << 8) | message[i];
            offset += 2;
        }
        i++;
    }
    set_cursor_offset(offset); 
}


void kprint_backspace() {
    int offset = get_cursor_offset() - 2; 
    
    if (offset < 0) return;

    VIDEO_ADDRESS[offset / 2] = (DEFAULT_COLOR << 8) | ' ';
    
    set_cursor_offset(offset);
}

void kprint_int(int n) {
    char str[12];
    int_to_ascii(n, str);
    kprint(str);
}
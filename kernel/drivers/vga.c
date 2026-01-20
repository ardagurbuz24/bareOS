#include <vga.h>
#include <io.h>
#include <stdint.h>

static uint16_t* const VIDEO_ADDRESS = (uint16_t*)0xB8000;
static const uint8_t DEFAULT_COLOR = 0x0F; 

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

void kprint(char* message) {
    int offset = get_cursor_offset();
    int i = 0;
    while (message[i] != 0) {
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
    if (n == 0) { kprint("0"); return; }
    char buffer[12];
    int i = 10;
    buffer[11] = '\0';
    while (n > 0) {
        buffer[i--] = (n % 10) + '0';
        n /= 10;
    }
    kprint(&buffer[i + 1]);
}
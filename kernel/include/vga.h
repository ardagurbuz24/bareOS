#ifndef VGA_H
#define VGA_H

#include <stdint.h>

void scroll();
void clear_screen();
void kprint(char* message);
void kprint_int(int n);
void set_cursor_offset(int offset);
int get_cursor_offset();
void kprint_backspace();

extern int cursor_x;
extern int cursor_y;

#endif
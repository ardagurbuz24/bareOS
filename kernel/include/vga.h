#ifndef VGA_H
#define VGA_H

void update_cursor(int x, int y);
void enable_cursor(unsigned char cursor_start, unsigned char cursor_end);
void scroll();
void clear_screen();
void kprint(const char *str);

extern int cursor_x;
extern int cursor_y;

#endif
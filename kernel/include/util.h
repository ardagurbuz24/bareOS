#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

int strcmp(char s1[], char s2[]);
int strlen(char s[]);
void int_to_ascii(int n, char str[]);
void reverse(char s[]);
void memory_set(uint8_t *dest, uint8_t val, uint32_t len);

#endif
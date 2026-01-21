#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include <stdint.h>

typedef struct {
    uint32_t flags;
    uint32_t mem_lower; // 0-640KB
    uint32_t mem_upper; // 1MB 
} __attribute__((packed)) multiboot_info_t;

#endif
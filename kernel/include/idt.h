#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct {
    uint16_t low_offset;  
    uint16_t sel;         
    uint8_t  always0;     
    uint8_t  flags;       
    uint16_t high_offset; 
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

void init_idt();
void set_idt_gate(uint8_t n, uint32_t handler, uint16_t sel, uint8_t flags);
extern void idt_flush(uint32_t); 

#endif
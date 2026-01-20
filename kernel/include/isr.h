#ifndef ISR_H
#define ISR_H

#include <stdint.h>

struct registers {
    uint32_t ds;                                     
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; 
    uint32_t int_no, err_code;                       
    uint32_t eip, cs, eflags, useresp, ss;           
} __attribute__((packed));

typedef struct registers registers_t;

void isr_handler(registers_t regs);

#endif
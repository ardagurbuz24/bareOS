#ifndef ISR_H
#define ISR_H
#define IRQ0 32
#define IRQ1 33

#include <stdint.h>


typedef struct {
    uint32_t ds;                                     
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; 
    uint32_t int_no, err_code;                       
    uint32_t eip, cs, eflags, useresp, ss;           
} __attribute__((packed)) registers_t;

typedef void (*isr_t)(registers_t*);
void register_interrupt_handler(uint8_t n, isr_t handler);

void isr_install();

void isr_handler(registers_t *regs);
void irq_handler(registers_t *regs);
#endif
#include <isr.h>
#include <vga.h>
#include <io.h>
#include <keyboard.h>

void isr_handler(registers_t *regs) {
    kprint("\n!!! INTERRUPTED !!!\n");
    kprint("Interrupt No: ");
    kprint_int(regs->int_no);
    kprint("\n");
    
    if (regs->int_no < 32) {
        kprint("System Halted (Exception).\n");
        for(;;); 
    }
}

void irq_handler(registers_t *regs) {
    if (regs->int_no >= 40) {
        outb(0xA0, 0x20); // Slave PIC EOI
    }
    outb(0x20, 0x20); // Master PIC EOI

    if (regs->int_no == 33) {
        keyboard_handler();
    }
}
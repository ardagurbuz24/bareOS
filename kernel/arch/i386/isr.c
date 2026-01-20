#include <isr.h>
#include <vga.h>

void isr_handler(registers_t regs) {
    kprint("\n!!! INTERRUPTED !!!\n");
    kprint("Interrupt No: ");
    kprint_int(regs.int_no);
    kprint("\n");
    
    if (regs.int_no < 32) {
        kprint("System Halted (Exception).\n");
        for(;;); 
    }
}
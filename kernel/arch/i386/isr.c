#include <isr.h>
#include <vga.h>
#include <io.h>
#include <gdt.h>
#include <idt.h>
#include <keyboard.h>

isr_t interrupt_handlers[256];

void isr_install() {
    
    init_gdt();
    init_idt();

    for (int i = 0; i < 256; i++) {
        interrupt_handlers[i] = 0;
    }
}

void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}


void isr_handler(registers_t *r) {
    kprint("Received Interrupt: ");
    kprint_int(r->int_no);
    kprint("\n");

    if (r->int_no == 13) {
        kprint("\n[CRITICAL] General Protection Fault (13)\n");
        kprint("EIP: "); kprint_int(r->eip); 
        kprint("\nSystem Halted.");
        asm volatile("cli; hlt"); 
    }

    if (interrupt_handlers[r->int_no] != 0) {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r);
    }
}

void irq_handler(registers_t *r) {
    if (interrupt_handlers[r->int_no] != 0) {
        isr_t handler = interrupt_handlers[r->int_no];
        handler(r);
    }

    if (r->int_no >= 40) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
}
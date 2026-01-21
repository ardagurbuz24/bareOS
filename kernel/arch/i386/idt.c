#include <idt.h>
#include <util.h>

idt_entry_t idt[256];
idt_ptr_t idt_ptr;

extern void isr0();  extern void isr1();  extern void isr2();  extern void isr3();
extern void isr4();  extern void isr5();  extern void isr6();  extern void isr7();
extern void isr8();  extern void isr9();  extern void isr10(); extern void isr11();
extern void isr12(); extern void isr13(); extern void isr14(); extern void isr15();
extern void isr16(); extern void isr17(); extern void isr18(); extern void isr19();
extern void isr20(); extern void isr21(); extern void isr22(); extern void isr23();
extern void isr24(); extern void isr25(); extern void isr26(); extern void isr27();
extern void isr28(); extern void isr29(); extern void isr30(); extern void isr31();

extern void irq0();  extern void irq1();

void set_idt_gate(uint8_t n, uint32_t handler, uint16_t sel, uint8_t flags) {
    idt[n].low_offset = (uint16_t)(handler & 0xFFFF);
    idt[n].sel = sel;
    idt[n].always0 = 0;
    idt[n].flags = flags; 
    idt[n].high_offset = (uint16_t)((handler >> 16) & 0xFFFF);
}

void init_idt() {
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base  = (uint32_t)&idt;

    memory_set((uint8_t *)&idt, 0, sizeof(idt_entry_t) * 256);

    set_idt_gate(0,  (uint32_t)isr0,  0x08, 0x8E);
    set_idt_gate(1,  (uint32_t)isr1,  0x08, 0x8E);
    set_idt_gate(2,  (uint32_t)isr2,  0x08, 0x8E);
    set_idt_gate(3,  (uint32_t)isr3,  0x08, 0x8E);
    set_idt_gate(4,  (uint32_t)isr4,  0x08, 0x8E);
    set_idt_gate(5,  (uint32_t)isr5,  0x08, 0x8E);
    set_idt_gate(6,  (uint32_t)isr6,  0x08, 0x8E);
    set_idt_gate(7,  (uint32_t)isr7,  0x08, 0x8E);
    set_idt_gate(8,  (uint32_t)isr8,  0x08, 0x8E);
    set_idt_gate(9,  (uint32_t)isr9,  0x08, 0x8E);
    set_idt_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    set_idt_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    set_idt_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    set_idt_gate(13, (uint32_t)isr13, 0x08, 0x8E); // GPF gate
    set_idt_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    set_idt_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    set_idt_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    set_idt_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    set_idt_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    set_idt_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    set_idt_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    set_idt_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    set_idt_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    set_idt_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    set_idt_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    set_idt_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    set_idt_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    set_idt_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    set_idt_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    set_idt_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    set_idt_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    set_idt_gate(31, (uint32_t)isr31, 0x08, 0x8E);

    set_idt_gate(32, (uint32_t)irq0, 0x08, 0x8E); // Timer
    set_idt_gate(33, (uint32_t)irq1, 0x08, 0x8E); // Keyboard

    idt_flush((uint32_t)&idt_ptr);
}
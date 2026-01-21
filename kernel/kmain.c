#include <io.h>
#include <vga.h>
#include <gdt.h>
#include <idt.h>
#include <keyboard.h>
#include <pic.h>
#include <stdint.h>
#include <util.h>
#include <timer.h>
#include <isr.h>
#include <multiboot.h>

void print_logo() {
        kprint("  ____                  ____   ____  \n");
        kprint(" | __ )  __ _ _ __ ___ / __ \\ / ___| \n");
        kprint(" |  _ \\ / _` | '__/ _ \\ |  | |\\___ \\ \n");
        kprint(" | |_) | (_| | | |  __/ |__| | ___) |\n");
        kprint(" |____/ \\__,_|_|  \\___|\\____/ |____/ \n");
        kprint("------------------------------------ \n");
        kprint("       BareOS v0.2 - Arda Gurbuz      \n\n");
}

multiboot_info_t* global_mbi;

void kmain(multiboot_info_t* mbi, uint32_t magic) {
    clear_screen();
    kprint("BareOS v0.2 is booting...\n");
    kprint("--------------------------\n");
    print_logo();

    global_mbi = mbi;

    kprint("Initializing GDT and IDT...\n");
    isr_install(); 

    pic_remap(0x20, 0x28);
    init_keyboard();

    kprint("BareOS v0.2 Memory Management Ready.\n");

    kprint("Starting PIT Timer (100Hz)...\n");
    init_timer(100);

    kprint("Enabling hardware interrupts...\n");
    asm volatile("sti");

    kprint("System ready. Type 'help' for commands.\n");
    kprint("> ");

    while(1) {
        asm volatile("hlt");
    }
}
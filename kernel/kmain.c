#include <io.h>
#include <vga.h>
#include <gdt.h>
#include <idt.h>
#include <keyboard.h>
#include <pic.h>

void print_logo() {
        kprint("  ____                  ____   ____  \n");
        kprint(" | __ )  __ _ _ __ ___ / __ \\ / ___| \n");
        kprint(" |  _ \\ / _` | '__/ _ \\ |  | |\\___ \\ \n");
        kprint(" | |_) | (_| | | |  __/ |__| | ___) |\n");
        kprint(" |____/ \\__,_|_|  \\___|\\____/ |____/ \n");
        kprint(" ------------------------------------ \n");
        kprint("       BareOS v0.1 - Arda Gurbuz      \n\n");
}

void kmain(void) {
    init_gdt();
    init_idt();
    pic_remap(0x20, 0x28);

    __asm__ __volatile__("cli");

    clear_screen();
    enable_cursor(0, 15);

    print_logo();
    kprint("BareOS>");

    while (1)
    {
        if (inb(0x64) & 0x01) {
            keyboard_handler();
        }
    }
    
}
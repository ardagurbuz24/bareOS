#include <io.h>
#include <vga.h>
#include <gdt.h>
#include <idt.h>
#include <keyboard.h>
#include <pic.h>
#include <stdint.h>
#include<util.h>

int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

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

    __asm__ __volatile__("sti");

    clear_screen();

    print_logo();
    kprint("BareOS>");

    while (1)
    {
        if (inb(0x64) & 0x01) {
             keyboard_handler();
        }
    }
    
}

void interpret_command(char* input) {
    if (strcmp(input, "help") == 0) {
        kprint("Available commands: help, clear, version\n");
    } else if (strcmp(input, "clear") == 0) {
        clear_screen();
    } else if (strcmp(input, "version") == 0) {
        kprint("BareOS v0.1 - Arda Gurbuz\n");
    } else if (strlen(input) > 0) {
        kprint("Unknown command: ");
        kprint(input);
        kprint("\n");
    }
}
#include <shell.h>
#include <vga.h>
#include <timer.h>
#include <util.h>
#include <multiboot.h>

extern multiboot_info_t* global_mbi;

extern uint32_t tick;

void interpret_command(char* input) {
    if (strlen(input) == 0) { kprint("\n> "); return; }

    
    if (strcmp(input, "help") == 0) {
        kprint("Commands: help, clear, uptime, version, meminfo\n");
    } else if (strcmp(input, "clear") == 0) {
        clear_screen();
    } else if (strcmp(input, "uptime") == 0) {
        kprint("Uptime: ");
        kprint_int(tick / 100);
        kprint("s\n");
    } else if (strcmp(input, "version") == 0) {
        kprint("BareOS v0.2.0-alpha (Jan 2026)\n");
    } else if (strcmp(input, "meminfo") == 0){
        uint32_t total_kb = global_mbi->mem_upper + 1024;
        uint32_t total_mb = total_kb / 1024;

        kprint("Memory Information:\n");
        kprint("Upper Memory: "); kprint_int(global_mbi->mem_upper); kprint(" KB\n");
        kprint("Total RAM: "); kprint_int(total_mb); kprint(" MB\n");
    } else {
        kprint("Unknown: "); kprint(input); kprint("\n");
    }
    kprint("> ");
}
#include<io.h>
#include<vga.h>

extern void keyboard_handler();

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
    clear_screen();
    enable_cursor(0, 15);

    
    char *vidptr = (char*)0xb8000;
    const char *str = "kernel is working";
    unsigned int i = 0;
    unsigned int j = 0;

    
    //clear the screen
    while(j < 80 * 25 * 2) {
        vidptr[j] = ' ';
        vidptr[j+1] = 0x07; 
        j = j + 2;
    }

    print_logo();
    kprint("BareOS>");
    

    while(1) {
        if(inb(0x64) & 0x01) {
            keyboard_handler();
        }
    }

    j = 0;
    
    // print text on the screen
    while(str[i] != '\0') {
        vidptr[j] = str[i];
        vidptr[j+1] = 0x0A; // 0x0A: neon green on black
        i++;
        j = j + 2;
    }
    return;
}
CC = gcc
AS = nasm
LD = ld

CFLAGS = -m32 -c -ffreestanding -fno-stack-protector -nostdlib -Ikernel/include
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T scripts/linker.ld

OBJ = boot/boot.o \
      boot/gdt_asm.o \
      boot/idt_asm.o \
      boot/interrupt.o \
      kernel/kmain.o \
      kernel/arch/i386/gdt.o \
      kernel/arch/i386/idt.o \
      kernel/arch/i386/isr.o \
      kernel/drivers/vga.o \
      kernel/drivers/keyboard.o \
	  kernel/drivers/pic.o

TARGET = kernel.bin

all: $(TARGET)

boot/boot.o: boot/boot.asm
	$(AS) $(ASFLAGS) boot/boot.asm -o boot/boot.o

boot/gdt_asm.o: boot/gdt.asm
	$(AS) $(ASFLAGS) boot/gdt.asm -o boot/gdt_asm.o

boot/idt_asm.o: boot/idt.asm
	$(AS) $(ASFLAGS) boot/idt.asm -o boot/idt_asm.o

boot/interrupt.o: boot/interrupt.asm
	$(AS) $(ASFLAGS) boot/interrupt.asm -o boot/interrupt.o

kernel/kmain.o: kernel/kmain.c
	$(CC) $(CFLAGS) kernel/kmain.c -o kernel/kmain.o

kernel/arch/i386/gdt.o: kernel/arch/i386/gdt.c
	$(CC) $(CFLAGS) kernel/arch/i386/gdt.c -o kernel/arch/i386/gdt.o

kernel/arch/i386/idt.o: kernel/arch/i386/idt.c
	$(CC) $(CFLAGS) kernel/arch/i386/idt.c -o kernel/arch/i386/idt.o

kernel/arch/i386/isr.o: kernel/arch/i386/isr.c
	$(CC) $(CFLAGS) kernel/arch/i386/isr.c -o kernel/arch/i386/isr.o

kernel/drivers/vga.o: kernel/drivers/vga.c
	$(CC) $(CFLAGS) kernel/drivers/vga.c -o kernel/drivers/vga.o

kernel/drivers/keyboard.o: kernel/drivers/keyboard.c
	$(CC) $(CFLAGS) kernel/drivers/keyboard.c -o kernel/drivers/keyboard.o

kernel/drivers/pic.o: kernel/drivers/pic.c
	$(CC) $(CFLAGS) kernel/drivers/pic.c -o kernel/drivers/pic.o

$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(TARGET)

run: all
	qemu-system-i386 -kernel $(TARGET)

clean:
	rm -f boot/*.o kernel/*.o kernel/arch/i386/*.o kernel/drivers/*.o $(TARGET)
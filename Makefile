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
      kernel/shell.o \
      kernel/util.o \
      kernel/arch/i386/gdt.o \
      kernel/arch/i386/idt.o \
      kernel/arch/i386/isr.o \
      kernel/drivers/vga.o \
      kernel/drivers/keyboard.o \
      kernel/drivers/pic.o \
	  kernel/drivers/io.o \
      kernel/drivers/timer.o

TARGET = kernel.bin

all: $(TARGET)

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) $< -o $@

kernel/arch/i386/%.o: kernel/arch/i386/%.c
	$(CC) $(CFLAGS) $< -o $@

kernel/drivers/%.o: kernel/drivers/%.c
	$(CC) $(CFLAGS) $< -o $@

boot/%.o: boot/%.asm
	$(AS) $(ASFLAGS) $< -o $@

boot/gdt_asm.o: boot/gdt.asm
	$(AS) $(ASFLAGS) boot/gdt.asm -o boot/gdt_asm.o

boot/idt_asm.o: boot/idt.asm
	$(AS) $(ASFLAGS) boot/idt.asm -o boot/idt_asm.o

$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(TARGET)

run: all
	qemu-system-i386 -kernel $(TARGET)

clean:
	rm -rf boot/*.o kernel/*.o kernel/arch/i386/*.o kernel/drivers/*.o $(TARGET)
CC = gcc
AS = nasm
LD = ld

CFLAGS = -m32 -c -ffreestanding -fno-stack-protector -nostdlib -Ikernel/include
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T scripts/linker.ld

TARGET = kernel.bin
OBJ = boot/boot.o kernel/kmain.o kernel/drivers/keyboard.o kernel/drivers/vga.o

all: $(TARGET)

boot/boot.o: boot/boot.asm
	$(AS) $(ASFLAGS) boot/boot.asm -o boot/boot.o


kernel/kmain.o: kernel/kmain.c
	$(CC) $(CFLAGS) kernel/kmain.c -o kernel/kmain.o


kernel/drivers/keyboard.o: kernel/drivers/keyboard.c
	$(CC) $(CFLAGS) kernel/drivers/keyboard.c -o kernel/drivers/keyboard.o


$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(TARGET)


run: all
	qemu-system-i386 -kernel $(TARGET)


clean:
	rm -f boot/*.o kernel/*.o kernel/drivers/*.o $(TARGET)
[BITS 32]
ALIGN 4
[EXTERN isr_handler]
[EXTERN irq_handler]

%macro ISR_NOERRCODE 1
  [GLOBAL isr%1]
  isr%1:
    cli              
    push byte 0      
    push byte %1     
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
  [GLOBAL isr%1]
  isr%1:
    cli              
    push byte %1     
    jmp isr_common_stub
%endmacro

%macro IRQ 2
  [GLOBAL irq%1]
  irq%1:
    cli
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro


ISR_NOERRCODE 0   ; Divide by Zero
ISR_NOERRCODE 1   ; Debug
ISR_NOERRCODE 2   ; Non Maskable Interrupt
ISR_NOERRCODE 3   ; Breakpoint
ISR_NOERRCODE 4   ; Into Detected Overflow
ISR_NOERRCODE 5   ; Out of Bounds
ISR_NOERRCODE 6   ; Invalid Opcode
ISR_NOERRCODE 7   ; No Coprocessor

ISR_ERRCODE   8   ; Double Fault 
ISR_NOERRCODE 9   ; Coprocessor Segment Overrun
ISR_ERRCODE   10  ; Bad TSS
ISR_ERRCODE   11  ; Segment Not Present
ISR_ERRCODE   12  ; Stack Fault
ISR_ERRCODE   13  ; General Protection Fault 
ISR_ERRCODE   14  ; Page Fault
ISR_NOERRCODE 15  ; Unknown Interrupt

ISR_NOERRCODE 16  ; x87 FPU Error
ISR_NOERRCODE 17  ; Alignment Check
ISR_NOERRCODE 18  ; Machine Check
ISR_NOERRCODE 19  ; SIMD Floating-Point
ISR_NOERRCODE 20  ; Virtualization
ISR_NOERRCODE 21  ; Reserved
ISR_NOERRCODE 22  ; Reserved
ISR_NOERRCODE 23  ; Reserved
ISR_NOERRCODE 24  ; Reserved
ISR_NOERRCODE 25  ; Reserved
ISR_NOERRCODE 26  ; Reserved
ISR_NOERRCODE 27  ; Reserved
ISR_NOERRCODE 28  ; Reserved
ISR_NOERRCODE 29  ; Reserved
ISR_NOERRCODE 30  ; Reserved
ISR_NOERRCODE 31  ; Reserved

IRQ 0, 32    ; Timer
IRQ 1, 33    ; Keyboard

[GLOBAL isr_common_stub]
isr_common_stub:
    pusha                ;  (eax, ecx, edx, ebx, esp, ebp, esi, edi)
    
    mov ax, ds
    push eax             ; 4 byte (data segment)

    mov ax, 0x10         ; Kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp             
    call isr_handler
    add esp, 4           ; clear ESP

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    popa
    add esp, 8           
    iret

irq_common_stub:
    pusha

    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call irq_handler
    add esp, 4

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    popa
    add esp, 8
    iret
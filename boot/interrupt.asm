; BareOS Interrupt Stubs
[bits 32]

extern isr_handler
extern irq_handler

; ISR (Exceptions 0-31) 
%macro ISR_NOERRCODE 1
  global isr%1
  isr%1:
    push byte 0      
    push byte %1     
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
  global isr%1
  isr%1:
    push byte %1     
    jmp isr_common_stub
%endmacro

; IRQ (Hardware 32-47)
%macro IRQ 2
  global irq%1
  irq%1:
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro

ISR_NOERRCODE 0  ; Divide By Zero Exception
ISR_NOERRCODE 1  ; Debug Exception
ISR_NOERRCODE 2  ; Non Maskable Interrupt Exception
ISR_NOERRCODE 3  ; Breakpoint Exception
ISR_NOERRCODE 4  ; Into Detected Overflow Exception
ISR_NOERRCODE 5  ; Out of Bounds Exception
ISR_NOERRCODE 6  ; Invalid Opcode Exception
ISR_NOERRCODE 7  ; No Coprocessor Exception

ISR_ERRCODE   8  ; Double Fault 
ISR_NOERRCODE 9  ; Coprocessor Segment Overrun
ISR_ERRCODE   10 ; Bad TSS
ISR_ERRCODE   11 ; Segment Not Present
ISR_ERRCODE   12 ; Stack Fault
ISR_ERRCODE   13 ; General Protection Fault 
ISR_ERRCODE   14 ; Page Fault
ISR_NOERRCODE 15 ; Unknown Interrupt Exception

ISR_NOERRCODE 16 ; x87 FPU Floating-Point Error
ISR_ERRCODE   17 ; Alignment Check
ISR_NOERRCODE 18 ; Machine Check
ISR_NOERRCODE 19 ; SIMD Floating-Point Exception
ISR_NOERRCODE 20 ; Virtualization Exception
ISR_NOERRCODE 21 ; Control Protection Exception 
ISR_NOERRCODE 22 ; Reserved
ISR_NOERRCODE 23 ; Reserved
ISR_NOERRCODE 24 ; Reserved
ISR_NOERRCODE 25 ; Reserved
ISR_NOERRCODE 26 ; Reserved
ISR_NOERRCODE 27 ; Reserved
ISR_NOERRCODE 28 ; Reserved
ISR_NOERRCODE 29 ; Reserved
ISR_ERRCODE   30 ; Security Exception
ISR_NOERRCODE 31 ; Reserved

IRQ 0, 32 ; Timer
IRQ 1, 33 ; Keyboard


isr_common_stub:
    pushad              ; EAX, ECX, EDX, EBX, etc.
    mov ax, ds          
    push eax

    mov ax, 0x10        
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp            
    call isr_handler
    add esp, 4          ; clean ESP

    pop eax             
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popad               
    add esp, 8          
    iret                

irq_common_stub:
    pushad
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

    popad
    add esp, 8
    iret
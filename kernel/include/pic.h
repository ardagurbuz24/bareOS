#ifndef PIC_H
#define PIC_H

#include <stdint.h>

#define PIC1          0x20    /* Master */
#define PIC1_COMMAND  PIC1
#define PIC1_DATA     (PIC1 + 1)
#define PIC2          0xA0    /* Slave  */
#define PIC2_COMMAND  PIC2
#define PIC2_DATA     (PIC2 + 1)

#define PIC_EOI       0x20    /* End of Interrupt */
#define ICW1_INIT     0x11    /* Start */
#define ICW4_8086     0x01    /* 8086/88 (MCS-80/85) */

void pic_remap(uint8_t offset1, uint8_t offset2);
void pic_send_eoi(unsigned char irq);

#endif
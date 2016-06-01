//isr.c
#include "isr.h"
void delayme();
void isr_handler(registers_t regs)
{
	irq_handler(regs);
		return;
	
   //kprintf("recieved interrupt: ");
   //kprintf("%x\n", regs.int_no);
   //kprintf("ds: %ud\tedi: %ud\tesi: %ud\tebp: %ud\tesp: %ud\tebx: %ud\tedx: %ud\tecx: %ud\neax: %ud\n", regs.ds, regs.edi, regs.esi, regs.ebp, regs.esp, regs.ebx, regs.edx, regs.ecx, regs.eax);
   //kprintf("int no: %ud\terr code: %ud\n", regs.int_no, regs.err_code);
}

isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}
void irq_handler(registers_t regs)
{
   // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.int_no >= 40)
   {
       // Send reset signal to slave.
       outb(0xA0, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   outb(0x20, 0x20);

   if (interrupt_handlers[regs.int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs.int_no];
       handler(regs);
   }
}

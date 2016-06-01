//exceptions.c
#include "exceptions.h"
void init_exceptions()
{
   register_interrupt_handler(0, &divide_by_0_callback);
}

void divide_by_0_callback(registers_t regs)
{
	panic("DO NOT DIVIDE BY 0! %8ux\n", regs.cs);//kernel panic because of /0 
}

void panic(char* error, ...)
{//print panic info
	va_list argptr;
	va_start(argptr, error);
	vgainit();
	kprintf(error, argptr);
	status("KERNEL PANIC", "DIVIDE BY 0");
	asm ( "hlt;\n\t" );
}

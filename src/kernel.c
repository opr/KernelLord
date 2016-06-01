#include "globals.h"
#include "multiboot.h"

void
abort( ) {
   kprintf ( "\n**** ABORT! ****\n");
   kprintf ( "Processor halted\n");
   asm ( "hlt;\n\t" );
}

void
kmain( void* mbd, unsigned int magic ) {
	status ("SCC211 Operating Systems kernel", "Tick: 0");
	getbootinfo (mbd, magic);
	asm volatile ("sti");
	kprintf("End of kernel\n");
	for(;;);
	/* getbootinfo (mbd, magic);
	getbootinfo (mbd, magic);
	getbootinfo (mbd, magic);
	getbootinfo (mbd, magic);
	getbootinfo (mbd, magic);
	getbootinfo (mbd, magic);
	kprintf("Hello123\rbbbb\n");
	kprintf("1111111111111111111111111111111111111111111111111222222222222222222222222222222222222223333333333333333333333333333333333333333");
	abort( );*/
}

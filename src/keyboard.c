//keyboard.c
#include "keyboard.h"

void init_keyboard()
{
   register_interrupt_handler(33, &keyboard_callback);
}

void keyboard_callback()
{
	int scancode = inb(0x60);
	kprintf("%c", getkey(scancode));//write the scanned code as a letter to the screen
}

char getkey(int code)
{
	if(code>80) return 0;
	if(code>0x53) code-=3;
	return keys[code-1];//lookup the letter in the list of keys
}

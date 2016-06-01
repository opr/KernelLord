#include "globals.h"
#include "isr.h"
//0xf0 = backspace
//0xf1 = enter 
//0xf2 = left control
//0xf3 = left shift
//0xf4 = right shift
//0xf5 = left alt
//0xf6 = caps lock

//0xe0 = f1
//0xe9 = f10
//0xea = f11
//0xeb
int keys[0x81] = {'\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', -0xf0, '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', -0xf2, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', -0xf3, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', -0xf4, '*', -0xf5, ' ', -0xf6, -0xe0, -0xe1, -0xe2, -0xe3, -0xe4, -0xe5, -0xe6, -0xe7, -0xe8, -0xe9, -0xb0, -0xb1, '7', '8', '9', '-', '4', '5', '6', '+', '1','2', '3', '0', '.', -0xea, -0xeb};

char getkey(int);
void init_keyboard();
void keyboard_callback();

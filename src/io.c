#include "globals.h"

inline void
outb (uint16_t port, uint8_t n) {
   asm volatile (
                  "outb %0, %1;\n\t"
                :                       // Outputs
                : "a" (n), "Nd" (port)  // Inputs
                );
}

inline
unsigned char inb( unsigned short port )
{
    unsigned char ret;
    asm volatile( "inb %1, %0"
                  : "=a"(ret) : "Nd"(port) );
    return ret;
}

void *memset(void *s, int c, size_t n)
{
    unsigned char* p=s;
    while(n--)
        *p++ = (unsigned char)c;
    return s;
}

inline
void io_wait( void )
{
    asm volatile( "jmp 1f\n\t"
                  "1:jmp 2f\n\t"
                  "2:" );
}

#ifndef __GLOBALS__
#define __GLOBALS__

#define BREAK(); asm volatile ( "xchg %bx, %bx;" ); /* Bochs magic break code */
#define NULL 0

//
//	======================== TYPES ========================
//
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned long      uint32_t;
typedef unsigned long long uint64_t;

typedef unsigned long      size_t;

//typedef char      int8_t;
typedef short     int16_t;
typedef long      int32_t;
typedef long long int64_t;

//
//	=================== PUBLIC FUNCTIONS ===================
//

// kernel.c
void kmain    ( void *, unsigned int );
void abort    ( void );

//keyboard.c
void init_keyboard();

//tables.c
void init_descriptor_tables();

// io.c
void     outb    ( uint16_t, uint8_t  );
unsigned char 	 inb(unsigned short);
void *memset(void *, int , size_t);
inline void io_wait(void);
// multiboot.c
void getbootinfo (void *, unsigned int );

//exceptions.c
void register_exceptions();
void panic(char*, ...);

//timer.c
void init_timer(uint32_t);

// printk.c
void kprintf(char * string, ...);
void printString(char * string, int w, int pad);
void printNum(int i, int w, int pad, int base, int u);
void cleanBuffer(char* buffer, int len);
void cleanBufferInt(int buffer[], int len);
void printChar(int c, int w, int pad);

// vga.c
void putchar  ( char   );
void vgainit  ( void   );
void status   ( char *, char* );

#endif //__GLOBALS__

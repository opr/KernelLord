#include "globals.h"
#include "vga.h"

static uint16_t * videoram = (uint16_t *) 0xb8000;

static const uint16_t ctrlreg = 0x03D4; // Address on I/O bus
static const uint16_t datareg = 0x03D5; // Address on I/O bus

static const int linelen   = 80;
static const int lines     = 24;

static int x = 0;
static int y = 0;

//
//   Move cursor to position x,y
//   - Notice this uses isolated I/O
//
void
setcursor (int x, int y) {
   uint16_t posn;

   posn = y * linelen + x;
   outb (ctrlreg, 14);
   outb (datareg, posn >> 8);
   outb (ctrlreg, 15);
   outb (datareg, posn &  0xff);
}

//
//   Clear the screen and move cursor to position 0,0
//
void
vgainit ( ) {
   uint16_t * screenp = videoram;
   //
   //   Clear the screen
   //
   int i=0;
	for(; i<=(linelen*lines)-1; i++)
	{
		*screenp++ = ' ' | FOREGROUND(WHITE) | BACKGROUND(BLUE);
	}

   x = 0; y = 0;
   setcursor(x, y);

   
}

uint16_t offset()
{//find the address in vram by looking at the x and y coordinates
	if(x==0&&y==0) return 0;
	if(x==0) return (y*linelen);
	if(y==0) return x;
	return ((y*linelen)+x);
}

void scrollLine()
{
	uint16_t * screenp = videoram;
	int i;
	for(i=0; i<(linelen*lines)-linelen; i++)
	{
		*screenp = *(screenp+80);
		screenp++;//scroll the line by adding 1 to y and dropping the x to 0
	}
	screenp = videoram+((linelen*lines)-(linelen));
	for(i=0; i<linelen; i++)
	{
		*screenp++ = ' ' | FOREGROUND(WHITE) | BACKGROUND(BLUE);
	}
	
}

void delay()
{//add a wee delay to the scrolling so it looks cool... o_O
	int i,j,k, m=0;
	for(i=0; i<100; i++)
	{
		
	for(j=0; j<100; j++)
	{
		
	for(k=0; k<100; k++)
	{
		m++;
	}
	}
	}
}

void
putchar (char c) {
	uint16_t * screenp = (videoram+offset()); //where the last written char is
   if(c=='\0') return;
   if(c=='\n')
	{
		x=0;
		y++;
		delay();
		
	}
	else if(c=='\r') x=0;
	else if(c=='\t')
	{
		while(++x%5!=0);
	}
	else
	{
		
		*screenp = c | FOREGROUND(WHITE) | BACKGROUND(BLUE);
		x++;
	}
   //*screenp++ = 'C' | FOREGROUND(WHITE) | BACKGROUND(BLUE);
   //*screenp++ = 'S' | FOREGROUND(WHITE) | BACKGROUND(BLUE);
   //
   //   Store character value (with colour information) at memory location
   //   of current x,y screen position and update x and y ready to move
   //   the cursor.
   //
   //   Remember that you'll need to handle reaching the end of lines and
   //   the bottom of the screen. Don't forget that, if you plan on having
   //   a status line you need to ensure you consider this when you're
   //   calculating the limit of the display area.
   //
   if(x==79)
   {
	   x=0;
	   y++;
   }
   if(y>lines-1)
   {
	   scrollLine();
	   y--;
	   x=0;
   }
   setcursor (x, y);
}

void
status ( char * str, char* tick ) {

   if (!str) return;
	
   uint16_t * screenp = videoram+(lines*80);
   int i=0;//same as putchar but just different colours and in a set position
	while(*str != '\0' && i<80)
	{
		*screenp++ = *str | FOREGROUND(BLUE) | BACKGROUND(WHITE);
		i++;
		str++;
	}
	
	*screenp++ = ' ' | FOREGROUND(BLUE) | BACKGROUND(WHITE);
	*screenp++ = ' ' | FOREGROUND(BLUE) | BACKGROUND(WHITE);
	*screenp++ = ' ' | FOREGROUND(BLUE) | BACKGROUND(WHITE);
	i+=3;
	
	while(*tick != '\0' && i<80)
	{
		*screenp++ = *tick | FOREGROUND(BLUE) | BACKGROUND(WHITE);
		i++;
		tick++;
	}
	
	while(i++<80)
	{
		*screenp++ = ' ' | FOREGROUND(BLUE) | BACKGROUND(WHITE);
	}   
   //
   //   Display string in status line. This should be a simpler version
   //   of what you have for putchar as it'll simply be overwriting what's
   //   there, so no scrolling.
   //
   //   Use different colours for the status line so 
   //
}

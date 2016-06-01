#include <stdarg.h>
#include "globals.h"

void cleanBufferInt(int buffer[], int len)
{//this method cleans an int buffer of length len to set all characters to null.
	int array;
	for(array=0; array<len; array++) //loop and set to null.
	{
		buffer[array] = '\0';
	}
	
}

void cleanBuffer(char* buffer, int len)
{//this method cleans a char* buffer of length len to set all characters to null.
	int array;
	for(array=0; array<len; array++)
	{
		buffer[array] = '\0';
	}
}

void printNum(int i, int w, int pad, int base, int u)
{//prints numbers, i is the number to be printed, w is the width, pad is
//the character with which to pad, base is obviously the base, and u shows signed/unsignedness.
	unsigned int j = i;
	if(i<0 && u==0){
		putchar('-'); //if it's not unsigned, and is negative print a - sign, and convert to a positive number.
		i-=(i*2); //this turns a negative number into the positive of itself.
	}
	if(base != 10) putchar('0'); //formatting nicely
	if(base==16) putchar('x');
	if(base==8)	putchar('o');
	if(base == 2) putchar('b');
	
	int buf[32];
	cleanBufferInt(buf, 32);
	char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	int bufferCount=0;
	if(u==0)
	{
		while(i>0)
		{
			int units = i%base;
			i=i/base;
			buf[bufferCount++] = units;//put into the cleaned buffer, the number you get
		}
	}
	else
	{
		while(j>0) //horrid workaround for unsigned numbers as i didnt know how to handle them properly.
		{
			int units = j%base;
			j/=base;
			buf[bufferCount++] = units;
		}
	}
		while(w---bufferCount > 0) putchar(pad);
		while(bufferCount-1>=0)
		{
			putchar(hex[buf[--bufferCount]]); //print the buffer in reverse
		}
	
	
}

void printString(char* string, int w, int pad)
{//prints a string until \0. can also pad it if you like...
	char * strTmp = string;
	int count=0;
	while(*strTmp++ != '\0') count++;
	while(w---count>0) putchar(pad);
	while(*string != '\0') putchar(*string++);
}

void printChar(int c, int w, int pad)
{//prints a char, again if you realllllly want to pad it you can.
	while(--w>0) putchar(pad);
	putchar(c);
}


void kprintf(char* string, ...)
{//hurray kprintf...
	va_list ap; //init of the vararg 
	char *c; //a pointer to the string
	va_start(ap, string);//start the vararg stuff
	for(c = string; *c!='\0'; c++)
	{
		if(*c!='%')
		{
			putchar(*c); //if it;s not a % then just print it!
			continue;
		}
		else
		{			
			int formatLoopFlag = 0, width=0, u=0, readBuffer=0;
			char* charToPrint;
			char tmpChar = *++c;         //doing init stuff
			int formatting[256];		 //resetting vars and such
			int padChar = '0';
			cleanBufferInt(formatting, 256);
			while(tmpChar!='s' && tmpChar!='c' && tmpChar!='d' && tmpChar!='b' && tmpChar!='o' && tmpChar!='x' && tmpChar!='%')
			{
				if(tmpChar == 'u') u=1;
				else formatting[readBuffer++] = tmpChar;
				tmpChar = *++c;
			}//loops through reading all of the formatting information for the %symbol
			
			if(readBuffer>0){//not a nice way of doing stuff, but basically finds how big you want to pad the number
				if(formatting[formatLoopFlag] == '0')
				{
					padChar=formatting[formatLoopFlag];
					while(formatting[formatLoopFlag++] != '\0') width= (width*10)+formatting[formatLoopFlag-1]-48;
				}
				else if(formatting[formatLoopFlag]>'9')
				{
					padChar=formatting[formatLoopFlag];
					while(formatting[++formatLoopFlag] != '\0') width= (width*10)+formatting[formatLoopFlag]-48;
				}
				else
				{
					while(formatting[formatLoopFlag++] != '\0') width= (width*10)+formatting[formatLoopFlag-1]-48;
				}
			}
			switch(*c)//now if it's a control character, print the appropriate thing
			{
				case 's':	//string printing
				charToPrint = va_arg(ap, char*);
				if(charToPrint==NULL) kprintf("(null)");
				else printString(charToPrint, width, padChar);
				break;
				case 'd':	//int printing
				printNum(va_arg(ap, int), width, padChar, 10, u);
				break;
				case 'c'://char printing
				printChar(va_arg(ap, int), width, padChar);
				break;
				case '%': //%printing
				putchar('%');
				break;
				case 'x':	//hex printing
				printNum(va_arg(ap, int), width, padChar, 16, u);
				break;
				case 'b'://bin printing
				printNum(va_arg(ap, int), width, padChar, 2, u);
				break;
				case 'o'://oct printing
				printNum(va_arg(ap, int), width, padChar, 8, u);
				break;
			}
		}
	}
}

/*
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/sysctl.h"
#include "grlib/grlib.h"
#include "Kentec320x240x16_SSD2119_SPI.h"
#include "img_balls.h"
#include "utils/ustdlib.h"
#include "Labs/labs.h"

void printDisp(char* format,...);
char *convert(unsigned int num, int base);
void putchar(char u8Char);
void puts(char * pu8Char);

void printDisp(char* format,...)
{
	char *traverse;
	int i;
	char *s;

	va_list arg;
	va_start(arg, format);
	traverse = format;

	while ('\0' != *traverse)
	{
		if ('%' == *traverse)
		{
			traverse++;
			switch(*traverse)
			{
				case 'c' : i = va_arg(arg,int);
				putchar(i);
				break;
				case 'd' : i = va_arg(arg,int);
				if(i<0)
				{
					i = -i;
					putchar('-');
				}
				puts(convert(i,10));
				break;
				case 'o': i = va_arg(arg,unsigned int);
				puts(convert(i,8));
				break;
				case 's': s = va_arg(arg,char *);
				puts(s);
				break;
				case 'x': i = va_arg(arg,unsigned int);
				puts("0x");
				puts(convert(i,16));
				break;
			}
		}
		else
		{
			putchar(*traverse);
		}
		traverse++;
	}
	va_end(arg);
}

char *convert(unsigned int num, int base)
{
	static char Representation[]= "0123456789ABCDEF";
	static char buffer[50];
	char *ptr;

	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = Representation[num%base];
		num /= base;
	}while(num != 0);

	return(ptr);
}

void puts(char * pu8Char)
{
	while('\0' != *pu8Char)
	{
		putchar(*pu8Char);
		pu8Char++;
	}
}

void putchar(char u8Char)
{
	static tContext sContext;
	static tRectangle sRect;
	static uint32_t u32CurrentX = 0;
	static uint32_t u32CurrentY = 0;
	if (NULL == sContext.psDisplay)
	{
		Kentec320x240x16_SSD2119Init();
		GrContextInit(&sContext, &g_sKentec320x240x16_SSD2119);
		GrContextFontSet(&sContext, &g_sFontCm12);
	}
	if ('\n' == u8Char)
	{
		GrFlush(&sContext);
		u32CurrentX = 0;
		u32CurrentY = u32CurrentY + 15;
		if (240 < u32CurrentY)
		{
			u32CurrentY = 0;
		}
	}
	else
	{
		sRect.i16XMin = u32CurrentX;
		sRect.i16YMin = u32CurrentY;
		sRect.i16XMax = u32CurrentX + 10;
		sRect.i16YMax = u32CurrentY + 15;
		GrContextForegroundSet(&sContext, ClrBlack);
		GrRectFill(&sContext, &sRect);
		GrContextForegroundSet(&sContext, ClrWhite);
		GrStringDraw(&sContext, &u8Char, -1, u32CurrentX, u32CurrentY, 0);
		u32CurrentX = u32CurrentX + 10;
	}
}

int main(void)
{
	uint32_t u32CurrTemp =0;

	SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	vMeassureIntTemperatureInit();

	printDisp("Start aplikace\n");
	vMeassureIntTemperature(&u32CurrTemp);
	printDisp("Aktualni teplota %d C\n", u32CurrTemp);
	//vRunLab03();
	//vRunLab04();
	while (true)
	{



	}

}

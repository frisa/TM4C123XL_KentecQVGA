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

tContext sContext;
tRectangle sRect;
unsigned char idx = 0;
char str[10];


int main(void)
{
   SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
   Kentec320x240x16_SSD2119Init();
   GrContextInit(&sContext, &g_sKentec320x240x16_SSD2119);

   sRect.i16XMin = 0;
   sRect.i16YMin = 0;
   sRect.i16XMax = GrContextDpyWidthGet(&sContext) - 1;
   sRect.i16YMax = 23;
   GrContextForegroundSet(&sContext, ClrDarkBlue);
   GrRectFill(&sContext, &sRect);
   GrContextForegroundSet(&sContext, ClrWhite);
   GrRectDraw(&sContext, &sRect);
   GrContextFontSet(&sContext, &g_sFontCm20);
   GrStringDrawCentered(&sContext, "Testovaci aplikace", -1, GrContextDpyWidthGet(&sContext) / 2, 8, 0);
   GrStringDraw(&sContext, "USB Driver Data:", -1, 0, 30, 0);
   GrFlush(&sContext);

   while(1)
   {
	   usprintf(str,"%d", idx++);
	   GrContextForegroundSet(&sContext, ClrWhite);
	   GrStringDraw(&sContext, str, -1, 170, 30, 0);
	   SysCtlDelay(800000);
	   GrContextForegroundSet(&sContext, ClrBlack);
	   GrStringDraw(&sContext, str, -1, 170, 30, 0);
   }

}

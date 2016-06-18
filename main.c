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

tContext sContext;
tRectangle sRect;
unsigned char idx = 0;
char str[10];

void gpxPrint(char * pui8String)
{

}


int main(void)
{
   uint32_t ui32TempC, ui32TempCOld;
   char piu8TempCStr[10], piu8TempCOldStr[10];

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
   GrStringDraw(&sContext, "Idx:", -1, 0, 30, 0);
   GrStringDraw(&sContext, "Temp:", -1, 80, 30, 0);
   GrFlush(&sContext);

   /* initialization of the meassurement of processor temperature from lab5*/
   vMeassureIntTemperatureInit();

   while(1)
   {
	   /* clear the context */
	   GrContextForegroundSet(&sContext, ClrBlack);
	   GrStringDraw(&sContext, str, -1, 40, 30, 0);

	   vMeassureIntTemperature(&ui32TempC);
	   if (ui32TempC != ui32TempCOld)
	   {
		   usprintf(piu8TempCOldStr,"%d", ui32TempCOld);
		   GrContextForegroundSet(&sContext, ClrBlack);
		   GrStringDraw(&sContext, piu8TempCOldStr, -1, 140, 30, 0);

		   usprintf(piu8TempCStr,"%d", ui32TempC);
		   GrContextForegroundSet(&sContext, ClrWhite);
		   GrStringDraw(&sContext, piu8TempCStr, -1, 140, 30, 0);
		   ui32TempCOld = ui32TempC;
	   }

	   /* show the context */
	   GrContextForegroundSet(&sContext, ClrWhite);
	   usprintf(str,"%d", ++idx);
	   GrStringDraw(&sContext, str, -1, 40, 30, 0);
	   SysCtlDelay(800000);

	   //vRunLab03();
	   //vRunLab04();
	   //vRunLab05();
   }

}

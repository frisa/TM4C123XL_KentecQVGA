/*
 * lab3.c
 *
 *  Created on: May 28, 2016
 *      Author: root
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

uint8_t ui8PinData = 2;

void vRunLab03(void)
{
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8PinData);
	SysCtlDelay(2000000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
	SysCtlDelay(2000000);
	if(ui8PinData==8) {ui8PinData=2;} else {ui8PinData=ui8PinData*2;}
}

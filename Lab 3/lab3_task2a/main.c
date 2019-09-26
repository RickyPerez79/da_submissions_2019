// Task 2a
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
// pin1 = r
// pin2 = b
// pin3 = g
//uint8_t ui8PinData=2; 001 0 -> r
//uint8_t ui8PinData=4; 010 0 -> b
//uint8_t ui8PinData=8; 100 0 -> g

// B G R
// 4,8,2

int main(void)
{
    uint8_t ui8PinData=4;
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    while(1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, ui8PinData);
        SysCtlDelay(10000000); // made delay slower to see the colors
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);
        SysCtlDelay(10000000); // made delay slower to see the colors
        if(ui8PinData==8){ui8PinData=2;} else {ui8PinData*=2;}
    }

}

// Task 2b
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
// pin1 = r
// pin2 = b
// pin3 = g
// uint8_t ui8PinData=2; 001 0 -> r
// uint8_t ui8PinData=4; 010 0 -> b
// uint8_t ui8PinData=8; 100 0 -> g

uint8_t ui8PinData=1;

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    while(1)
    {
        while(ui8PinData<10)
        {
        ui8PinData *= 2; // R,G,B
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8PinData);
        SysCtlDelay(10000000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
        SysCtlDelay(10000000);
        if(ui8PinData==4){ui8PinData=10;} // once it reaches to 4 it will exit the loop
        if(ui8PinData==2){ui8PinData*=2;}
        if(ui8PinData==8){ui8PinData=2;}
        }
        ui8PinData = 8;
        while (ui8PinData < 16)
        {
        /*
          (sequence of blinking with delay – R, G, B, RG, RB, GB, RGB, R, G, …)
          R = 0010 = 2
          B = 0100 = 4
          G = 1000 = 8
          RG = 1010 = 10
          RB = 0110 = 6
          GB = 1100 = 12
          RBG = 1110 = 14
         */
        ui8PinData +=2; // starts at RG
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, (ui8PinData));
        SysCtlDelay(10000000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1, 0x00);
        SysCtlDelay(10000000);
        if (ui8PinData == 14) {ui8PinData +=2;}
        if (ui8PinData == 10){ui8PinData = 4;}
        if (ui8PinData == 6) {ui8PinData = 10;}
        }
        ui8PinData = 1; // reinitialize
    }

}

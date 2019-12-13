// task 02
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"

int main(void)
{

    int i; //for loop temp variable
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //enable GPIOF
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1); //enable PWM1

    GPIOPinConfigure(GPIO_PF1_M1PWM5); //assign pin to PWM
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); //set pins as output

    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, 400); //set period to 400
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 400);

    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 100);

    PWMGenEnable(PWM1_BASE, PWM_GEN_2);
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);

    PWMOutputState(PWM1_BASE, (PWM_OUT_5_BIT | PWM_OUT_6_BIT | PWM_OUT_7_BIT), true);
    //output PWM pins

    while(1)
    {
        for(i = 40; i < 360 ; i+=5){ //increase from 10% (40) duty cycle to 90%  (360)
          ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, i); //PF1
          SysCtlDelay(100000);
        }
        for(i = 360; i > 40; i-=5 ){ //decrease from 90% (360) duty cycle to 10%  (40)
          ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, i); //PF1
          SysCtlDelay(100000);
        }

    }

}

// Ricky Perez
// CpE 403
// Lab 7
// Task 1
// Continuously display the temperature of the device (internal temperature sensor)
// on the a) hyperterminal,
// and b) GUI Composer (Temp Sensor) using a timer interrupt every 0.5 secs

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/adc.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/timer.h"
#include "driverlib/debug.h"

/////////////////////////////////////////
void PrintUART(void);
void configTimer1A(void);
void convertUARTtemp(uint32_t);
void UART_OutChar(char);
//////////////////////////////////////////

//////////////////////////////////////////
uint32_t halfPeriod;
uint32_t ui32ADC0Value[1];
volatile uint32_t ui32TempAvg;
volatile uint32_t ui32TempValueC;
volatile uint32_t ui32TempValueF;
//////////////////////////////////////////


// 1 clock cycle = 1 / SysCtlClockGet() second
// 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
// 1 second = SysCtlClockGet() / 3
// 0.001 second = 1 ms = SysCtlClockGet() / 3 / 1000
// so 0.5 seconds = SysCtkClockGet() / 3 / 2
// => 0.5 seconds = SysCtkClockGet() / (3*2)


int main(void)
{
    // set up system clock
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    // Enable the URAT0 and GPIOA peripherals
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // configure the pins for the receiver and transmitter using GPIOPinConfigure
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //enable GPIO port for LED
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); //enable pin for LED
    //  Initialize the parameters for the UART: 115200, 8-1-N
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);// enable the ADC0 peripheral

    ADCHardwareOversampleConfigure(ADC0_BASE, 32); // hardware averaging

    //configure the ADC sequencer.
    //We want to use ADC0
    //sample sequencer 1
    // we want the processor to trigger the sequence and we want to use the highest priority.
    //ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    //ADCSequenceStepConfigure(ADC0_BASE,1,3,ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE,3,0,ADC_CTL_TS|ADC_CTL_IE|ADC_CTL_END);

    halfPeriod = SysCtlClockGet() / 2 ;

    configTimer1A();

    ADCIntEnable(ADC0_BASE,3);
    ADCSequenceEnable(ADC0_BASE,3);

    while (1)
    {
    }
}
void Timer1IntHandler(void)// add to startup_ccs
{
   // halfPeriod = 0.5 * (SysCtlClockGet());
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    TimerLoadSet(TIMER1_BASE, TIMER_A, halfPeriod);
    // The indication that the ADC conversion process is complete will be the ADC interrupt status flag.
    ADCIntClear(ADC0_BASE, 3);
    // Trigger the ADC conversion with software
    ADCProcessorTrigger(ADC0_BASE, 3);
    // Wait for the conversion to complete.
    while(!ADCIntStatus(ADC0_BASE, 3, false))
    {
    }
    // When code execution exits the loop in the previous step,
    // we know that the conversion is complete and that we can read the ADC value from the ADC Sample Sequencer 1 FIFO.
    // The function we’ll be using copies data from the specified sample sequencer output FIFO to a buffer in memory.
    // The number of samples available in the hardware FIFO are copied into the buffer, which must be large enough to hold that many samples.
    // This will only return the samples that are presently available, which might not be the entire sample sequence if you attempt to access the FIFO before the conversion is complete.

    ADCSequenceDataGet(ADC0_BASE, 3, ui32ADC0Value);
    //  Calculate the average of the temperature sensor data.

    ui32TempAvg = ui32ADC0Value[0];

    // Calculate the Celsius value of the temperature.
    // TEMP = 147.5 – ((75 * (VREFP – VREFN) * ADCVALUE) / 4096)
    ui32TempValueC = (1475 - ((2475 * ui32TempAvg)) / 4096)/10;

    // The conversion from Celsius to Fahrenheit is F = ( C * 9)/5 +32.
    // Adjusting that a little gives: F = ((C * 9) + 160) / 5

    ui32TempValueF = ((ui32TempValueC * 9) + 160) / 5;

    PrintUART();
}


void configTimer1A(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, halfPeriod);
    IntEnable(INT_TIMER1A);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    TimerEnable(TIMER1_BASE, TIMER_A);

    IntMasterEnable(); //enable processor interrupts
}

void PrintUART()
{
    //UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT); //only enable RX and TX interrupts
    UARTCharPut(UART0_BASE, 'T');
    UARTCharPut(UART0_BASE, 'e');
    UARTCharPut(UART0_BASE, 'm');
    UARTCharPut(UART0_BASE, 'p');
    UARTCharPut(UART0_BASE, 'e');
    UARTCharPut(UART0_BASE, 'r');
    UARTCharPut(UART0_BASE, 't');
    UARTCharPut(UART0_BASE, 'u');
    UARTCharPut(UART0_BASE, 'r');
    UARTCharPut(UART0_BASE, 'e');
    UARTCharPut(UART0_BASE, ':');
    UARTCharPut(UART0_BASE, ' ');
    convertUARTtemp(ui32TempValueF);
    UARTCharPut(UART0_BASE, 'F');
    // linefeed
    UARTCharPut(UART0_BASE, '\n');
    // carriage-return
    UARTCharPut(UART0_BASE, '\r');

}
void convertUARTtemp(uint32_t tempF)
{
    if (tempF >= 10)
    {
        convertUARTtemp(tempF/10);
        tempF %= 10;
    }
    UART_OutChar(tempF + '0');
}

void UART_OutChar(char val)
{
    // Input: letter is an 8-bit ASCII character to be transferred
    // Output: 8-bit to serial port
    while((UART0_FR_R & UART_FR_TXFF) != 0);
    UART0_DR_R = val;
}


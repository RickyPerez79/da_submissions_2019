// Ricky Perez
// CpE 403
// Lab 9
// Task 2
// Modify the code to implement the equation: sin⁡(2π⁡*⁡50t)⁡+⁡0.5⁡*⁡cos(2π⁡*⁡200t)
// to generate a frequency of 5 Hz.
// Display the equation for 1 sec.

#include <stdint.h>
#include <stdbool.h>
#include <math.h> // this program uses sinf() so we need this library
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h" // support for Floating Point Unit
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"


// If the variable M_PI is not define when executing
// this will define it
#ifndef M_PI
#define M_PI        3.14159265358979323846  // value of Pi
#endif

#define SERIES_LENGTH 100 // depth of our data buffer
float gSeriesData[SERIES_LENGTH]; // an array of floats SERIES_LENGTH long

int32_t i32DataCount = 0;// counter

int main(void)
{
    float fRadians; // will be used to calculate sine
    float fRadians_2;
    ROM_FPULazyStackingEnable(); // turn on Lazy Stacking
    ROM_FPUEnable(); // turn on the FPU
    // set the system clock for 50MHz
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    // A full sine wave cycle is 2*pi radians.
    // Divide (2*pi) by the depth of the array.

    // 2π⁡*⁡50t; exclude "t" until loop
    fRadians = ((2 * M_PI* 50) / SERIES_LENGTH);
    // 2π⁡*⁡200; exclude "t" until loop
    fRadians_2 = ((2 * M_PI* 200) / SERIES_LENGTH);
    while(i32DataCount < SERIES_LENGTH)
     {
        // calculate the sine value for each of the 100 values
        // of the angle and place them in our data array
         //gSeriesData[i32DataCount] = sinf(fRadians * i32DataCount);

        //sin⁡(2π⁡*⁡50t)⁡+⁡0.5⁡*⁡cos(2π⁡*⁡200t)
        gSeriesData[i32DataCount] = 1.0*sinf(fRadians * i32DataCount) + (0.5*(cosf(fRadians_2 *i32DataCount)));

        i32DataCount++; // increment counter by one
    }

    while(1)
        {
        // endless loop
        }

}

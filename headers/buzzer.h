/*
 * buzzer.h
 *
 *  Created on: Mar. 30, 2021
 *      Author: Owen Cantor
 *      Version: 1.0.1
 *      Changes:
 *      1.0.1:
 *          --Added Long buzz function
*       1.0.0:
 *          --Header File Created
 */

#ifndef HEADERS_BUZZER_H_
#define HEADERS_BUZZER_H_
#include <stdint.h>
#include <SerLCD.h>
/*
 * Define EK-TM4C123GXL Register Addresses
 */

//Port A GPIO Registers
#define GPIO_PORTA_DATA_R       (*((volatile uint32_t *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile uint32_t *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile uint32_t *)0x40004420))
#define GPIO_PORTA_DR2R_R       (*((volatile uint32_t *)0x40004500))
#define GPIO_PORTA_PDR_R        (*((volatile uint32_t *)0x40004514))
#define GPIO_PORTA_DEN_R        (*((volatile uint32_t *)0x4000451C))

//System Control Registers
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))

/*
 * GPIO Port Initialization
 */

void buzzerInit(){
    /*
     * Initialize GPIO Port A (PA6) to be digital output pin
     */

    //Enable Clock to Port A
    SYSCTL_RCGCGPIO_R |= 0x01;
    //Set PA6 Output pin
    GPIO_PORTA_DIR_R |= 0x40;
    //Set GPIOAFSEL for Port A to 0 to select GPIO Function
    GPIO_PORTA_AFSEL_R |= 0x00;
    //Set pin PA6 to Use 2mA Drive
    GPIO_PORTA_DR2R_R |= 0x40;
    //Set PullDown resistor for output
    GPIO_PORTA_PDR_R |= 0x40;
    //Set Digital I/O
    GPIO_PORTA_DEN_R |= 0x40;
}

/*
 * Time Function
 */

void tDelay_us(int us)
{
    int i,j;
    for(i=0;i<us;i++)
    for(j=0;j<3;j++)
    {}

}

/*
 * Buzzer Functions
 */

void buzz(){
    /*
     * Buzz for one period, must be looped externally to generate a tone.
     */
    GPIO_PORTA_DATA_R = 0x40;
    tDelay_us(1135);
    GPIO_PORTA_DATA_R = 0x00;
    tDelay_us(1135);
    return;
}

/*
 * This is the Buzz function in a loop
 */
void longBuzz(){
    int count = 0;
    while(count < 10)
    {
        buzz();
        tDelay(5);
        count++;
    }
}
#endif /* HEADERS_BUZZER_H_ */

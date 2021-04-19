/*
 * LightSensor.h
 *
 *  Created on: Apr. 6, 2021
 *      Author: Jared Riepert
 *      Version 1.0.2
 *      Changes:
 *       1.0.2:
 *          --Added more comments
 *       1.0.1:
 *          --Added Scan Function
 *       1.0.0:
 *           --Header Created
 */

#ifndef LIGHTSENSOR_H_
#define LIGHTSENSOR_H_

#include <motor.h>
#include <SerLCD.h>

/*
 * Define EK-TM4C123GXL Register Addresses
 */
//System Control Registers
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))
#define SYSCTL_RCGCADC_R        (*((volatile uint32_t *)0x400FE638))

//PORTE addresses
#define GPIO_PORTE_ADCCTL_R     (*((volatile uint32_t *)0x40024530))
#define GPIO_PORTE_AFSEL_R      (*((volatile uint32_t *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile uint32_t *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile uint32_t *)0x40024528))

//ADC0 Addresses
#define ADC0_SSFIFO3_R          (*((volatile uint32_t *)0x400380A8))
#define ADC0_RIS_R              (*((volatile uint32_t *)0x40038004))
#define ADC0_PSSI_R             (*((volatile uint32_t *)0x40038028))
#define ADC0_ISC_R              (*((volatile uint32_t *)0x4003800C))
#define ADC0_ACTSS_R            (*((volatile uint32_t *)0x40038000))
#define ADC0_EMUX_R             (*((volatile uint32_t *)0x40038014))
#define ADC0_SSMUX3_R           (*((volatile uint32_t *)0x400380A0))
#define ADC0_SSCTL3_R           (*((volatile uint32_t *)0x400380A4))
#define ADC0_ACTSS_R            (*((volatile uint32_t *)0x40038000))

#include <stdint.h>

/*
 * GPIO Port Initialization
 */
void LightInit(){
    /* Must be done first */
    GPIO_PORTE_ADCCTL_R |= 20;      //set PE5 to ADC

    /* Enable Clock to ADC0 and GPIO pins*/
    SYSCTL_RCGCGPIO_R |= (1<<6);   /* Enable Clock to GPIOE or PE5/AIN8 */
    SYSCTL_RCGCADC_R |= (1<<0);    /* AD0 clock enable*/

        /* initialize PE5 for AIN8 input  */
    GPIO_PORTE_AFSEL_R |= (1<<5);       /* enable alternate function */
    GPIO_PORTE_DEN_R &= ~(1<<5);        /* disable digital function */
    GPIO_PORTE_AMSEL_R |= (1<<5);       /* enable analog function */

        /* initialize sample sequencer3 */
    ADC0_ACTSS_R &= ~(1<<3);        /* disable SS3 during configuration */
    ADC0_EMUX_R &= ~0xF000;    /* software trigger conversion */
    ADC0_SSMUX3_R = 8;         /* get input from channel 0 */
    ADC0_SSCTL3_R |= (1<<1)|(1<<2);        /* take one sample at a time, set flag at 1st sample */
    ADC0_ACTSS_R |= (1<<3);         /* enable ADC0 sequencer 3 */

}

/*
 * Read Light Value Function
 */
unsigned int ReadLight(){
    /*
     * Reads the current value of the Light Sensor
     * Returns an unsigned int value between 0 and 4096
     * 0 being in a black hole and 4096 being inside the Sun
     */

    ADC0_ISC_R = 8;          /* clear coversion clear flag bit*/
    ADC0_PSSI_R |= (1<<3);        /* Enable SS3 conversion or start sampling data from AN0 */
    while((ADC0_RIS_R & 8) == 0) ;   /* Wait untill sample conversion completed*/
    return ADC0_SSFIFO3_R; /* read adc coversion result from SS3 FIFO*/
}

/*
 * Gets Light Voltage Level
 */
float GetLightVoltage(){
    /*
     * This function will return the voltage readings of
     * the light sensor
     */

    return (ReadLight() * 0.0008);
}

/*
 * This function will scane the entire range looking for the brightest light source
 * Once the brightest light source has been found it will sit at the location
 */
void scan()
{
    //tell the user it is looking
    LCD_Clear();
    LCD_SendStr("Searching...");
    tDelay(50);
    //reset panel to starting spot
    goToZero();
    //needed variables
    int angle = getAngle();
    float topValue = 0;
    float currentValue = 0;
    int topValueAngle = 0;

 //1 clockwise, 2 counter clockwise
    //start by moving clockwise, read after every move and check to see if that
    //value is the biggest value seen
    int direction = 1;
    if(direction == 1)
     {
        //while in range move clockwise
        while(angle<range)
        {
             currentValue = ReadLight();
             tDelay(1);
             if(currentValue > topValue)
             {
                 topValue = currentValue;
                 topValueAngle = angle;
             }
             stepCW();
             tDelay(3);
             angle++;
         }
         direction = 2;
     }
    //now move counter clockwise all the way to the other limit seeing if any bigger 
    //values are over there
    if(direction == 2)
     {
        //while in range
         while(angle>0)
         {
             currentValue = ReadLight();
             tDelay(1);
              if(currentValue > topValue)
              {
                  topValue = currentValue;
                  topValueAngle = angle;
              }
             stepCCW();
             tDelay(3);
             angle--;
         }
         direction = 1;
     }
    //now that all angles have been checked return to the position that had
    //the greatest value recorded
    while(angle<topValueAngle)
    {
        stepCW();
        tDelay(3);
        angle++;
    }
    while(angle>topValueAngle)
    {
        stepCCW();
        tDelay(3);
        angle--;
    }
    //stop at the location with the greatest value and tell the user you
    //found the best spot and the value at that spot
    LCD_Clear();
    LCD_SetCurPos(0,0);
    LCD_SendStr("Found Light!");
    tDelay(50);
    LCD_SetCurPos(1,0);
    LCD_SendStr("Value = ");
    LCD_SendFloat(topValue);
    updateAngle(angle);
}
#endif /* LIGHTSENSOR_H_ */

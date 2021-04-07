/*
 * KeyPad.h
 *
 *  Created on: Apr. 6, 2021
 *      Author: Jared Riepert
 *      Version 1.0.0
 *      Changes:
 *       1.0.0:
 *           --Header Created
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include <stdint.h>

/*
 * Define EK-TM4C123GXL Register Addresses
 */
//System Control Registers
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))
//PORTE and PORTC
#define GPIO_PORTC_CR_R         (*((volatile uint32_t *)0x40006524))
#define GPIO_PORTE_CR_R         (*((volatile uint32_t *)0x40024524))
#define GPIO_PORTE_DIR_R        (*((volatile uint32_t *)0x40024400))
#define GPIO_PORTC_DIR_R        (*((volatile uint32_t *)0x40006400))
#define GPIO_PORTE_PDR_R        (*((volatile uint32_t *)0x40024514))
#define GPIO_PORTC_DEN_R        (*((volatile uint32_t *)0x4000651C))
#define GPIO_PORTE_DEN_R        (*((volatile uint32_t *)0x4002451C))
#define GPIO_PORTC_DATA_R       (*((volatile uint32_t *)0x400063FC))
#define GPIO_PORTE_DATA_R       (*((volatile uint32_t *)0x400243FC))

/*
 * Keypad symbol layout
 */
//#define row 4
//#define column 3
unsigned char symbol[4][3]= {{'1','2','3'},
                                    {'4','5','6'},
                                    {'7','8','9'},
                                    {'*','0','#'}};
/*
 * GPIO Port Initialization
 */
void KeypadInit(void)
{
    SYSCTL_RCGCGPIO_R |= 0x14;        //Enable clock to PORTC and PORTE
    while ((SYSCTL_RCGCGPIO_R&0x14)==0);  //wait for clock to be setted
    GPIO_PORTC_CR_R  |= 0xE0;             //Allow settings for all pins of PORTC
    GPIO_PORTE_CR_R  |= 0x0F;             //Allow settings for all pins of PORTE
    GPIO_PORTE_DIR_R |= 0x00;             //PE0-PE3 are used with row and set them as digital input pins
    GPIO_PORTC_DIR_R |= 0xE0;             //5,6,7 PORTC output
    GPIO_PORTE_PDR_R |= 0x0F;             //Enable pull down resistor on PORTE
    GPIO_PORTC_DEN_R |= 0xE0;             //Set PORTC as digital pins
    GPIO_PORTE_DEN_R |= 0x0F;             //Set PORTE as digital pins
}

/*
 * Time Function
 */
void delay_us(int n)
{
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3;j++)
 {}

}

/*
 * Get Key Pressed Function
 */
char Keypad_getkey(void)
{
    /*
     * Get the value of a key pressed on the keypad
     * function will wait forever until key is pressed
     */

    int i,j;
    //look until key is pressed
    while(1)
    {
        //search each column
        for(i = 0; i < 3; i++)
        {
            //select the column to look going from PORTC 5,6,7
            GPIO_PORTC_DATA_R = (1U << i+5);
            delay_us(2);
            //search each row
            for(j = 0; j < 4; j++)
            {
                //check for high signal from each row
                if((GPIO_PORTE_DATA_R & 0x0F) & (1U << j))
                {
                    //if high signal found then key was pressed
                    //search up the button pressed by looking in the symbol matrix with the row (j) and column (i) values
                    return symbol[j][i];
                }
            }
        }
    }
}


#endif /* KEYPAD_H_ */

/*
 * Bluetooth.h
 *
 *  Created on: Apr. 6, 2021
 *      Author: Jared Riepert
 *      Version 1.0.0
 *      Changes:
 *       1.0.0:
 *           --Header Created
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_
#include <stdint.h>

/*
 * Define EK-TM4C123GXL Register Addresses
 */
#define SYSCTL_RCGCUART_R       (*((volatile uint32_t *)0x400FE618))
#define SYSCTL_RCGCGPIO_R5      0x00000020  // GPIO Port F Run Mode Clock
                                            // Gating Control
// UART2 Addresses
#define UART2_CTL_R             (*((volatile uint32_t *)0x4000E030))
#define UART2_IBRD_R            (*((volatile uint32_t *)0x4000E024))
#define UART2_FBRD_R            (*((volatile uint32_t *)0x4000E028))
#define UART2_CC_R              (*((volatile uint32_t *)0x4000EFC8))
#define UART2_LCRH_R            (*((volatile uint32_t *)0x4000E02C))
#define UART2_CTL_R             (*((volatile uint32_t *)0x4000E030))
#define UART2_FR_R              (*((volatile uint32_t *)0x4000E018))
#define UART2_DR_R              (*((volatile uint32_t *)0x4000E000))

//PORTD Addresses
#define GPIO_PORTD_DEN_R        (*((volatile uint32_t *)0x4000751C))
#define GPIO_PORTD_AFSEL_R      (*((volatile uint32_t *)0x40007420))
#define GPIO_PORTD_AMSEL_R      (*((volatile uint32_t *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile uint32_t *)0x4000752C))

/*
 * GPIO Port Initialization
 */
void BluetoothInit(void)
{
    SYSCTL_RCGCUART_R |= 0x4;  /* enable clock to UART2 */
    SYSCTL_RCGCGPIO_R |= 0x8;  /* enable clock to PORTE for PD6/Rx and PD7/Tx */
        delay_us(1);
        /* UART2 initialization */
        UART2_CTL_R = 0x00;         /* UART2 module disable */
        UART2_IBRD_R = 0x68;      /* for 9600 baud rate, integer = 104 */
        UART2_FBRD_R =0xb;       /* for 9600 baud rate, fractional = 11*/
        UART2_CC_R =0x0;          /*select system clock*/
        UART2_LCRH_R = 0x60;     /* data length 8-bit, not parity bit, no FIFO */
        UART2_CTL_R = 0x301;     /* Enable UART2 module, Rx and Tx */

        /* UART2 TX2 and RX2 use PD6 and PD7. Configure them digital and enable alternate function */
        GPIO_PORTD_DEN_R = 0xC0;      /* set PD6 and PD7 as digital */
        GPIO_PORTD_AFSEL_R = 0xC0;    /* Use PD6,PD7 alternate function */
        GPIO_PORTD_AMSEL_R = 0;    /* Turn off analog function*/
        GPIO_PORTD_PCTL_R = 0x11000000;     /* configure PD6 and PD7 for UART */
}

/*
 * Read Bluetooth Value Function
 */
char Bluetooth_Read(void)
{
    /*
     * This function will listen for a new input from Bluetooth
     * and return it as a char
     */

    char data;
      while((UART2_FR_R & (1<<4)) != 0); /* wait until Rx buffer is not full */
    data = UART2_DR_R ;      /* before giving it another byte */
    return (unsigned char) data;
}

#endif /* BLUETOOTH_H_ */

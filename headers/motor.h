/*
 * motor.h
 *
 *  Created on: Mar. 29, 2021
 *      Author: Owen Cantor
 *      Version 1.0.1
 *      Changes:
 *      1.0.1:
 *          --Fixed error in comments that referred to Port F instead of Port A
*       1.0.0:
*           --Header Created
 */

#ifndef HEADERS_MOTOR_H_
#define HEADERS_MOTOR_H_
#include <stdint.h>
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

void motorInit(){
    /*
     * Initialize GPIO Port A (PA2 -> PA5) to be digital output pins
     */

    //Enable Clock to Port A
    SYSCTL_RCGCGPIO_R |= 0x01;
    //Set PA2 -> PA5 Output pins
    GPIO_PORTA_DIR_R |= 0x3C;
    //Set GPIOAFSEL for Port A to 0 to select GPIO Function
    GPIO_PORTA_AFSEL_R |= 0x00;
    //Set pins PA2 -> PA5 to Use 2mA Drive
    GPIO_PORTA_DR2R_R = 0x3C;
    //Set PullUp resistors for output
    GPIO_PORTA_PDR_R |= 0x3C;
    //Set Digital I/O
    GPIO_PORTA_DEN_R |= 0x3C;

}

/*
 * Stepper Motor Functions
 */

void stepCW(){
    /*
     * Rotate the motor to its next clockwise position.
     *
     * If being implemented in a loop, should be paired
     * with delay time in between
     * position changes.
     * (10ms is a crawl, 1ms is semi fast)
     */
    uint32_t curPos = GPIO_PORTA_DATA_R;
    switch (curPos){
        case 0x24:
            GPIO_PORTA_DATA_R = 0x30;
            break;
        case 0x30:
            GPIO_PORTA_DATA_R = 0x18;
            break;
        case 0x18:
            GPIO_PORTA_DATA_R = 0x0C;
            break;
        case 0x0C:
            GPIO_PORTA_DATA_R = 0x24;
            break;
        default:
            GPIO_PORTA_DATA_R = 0x24;
    }
}

void stepCCW(){
    /*
     * Rotate the motor to its next counter-clockwise position.
     *
     * If being implemented in a loop, should be paired
     * with delay time in between
     * position changes.
     * (10ms is a crawl, 1ms is semi fast)
     */
    uint32_t curPos = GPIO_PORTA_DATA_R;
    switch (curPos){
    case 0x0C:
        GPIO_PORTA_DATA_R = 0x18;
        break;
    case 0x18:
        GPIO_PORTA_DATA_R = 0x30;
        break;
    case 0x30:
        GPIO_PORTA_DATA_R = 0x24;
        break;
    case 0x24:
        GPIO_PORTA_DATA_R = 0x0C;
        break;
    default:
        GPIO_PORTA_DATA_R = 0x0C;

    }
}


#endif /* HEADERS_MOTOR_H_ */

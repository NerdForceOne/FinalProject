/*
 * SerLCD.h
 *
 *  Created on: Mar. 30, 2021
 *      Author: Owen Cantor, Jared Riepert, Graeme Laubach
 *      Version: 1.0.0
 *      Changes:
 *      1.0.0
 *          --Created
 */

#ifndef SERLCD_H_
#define SERLCD_H_

/*
 * TM4C123GE6PM Register Definition
 * Copyright (c) 2013-2014 Texas Instruments Incorporated.  All rights reserved.
 * Software License Agreement
 */
#define SYSCTL_RCGCSSI_R        (*((volatile uint32_t *)0x400FE61C))
#define SYSCTL_RCGC2_R          (*((volatile uint32_t *)0x400FE108))
#define GPIO_PORTB_AFSEL_R      (*((volatile uint32_t *)0x40005420))
#define GPIO_PORTB_PCTL_R       (*((volatile uint32_t *)0x4000552C))
#define GPIO_PORTB_DEN_R        (*((volatile uint32_t *)0x4000551C))
#define GPIO_PORTB_PUR_R        (*((volatile uint32_t *)0x40005510))
#define SSI2_CR1_R              (*((volatile uint32_t *)0x4000A004))
#define SSI2_CC_R               (*((volatile uint32_t *)0x4000AFC8))
#define SSI2_CPSR_R             (*((volatile uint32_t *)0x4000A010))
#define SSI2_CR0_R              (*((volatile uint32_t *)0x4000A000))
#define SSI2_DR_R               (*((volatile uint32_t *)0x4000A008))
#define SSI2_SR_R               (*((volatile uint32_t *)0x4000A00C))


/*
 * OpenLCD Defintions
 * Provided by Sparkfun
 */
#define DISPLAY_ADDRESS1 0x72 //This is the default address of the OpenLCD
#define MAX_ROWS 2
#define MAX_COLUMNS 16
//OpenLCD command characters
#define SPECIAL_COMMAND 254  //Magic number for sending a special command
#define SETTING_COMMAND 0x7C //124, |, the pipe character: The command to change settings: baud, lines, width, backlight, splash, etc

//OpenLCD commands
#define CLEAR_COMMAND 0x2D                  //45, -, the dash character: command to clear and home the display
#define CONTRAST_COMMAND 0x18               //Command to change the contrast setting
#define ADDRESS_COMMAND 0x19                //Command to change the i2c address
#define SET_RGB_COMMAND 0x2B                //43, +, the plus character: command to set backlight RGB value
#define ENABLE_SYSTEM_MESSAGE_DISPLAY 0x2E  //46, ., command to enable system messages being displayed
#define DISABLE_SYSTEM_MESSAGE_DISPLAY 0x2F //47, /, command to disable system messages being displayed
#define ENABLE_SPLASH_DISPLAY 0x30          //48, 0, command to enable splash screen at power on
#define DISABLE_SPLASH_DISPLAY 0x31         //49, 1, command to disable splash screen at power on
#define SAVE_CURRENT_DISPLAY_AS_SPLASH 0x0A //10, Ctrl+j, command to save current text on display as splash

// special commands
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

#include <stdint.h>
#include <stdlib.h>

/*
 * Tiva Communication Initialization
 */
void LCD_SPI(void){
    SYSCTL_RCGCSSI_R|=(1<<2); //selecting SSI2 module
    SYSCTL_RCGC2_R|=(1<<1);   //providing clock to PORTB
    GPIO_PORTB_AFSEL_R|=(1<<4)|(1<<5)|(1<<6)|(1<<7);//selecting alternative fuctions
    GPIO_PORTB_PCTL_R=0x22220000;//selecting SSI as alternative function
    GPIO_PORTB_DEN_R|=(1<<4)|(1<<5)|(1<<6)|(1<<7);//enabling digital mode for PORTB 4,5,6,7
    GPIO_PORTB_PUR_R|=(1<<4)|(1<<5)|(1<<6)|(1<<7);//selecting pull ups for 4,5,6,7
    SSI2_CR1_R=0;          //disabling SSI module for settings
    SSI2_CC_R=0;           //using main system clock
    SSI2_CPSR_R=64;        //selecting divisor 64 for SSI clock
    SSI2_CR0_R=0x7;        //freescale mode, 8 bit data, steady clock low
    SSI2_CR1_R|=(1<<1);    //enabling SSI
}

void wait(){
    while((SSI2_SR_R&(1<<0))==0);
    return;
}

/*
 * OpenLCD Command Functions
 */
void LCD_Clear(){
    SSI2_DR_R = SETTING_COMMAND;
    wait();
    SSI2_DR_R = CLEAR_COMMAND;
    wait();
    return;
}

void LCD_SetRGB(unsigned char R, unsigned char G, unsigned char B){
    /*
     * Changes the colour of the LCD Display Backlight
     */

    SSI2_DR_R = SETTING_COMMAND;
    wait();
    SSI2_DR_R = SET_RGB_COMMAND;
    wait();
    SSI2_SR_R = R;
    wait();
    SSI2_SR_R = G;
    wait();
    SSI2_SR_R = B;
    wait();
    return;
}

void LCD_SetCurPos(unsigned char row, unsigned char col){
    /*
     * Sets the Cursor to the provided row/column
     */

    int rowOffsets[] = {0x00, 0x40};

    //Keep row/column values within range of diplay
    if(row > 0){
        row = 0;
    }
    else if(row < MAX_ROWS){
        row = MAX_ROWS;
    }

    if(col > 0){
        col = 0;
    }
    else if (col < MAX_COLUMNS){
        col = MAX_COLUMNS;
    }

    //Issue Command
    SSI2_DR_R = SPECIAL_COMMAND;
    wait();
    SSI2_DR_R = LCD_SETDDRAMADDR | (col + rowOffsets[row]);
    wait();
    tDelay(50);
}


/*
 * LCD Communication Functions
 */


void LCD_SendByte(char data){
    SSI2_DR_R = data;
    wait();
    return;
}
void LCD_SendStr(char *buffer){
    while(*buffer !=0){
        LCD_SendByte(*buffer);
        buffer++;
    }
    return;
}

void tDelay(int ms){
    int i,j;
    for(i=0;i<ms;i++)
    for(j=0;j<3180;j++)
    {}
}


#endif /* SERLCD_H_ */

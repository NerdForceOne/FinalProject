
#include <SerLCD.h>
#include <buzzer.h>
#include <motor.h>
#include <LightSensor.h>
#include <KeyPad.h>
#include <Bluetooth.h>
#include <menu.h>
#include <Tracking.h>
#include <stdbool.h>

/**
 * main.c
 */

void main(void)
{
    //Component initialization
    LCD_SPI();
    KeypadInit();
    buzzerInit();
    motorInit();
    LightInit();
    BluetoothInit();

    //LCD setup
    LCD_Clear();
    LCD_SetRGB(255,255,255);
    tDelay(300);
    checkInput('*');

    while(1)
    {
        bool iftrack = false;
        char key = Keypad_getkey();
        if(key == '|')
        {
            key = Bluetooth_Read();
        }
        if(key == '*')
        {
                setTracking(false);
                iftrack = false;
        }
        checkInput(key);

        if(getTracking()==true)
        {
            iftrack = true;
            track();
            tDelay(1000);
        }
    }

}

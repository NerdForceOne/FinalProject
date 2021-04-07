
#include <SerLCD.h>
#include <buzzer.h>
#include <motor.h>
#include <LightSensor.h>
#include <KeyPad.h>
#include <Bluetooth.h>

/**
 * main.c
 */
int main(void)
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


    while(1)
    {
        float voltage = GetLightVoltage();
        LCD_SetCurPos(0,0);
        LCD_SendStr("ADC0= ");
        LCD_SetCurPos(1,0);
        LCD_SendStr("ADC1= ");

        LCD_SetCurPos(0,6);
        LCD_SendFloat(voltage);
        LCD_SetCurPos(1,6);
        LCD_SendFloat(voltage+1);
        tDelay(600);
    }

	return 0;
}

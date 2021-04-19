/*
 * Tracking.h
 *
 *  Created on: Apr. 18, 2021
 *      Author: Jared
 *      Version 1.0.0
 *      Changes:
 *       1.0.0:
 *           --Header Created
 */

#ifndef TRACKING_H_
#define TRACKING_H_

#include <LightSensor.h>
#include <motor.h>
#include <stdbool.h>

//global variable to see if tracking is turned on
bool trackingIsOn = false;

//get the value of is tracking
bool getTracking()
{
    return trackingIsOn;
}
//set the value of is tracking
void setTracking(bool status)
{
    trackingIsOn = status;
}

/*
 * This function will follow the brightest lights source
 * you just need to call this once for it to do a single check
 * pair this function in a loop with a delay (1 second is nice)
 * to have it always looking for the light
 */
void track()
{
    //print to the screen it is now tracking
    LCD_Clear();
    LCD_SendStr("Tracking!");
    LCD_SetCurPos(1,0);
    LCD_SendStr("Hold '*' to stop");

    //variables needed 
    int currentRead = ReadLight();
    int lastRead = 0;
    int count = 0;
    int angle = getAngle();
    //take a reading and then move a little bit clockwise and check
    //if the light value there is greater or not from before
    do{
        lastRead = currentRead;
        count = 0;
    while(count < 25 && angle < range)
    {
        stepCW();
        tDelay(3);
        angle++;
        count++;
    }
    currentRead = ReadLight();
    //if the value is greater here then from before then repeat the same process
    //to see if the next spot is also better
    }while(currentRead > lastRead);

    //if moving clockwise did not make the light value bigger then try moving counter clockwise 
    do{
        lastRead = currentRead;
        count = 0;
        while(count < 25 && angle > 0)
        {
            stepCCW();
            tDelay(3);
            angle--;
            count++;
        }
        currentRead = ReadLight();
        //if moving counter clockwise got a bigger reading then do it again
        }while(currentRead > lastRead);
    //if no more directions made a bigger value then stop at the current location
    //and make note of the angle you are at
    updateAngle(angle);
}

#endif /* TRACKING_H_ */

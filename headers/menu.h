/*
 * menu.h
 *
 *  Created on: Apr. 15, 2021
 *      Author: Jared
 *      Version 1.0.1
 *      Changes:
 *       1.0.1:
 *          --Updated Comments and fixed menu selection bug
 *       1.0.0:
 *           --Header Created
 */
#ifndef MENU_H_
#define MENU_H_

//Includes
#include <SerLCD.h>
#include <motor.h>
#include <LightSensor.h>

//Defines
/*
 * The below diagram shows a visual of how the menu system works
 * If you want to add an action to the menu you must add the action number
 * to the switch case in the 'LoadMenu' function, and add what happens there
 *
 * A max of 10 items can be within a menu section, otherwise the system
 * will be calling multiple selections at a time
 *
 * Main Menu           menu1    Action
 * [choice 1 {0.1}] -> [1.1] -> [11] {can have an action done here}
 *                     [1.2] -> [12] {something else here}
 *                     [1.3] -> [13] {all of these places can have something different}
 *                     menu2
 * [choice 2 {0.2}] -> [2.1] -> [21] {anything can be triggered to happen}
 *                     [2.2] -> [22] {you have lots of choices}
 *                     [2.3] -> [23] {I think you understand how this works}
 *                     [2.4] -> [24]
 *                     menu3
 * [choice 3 {0.3}] -> [3.1] -> [31]
 *                     [3.2] -> [32]
 *                     menu4
 * [choice 4 {0.4}] -> [4.1] -> [41]
 *                     [4.2] -> [42]
 *                     [4.3] -> [43]
 *                     [4.4] -> [44]
 *                     [4.5] -> [45]
 *                     menux
 * [choice x {0.x}] -> [x.1] -> [x1]
 *                     [x.2] -> [x2]
 *                     [x.3] -> [x3]
 *                     [x.4] -> [x4]
 *                     [x.5] -> [x5]
 *                     [x.6] -> [x6]
 *                     [x.7] -> [x7]
 *                     [x.8] -> [x8]
 *                     [x.9] -> [x9]
 *                     [x.10] -> [(x+1)0]
 *
 * This is the Main Menu array format
 * if the number of rows change then make sure
 * to update the row count define
 */
#define mainMenuRows 3
char* mainMenu[mainMenuRows]=  {{"Motor Controls"},
                                {"Light Tracking"},
                                {"something"}};
/*
 * This is the Menu 1 array format
 * if the number of rows change then make sure
 * to update the row count define
 */
#define menu1Rows 3
char* menu1[menu1Rows] = {{"Go To 0"},
                          {"Go Far Left"},
                          {"Go Far Right"}};
/*
 * This is the Menu 2 array format
 * if the number of rows change then make sure
 * to update the row count define
 */
#define menu2Rows 4
char* menu2[menu2Rows] = {{"Scan"},
                          {"Read Value"},
                          {"--1--"},
                          {"--2--"}};
/*
 * This is the Menu 3 array format
 * if the number of rows change then make sure
 * to update the row count define
 */
#define menu3Rows 2
char* menu3[menu3Rows] = {{"menu3 1"},
                          {"menu3 2"}};
/*
 * This is the Menu 4 array format
 * if the number of rows change then make sure
 * to update the row count define
 */
#define menu4Rows 5
char* menu4[menu4Rows] = {{"menu4 1"},
                          {"menu4 2"},
                          {"menu4 3"},
                          {"menu4 4"},
                          {"menu4 5"}};


//Functions
/*
 * This function loads the Main Menu
 * You will never directly call this function
 */
void LoadMainMenu(int *row)
{
    //This function will receive a row value to go to, if the value does not exist then loop back around to where it does
    //if the row is past the maximum ones then go to the first row (row = 0)
    if(*row > mainMenuRows-1){
        *row = 0;
    //if the row is below the first row (row = 0) then goto the last row
    }else if(*row < 0)
    {
        *row = mainMenuRows-1;
    }
    //check if the row is on the first or second LCD line
    int posistion = *row % 2;
    //reset the screen first
        LCD_Clear();
    //go to the correct LCD line and print the arrow
        LCD_SetCurPos(posistion,0);
        LCD_SendStr("->");
    //small delay
        tDelay(8);
    //Check to see which line the arrow is on
        if(posistion == 1)
        {
            //if the second line then go back to the first line and print the menu option above the currently selected one
            LCD_SetCurPos(0,0);
            if(*row > 0){
                LCD_SendStr(mainMenu[*row-1]);
            }else{
                //if out of range then loop around
                LCD_SendStr(mainMenu[mainMenuRows-1]);
            }
        }else{
            //if on the first LCD line then print the current menu item after the arrow
            LCD_SendStr(mainMenu[*row]);
        }
    //small delay
        tDelay(15);
    //now move to the second line of the LCD
        LCD_SetCurPos(1,0);
    //check to see which line the arrow is on
        if(posistion == 1)
        {
            //if the second line then print the current menu item after the arrow
            LCD_SetCurPos(1,2);
            LCD_SendStr(mainMenu[*row]);
        }else{
            //if on the first LCD line then print the next menu item on the second line
            if(*row < mainMenuRows-1)
            {
                LCD_SendStr(mainMenu[*row+1]);
            }else{
                //if out of range then loop around
                LCD_SendStr(mainMenu[0]);
            }
        }
        //small delay
        tDelay(50);
}
/*
 * This function loads the Menu for the first item on the Main Menu
 * You will never directly call this function
 * Refer to the Main Menu function for comments, the code is the same besides variable names
 */
void LoadMenu1(int *row)
{
    if(*row > menu1Rows-1){
            *row = 0;
        }else if(*row < 0)
        {
            *row = menu1Rows-1;
        }
    int posistion = *row % 2;
            LCD_Clear();
            LCD_SetCurPos(posistion,0);
            LCD_SendStr("->");
            tDelay(8);
            if(posistion == 1)
            {
                LCD_SetCurPos(0,0);
                if(*row > 0){
                    LCD_SendStr(menu1[*row-1]);
                }else{
                    LCD_SendStr(menu1[menu1Rows-1]);
                }
            }else{
                LCD_SendStr(menu1[*row]);
            }
            tDelay(15);
            LCD_SetCurPos(1,0);
            if(posistion == 1)
            {
                LCD_SetCurPos(1,2);
                LCD_SendStr(menu1[*row]);
            }else{
                if(*row < menu1Rows-1)
                {
                    LCD_SendStr(menu1[*row+1]);
                }else{
                    LCD_SendStr(menu1[0]);
                }
            }
            tDelay(50);
}
/*
 * This function loads the Menu for the second item on the Main Menu
 * You will never directly call this function
 * Refer to the Main Menu function for comments, the code is the same besides variable names
 */
void LoadMenu2(int *row)
{
    if(*row > menu2Rows-1){
                *row = 0;
            }else if(*row < 0)
            {
                *row = menu2Rows-1;
            }
        int posistion = *row % 2;
                LCD_Clear();
                LCD_SetCurPos(posistion,0);
                LCD_SendStr("->");
                tDelay(8);
                if(posistion == 1)
                {
                    LCD_SetCurPos(0,0);
                    if(*row > 0){
                        LCD_SendStr(menu2[*row-1]);
                    }else{
                        LCD_SendStr(menu2[menu2Rows-1]);
                    }
                }else{
                    LCD_SendStr(menu2[*row]);
                }
                tDelay(15);
                LCD_SetCurPos(1,0);
                if(posistion == 1)
                {
                    LCD_SetCurPos(1,2);
                    LCD_SendStr(menu2[*row]);
                }else{
                    if(*row < menu2Rows-1)
                    {
                        LCD_SendStr(menu2[*row+1]);
                    }else{
                        LCD_SendStr(menu2[0]);
                    }
                }
                tDelay(50);
}
/*
 * This function loads the Menu for the third item on the Main Menu
 * You will never directly call this function
 * Refer to the Main Menu function for comments, the code is the same besides variable names
 */
void LoadMenu3(int *row)
{
    if(*row > menu3Rows-1){
                    *row = 0;
                }else if(*row < 0)
                {
                    *row = menu3Rows-1;
                }
            int posistion = *row % 2;
                    LCD_Clear();
                    LCD_SetCurPos(posistion,0);
                    LCD_SendStr("->");
                    tDelay(8);
                    if(posistion == 1)
                    {
                        LCD_SetCurPos(0,0);
                        if(*row > 0){
                            LCD_SendStr(menu3[*row-1]);
                        }else{
                            LCD_SendStr(menu3[menu3Rows-1]);
                        }
                    }else{
                        LCD_SendStr(menu3[*row]);
                    }
                    tDelay(15);
                    LCD_SetCurPos(1,0);
                    if(posistion == 1)
                    {
                        LCD_SetCurPos(1,2);
                        LCD_SendStr(menu3[*row]);
                    }else{
                        if(*row < menu3Rows-1)
                        {
                            LCD_SendStr(menu3[*row+1]);
                        }else{
                            LCD_SendStr(menu3[0]);
                        }
                    }
                    tDelay(50);
}
/*
 * This function loads the Menu for the fourth item on the Main Menu
 * You will never directly call this function
 * Refer to the Main Menu function for comments, the code is the same besides variable names
 */
void LoadMenu4(int *row)
{
    if(*row > menu4Rows-1){
                        *row = 0;
                    }else if(*row < 0)
                    {
                        *row = menu4Rows-1;
                    }
                int posistion = *row % 2;
                        LCD_Clear();
                        LCD_SetCurPos(posistion,0);
                        LCD_SendStr("->");
                        tDelay(8);
                        if(posistion == 1)
                        {
                            LCD_SetCurPos(0,0);
                            if(*row > 0){
                                LCD_SendStr(menu4[*row-1]);
                            }else{
                                LCD_SendStr(menu4[menu4Rows-1]);
                            }
                        }else{
                            LCD_SendStr(menu4[*row]);
                        }
                        tDelay(15);
                        LCD_SetCurPos(1,0);
                        if(posistion == 1)
                        {
                            LCD_SetCurPos(1,2);
                            LCD_SendStr(menu4[*row]);
                        }else{
                            if(*row < menu4Rows-1)
                            {
                                LCD_SendStr(menu4[*row+1]);
                            }else{
                                LCD_SendStr(menu4[0]);
                            }
                        }
                        tDelay(50);
}
/*
 * This function is called to load the LCD
 * Call this function with a row and menu number
 * and it will select the correct menu to print
 *
 * MORE MENUS CAN BE ADDED!!
 * A Load function must be made for it and the array format with specified row count defined
 * Then add a case here that calls the function
 * Follow any of the other menus as a guide line
 */
void LoadLCD(int *row,int *menu)
{
    int loop = 1;
    while(loop)
    {
    switch(*menu){
    case 0:
        LoadMainMenu(&*row);
        loop = 0;
        break;
    case 1:
        LoadMenu1(&*row);
        loop = 0;
        break;
    case 2:
        LoadMenu2(&*row);
        loop = 0;
        break;
    case 3:
        LoadMenu3(&*row);
        loop = 0;
        break;
    case 4:
        LoadMenu4(&*row);
        loop = 0;
        break;
    case 11:
        goToZero();
        loop = 0;
        *menu = 0;
        break;
    case 12:
        goFarLeft();
        loop = 0;
        *menu = 0;
        break;
    case 13:
        goFarRight();
        loop = 0;
        *menu = 0;
        break;
    case 21:
        scan();
        loop = 0;
        *menu = 0;
        break;
    case 22:
        LCD_Clear();
        LCD_SendStr("Value = ");
        LCD_SendFloat((float)ReadLight());
        tDelay(1000);
        loop = 0;
        *menu = 0;
        break;
    default:
        //your selection doesn't exist yet
        //go back to main menu
        LCD_Clear();
        LCD_SendStr("Nothing at menu ");
        LCD_SendFloat((float)*menu);
        tDelay(1000);
        *menu = 0;
        break;
    }
    }
}
/*
 * This function will call for an update on the LCD menu after
 * a correct command key is pressed (up-2, down-8, select-#, back-*)
 */
void checkInput(char key)
{
    static int row;
    static int menu;
    //check which key was pressed
    if(key == '2')
        {
        //if 2 (up) then go back a row position
            row--;
            LoadLCD(&row,&menu);
        }else if(key == '8')
        {
            //if 8 (down) then go forward a row position
            row++;
            LoadLCD(&row,&menu);
        }else if(key == '#')
        {
            //if # (select) the go forward a menu position
            menu = (++row)+(menu*10);
            row = 0;
            LoadLCD(&row,&menu);
        }else if(key == '*')
        {
            //if * (back) then reset everything to default position (0)
            menu = 0;
            row = 0;
            LoadLCD(&row,&menu);
        }
}

#endif /* MENU_H_ */

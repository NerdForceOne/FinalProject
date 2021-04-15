/*
 * menu.h
 *
 *  Created on: Apr. 15, 2021
 *      Author: Jared
 *      Version 1.0.0
 *      Changes:
 *       1.0.0:
 *           --Header Created
 */
#ifndef MENU_H_
#define MENU_H_

//Includes
#include <SerLCD.h>

//Defines
/*
 * This is the Main Menu array format
 * if the number of rows change then make sure
 * to update the row count define
 */
#define mainMenuRows 8
char* mainMenu[mainMenuRows]=  {{"Choice 0"},
                                {"Choice 1"},
                                {"Choice 2"},
                                {"Choice 3"},
                                {"Choice 4"},
                                {"Choice 5"},
                                {"Choice 6"},
                                {"Choice 7"}};
/*
 * This is the Menu 1 array format
 * if the number of rows change then make sure
 * to update the row count define
 */
#define menu1Rows 3
char* menu1[menu1Rows] = {{"menu1 0"},
                          {"menu1 1"},
                          {"menu1 2"}};
/*
 * This is the Menu 2 array format
 * if the number of rows change then make sure
 * to update the row count define
 */
#define menu2Rows 4
char* menu2[menu2Rows] = {{"menu2 0"},
                          {"menu2 1"},
                          {"menu2 2"},
                          {"menu2 3"}};
/*
 * This is the Menu 3 array format
 * if the number of rows change then make sure
 * to update the row count define
 */
#define menu3Rows 2
char* menu3[menu3Rows] = {{"menu3 0"},
                          {"menu3 1"}};
/*
 * This is the Menu 4 array format
 * if the number of rows change then make sure
 * to update the row count define
 */
#define menu4Rows 5
char* menu4[menu4Rows] = {{"menu4 0"},
                          {"menu4 1"},
                          {"menu4 2"},
                          {"menu4 3"},
                          {"menu4 4"}};


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
void LoadLCD(int *row,int menu)
{
    switch(menu){
    case 0:
        LoadMainMenu(&*row);
        break;
    case 1:
        LoadMenu1(&*row);
        break;
    case 2:
        LoadMenu2(&*row);
        break;
    case 3:
        LoadMenu3(&*row);
        break;
    case 4:
        LoadMenu4(&*row);
        break;
    default:
        LoadMainMenu(&*row);
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
            LoadLCD(&row,menu);
        }else if(key == '8')
        {
            //if 8 (down) then go forward a row position
            row++;
            LoadLCD(&row,menu);
        }else if(key == '#')
        {
            //if # (select) the go forward a menu position
            menu = row+1;
            row = 0;
            LoadLCD(&row,menu);
        }else if(key == '*')
        {
            //if * (back) then reset everything to default position (0)
            menu = 0;
            row = 0;
            LoadLCD(&row,menu);
        }
}

#endif /* MENU_H_ */

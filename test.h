/*****************************************************************************
* | File      	:   trst.h
* | Author      :   Waveshare team
* | Function    :   
* | Info        :
*
*----------------
* |	This version:   V1.0
* | Date        :   2020-05-20
* | Info        :   Basic version
*
******************************************************************************/

#ifndef _TRST_H_
#define _TRST_H_

void LCD_1IN28_test(void);
void Touch_HandWriting();
void Touch_Gesture();
void Touch_INT_callback(void);
char loadBmp(const char *path);
char getTouch();

#endif
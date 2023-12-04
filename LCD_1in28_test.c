#include "DEV_Config.h"
#include "LCD_1in28.h"
#include "Touch_1in28.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "test.h"
#include "image.h"
#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()
#include <wiringPi.h>

void Touch_INT_callback(void);

UBYTE flag = 0,flgh = 0;
static UBYTE isInit = 0;
UWORD BlackImage[LCD_1IN28_HEIGHT*LCD_1IN28_WIDTH*2];


/************************************************************************/
void Touch_INT_callback(void) {
    flag = TOUCH_IRQ;
    if (XY.mode == 0)
        XY.Gesture = I2C_Read_Byte(0x01);
}

/************************************************************************/
char init(){
    printf("My init.\r\n");
    // Exception handling:ctrl + c
    signal(SIGINT, Handler_1IN28_LCD);    
    
	if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        //exit(0);
        return 1;
    }

    LCD_1IN28_Init(HORIZONTAL);
	LCD_1IN28_Clear(BLACK);
	LCD_SetBacklight(1023); 

    Paint_NewImage(BlackImage, LCD_1IN28_WIDTH, LCD_1IN28_HEIGHT, 0, BLACK, 16);
    Paint_Clear(WHITE);
	Paint_SetRotate(ROTATE_0);   

    // TP Init    
    if(Touch_1IN28_init(XY.mode) == true)
        printf("Success:Detected CST816T.\r\n");
    else
        printf("Error: Not Detected CST816T.\r\n");

    wiringPiISR(TP_INT, INT_EDGE_FALLING, &Touch_INT_callback);

    return 0;
}

/************************************************************************/
char getTouch(){
    if(isInit == 0){
        //char res = 
        init();
        //if(res) return res;
        isInit = 1;
    }
    if (flag == TOUCH_IRQ){
        printf("Touch_INT_callback\r\n");
        flag = 0;
        DEV_Delay_ms(1);
        return 1;
    }
    return 0;
}

/************************************************************************/
char loadBmp(const char *path){
    if(isInit == 0){
        char res = init();
        if(res) return res;
        isInit = 1;
    }

	LCD_1IN28_Clear(BLACK);
    
    Paint_NewImage(BlackImage, LCD_1IN28_WIDTH, LCD_1IN28_HEIGHT, 0, BLACK, 16);
    Paint_Clear(WHITE);
	Paint_SetRotate(ROTATE_0); 

    Paint_SelectImage(BlackImage);
    //if (0 == GUI_ReadBmp(path)) return 3;
    GUI_ReadBmp(path);

    LCD_1IN28_Display((UWORD *)BlackImage);

    return 0;
}

/************************************************************************/
void clearLcd(){
	LCD_1IN28_Clear(BLACK);        
}

